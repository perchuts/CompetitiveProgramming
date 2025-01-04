#include <bits/stdc++.h>
using namespace std;

#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int dp[501][501][501];

int32_t main() {
	fast_io;
	int n, k; cin >> n >> k;
	string s; cin >> s;
	for (int i = 0; i <= n; ++i) for (int j = 0; j <= n; ++j) {
		for (int w = 1; w <= n; ++w) dp[i][j][w] = n + 69;
	}
	for (int i = n; i >= 1; --i) {
		for (int j = i; j <= n; ++j) {
			for (int w = 0; w <= n; ++w) {
				dp[i][j][w] = n+69;
				if (w == 0) {
					dp[i][j][w] = 0;
					continue;
				}

				if (s[i-1] == s[j-1]) {
					if (i == j && w == 1) dp[i][j][w] = 0;
					if (i != j && w > 1) dp[i][j][w] = dp[i+1][j-1][w-2];
				}

				if (i == j && w == 1) dp[i][j][w] = min(dp[i][j][w], 1);
				if (i != j && w > 1) dp[i][j][w] = min(dp[i][j][w], dp[i+1][j-1][w-2]+1);

				if (i != j) {
					dp[i][j][w] = min(dp[i][j][w], dp[i+1][j][w]);
					dp[i][j][w] = min(dp[i][j][w], dp[i][j-1][w]);
				}
			}
		}
	}
	cout << dp[1][n][k] << endl;

}
