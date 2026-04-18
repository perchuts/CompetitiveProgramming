#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back

using ll = long long;
using namespace std;

const int mod = 998244353;



int32_t main() {_
	int n; cin >> n;
	vector<int> as(n);
	for (int i = 0; i < n; ++i) cin >> as[i];

	sort(as.begin(), as.end());

	auto g = [&] (int i, int v){
		if(i == n) return 0ll;
		if(as[i] >= v) return n-i;
		return n - (lower_bound(as.begin(), as.end(), v) - as.begin());
	};
	auto f = [&](int i, int v){
		int tam = n-i;
		return tam-g(i,v);
	};
	int lim = 2*n+10;
	vector<int> p3(lim), p2(lim);
	p2[0] = 1;
	for (int i = 1; i < lim; ++i) p2[i] = p2[i-1]*2ll%mod;

	p3[0] = 1;
	for (int i = 1; i < lim; ++i) p3[i] = p3[i-1]*3ll%mod;

	int ans = 0;
	for (int c = n-1; c >= 2; --c)
		for (int b = c-1; b >= 1; --b){
				int x = as[0], y = as[b], z = as[c];
				if (x+y <= z) break;
				vector<int> v = {x+y, x+z, y+z};
				sort(v.begin(), v.end());
				if (c != n-1 and as[n-1] >= v[2]) break;
				int suf = n-c-1;
				int x3 = f(c+1, v[0]);
				int x2 = f(c+1, v[1]);
				int x1 = f(c+1, v[2]);
				int v3 = x3;
				int v2 = x2-x3;
				int v1 = x1-x2;
				int cur = p3[v3] * p2[v2 + c-b-1] % mod;
				ans = (ans + cur) % mod;
		}	

	cout << ans << endl;
}
