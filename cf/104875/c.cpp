#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
using namespace std;

using ll = long long;

const int mod = 998244353;
const int inf = 2e9 + 100;
const int magic = 17842;

int32_t main() {_
	int s; cin >> s;

	double lo = 0.2, hi = magic;
	while (abs(hi - lo) > 1e-7) {
		double mid = (lo + hi) / 2;
		
		int cnt = 0;
		for (int i = 1; i <= min<int>(mid, magic); i++) {
			double tot = mid * mid - i * i;
			int add = sqrt(tot) + 1;
			while (add * add > tot + 1e-7) --add;
			cnt += add;
		}

		if (4 * cnt > s)
			hi = mid;
		else
			lo = mid;
	}

	cout << fixed << setprecision(9);
	cout << lo << endl;
}
