#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

const int mod = 1e9 + 7;

int32_t main() {
	fast_io;

	int n, m;
	cin >> n >> m;
	vector dp(n+1, vector(n+1, vector(2, 0LL)));
	dp[0][0][1] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int k = 1; k <= min(n, m); ++k) {
			dp[i][k][0] = (dp[i-1][k-1][1] * (m-k+1) + dp[i-1][k][0] * (m-k)) % mod;
			dp[i][k][1] = (k * dp[i-1][k][0] + k * dp[i-1][k][1]) % mod;
		}
	}
	int ans = 0;
	for (int i = 1; i <= min(m, n); ++i) ans = (ans + dp[n][i][1]) % mod;
	cout << ans << endl;	
}
