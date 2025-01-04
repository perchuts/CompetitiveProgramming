#include <bits/stdc++.h>
#define sz(x) (int) x.size()
#define pb push_back
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

const int mod = (119<<23)+1;

int32_t main() {
	fast_io;
	int n; cin >> n;
	vector<int> a(n), primos;
	for (auto& x : a) cin >> x;
	vector<vector<int>> dp(2, vector<int>(512)), ndp = dp;
	dp[0][0] = dp[1][0] = 1;
	for (int i = 2; ; ++i) {
		bool ok = 1;
		for (int j = 2; j * j <= i; ++j) {
			if (i % j == 0) ok = 0;
		}
		if (ok) primos.pb(i);
		if (sz(primos) == n) break;
	}
	for (int i = 0; i < n; ++i) {
		for (int k = 0; k < 512; ++k) ndp[0][k] = 0, ndp[1][k] = 0;
		int pot = 1;
		for (int j = 0; j <= a[i]; ++j) {
				for (int k = 0; k < 512; ++k) {
					// numero de elementos 
					ndp[0][k] += dp[0][k^(a[i]-j)];
					if (ndp[0][k] >= mod) ndp[0][k] -= mod;
					// soma de elementos
					ndp[1][k] += pot * dp[1][k^(a[i]-j)];
					ndp[1][k] %= mod;
				}
				pot = pot * primos[i] % mod;
		}
		swap(dp, ndp);
	}
	cout << dp[0][0] << ' ' << dp[1][0] << endl;
}
