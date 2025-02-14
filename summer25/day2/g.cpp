#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

const int mod = 1e9+7;

int32_t main() {
	fast_io;
	int n; cin >> n;
	vector<int> v(n);
	for (auto& x : v) cin >> x;
	vector<vector<int>> dp(n+1, vector<int>(10000));
	sort(begin(v), end(v));
	dp[0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		int val = v[i-1];
		for (int j = 0; j < 10000; ++j) {
			dp[i][j] = dp[i-1][j];
			if (j - val >= 0 and val <= j-val+1) {
				if (j >= 4999) {
					if (j - val < 4999) dp[i][j] += dp[i-1][j-val];
				} else dp[i][j] += dp[i-1][j-val];
			}
			if (dp[i][j] >= mod) dp[i][j] -= mod;
		}
	}
	vector<int> pot(n+1);
	pot[0] = 1;
	for (int i = 1; i <= n; ++i) pot[i] = (pot[i-1] + pot[i-1]) % mod;
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 4999; j < 10000; ++j) {
			int x = (dp[i][j] - dp[i-1][j] + mod) % mod;
			ans = (ans + x * pot[n-i]) % mod;
		}
	}
	for (int j = 1; j < 4999; ++j) ans = (ans + dp[n][j]) % mod;
	cout << ans << endl;
}
