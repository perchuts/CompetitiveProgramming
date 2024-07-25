#include <bits/stdc++.h>
#define int long long
using namespace std;

void solve() {
	int n; cin >> n;
	vector<vector<int>> grid(n, vector<int>(n));
	for (auto& x : grid) for (auto& y : x) cin >> y;
	vector<int> dp(16, 1e18), best(16, 1e18);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			int type = 0;
			if (i <= (n)/2 && j <= (n)/2) type += 1;
			if (i <= (n)/2 && j >= (n)/2) type += 2;
			if (i >= (n)/2 && j <= (n)/2) type += 4;
			if (i >= (n)/2 && j >= (n)/2) type += 8;
			best[type] = min(best[type], grid[i][j]);
		}
	}
	dp[0] = 0;
	for (int i = 1; i < 16; ++i) {
		for (int j = 1; j < 16; ++j) {
			dp[i] = min(dp[i], dp[i-(j&i)] + best[j]);
		}
	}	
	cout << dp[15] << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
}
