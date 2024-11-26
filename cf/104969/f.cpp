#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define int ll
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;

int32_t main() {
    fast_io;

	int n, k; cin >> n >> k;
	const int MOD = 1e9 + 7;

	vector dp(n + 1, vector(k + 1, 0));
	dp[0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= k; ++j) {
			for (int pos = 0; pos <= i-1 and j+pos <= k; ++pos) {
				dp[i][j+pos] += dp[i-1][j];
				if (dp[i][j+pos] >= MOD) dp[i][j+pos] -= MOD;
			}
		}
	}

	cout << dp[n][k] << endl;
}
