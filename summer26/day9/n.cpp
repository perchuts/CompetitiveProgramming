#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int long long
#define endl '\n'
#define pb push_back
#pragma GCC optimize("O3")
using namespace std;

using ll = long long;

const int D = 100000001;
bitset<D> bb;
const int lim = 300000000ll;

using ui = unsigned int32_t;

int32_t main() {_ 
	int id = 1; 
	for (int i = 5; i*i <= lim; ++i){ 
		if (!(i&1)) continue;
		if (i%3 == 0) continue;
		id++;
		if (!bb[id]){
			for (int j = 2ll*i; j <= lim; j += i){
				if (!(j&1)) continue;
				if (j%3 == 0) continue;
				int jd = j - j/2 - j/3 + j/6;
				bb[jd] = 1;
			}
		}
	}


	int n;
	ui a, b, c, d; cin >> n >> a >> b >> c >> d;

	ui ans = 0;

	int m2 = 1, m3 = 2;
	id = 2;
	for (int i = 5; i <= n; ++i){
		if (m2 and m3 and !bb[id]){
			ui v = 0;
			if (i > 100000) v = n/i;
			else for (int p = i; p <= n; p = p*i) v += n/p;

			ui p = i;
			ui f = d + p * (c + p * (b + p * a));
			v *= f;
			ans += v;
		}

		if (m2 and m3) id++;
		m2 = !m2;
		m3 = (m3 == 2) ? 0 : m3+1;
	}

	
	//soma 2
	ui v2 = 0;
	for (int p = 2; p <= n; p = p*2ll) v2 += n/p;
	ui p = 2;
	ui f = d + p * (c + p * (b + p * a));
	v2 *= f;
	ans += v2;

	//soma 3
	v2 = 0;
	for (int p = 3; p <= n; p = p*3ll) v2 += n/p;
	p = 3;
	f = d + p * (c + p * (b + p * a));
	v2 *= f;
	ans += v2;

	cout << ans << endl;
}
