#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;
	int n, k; cin >> n >> k;
	vector<int> t(n);
	for (auto& x : t) cin >> x;
	int m; cin >> m;
	map<pair<int, int>, bool> exists;
	for (int i = 0; i < m; ++i) {
		int u, v; cin >> u >> v;
		exists[{u, v}] = 1;
	}
	vector<int> dp(n, -1);
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		if (t[i] == k+1) continue;
		if (i < 2) dp[i] = 1;
		for (int j = i-1; j > max(-1ll, i-3); --j) {
			if (dp[j] == -1) continue;
			if (exists[{t[j], t[i]}]) dp[i] = max(dp[i], dp[j] + 1);
		}
		if (i > n-3 and dp[i] != -1) ans = max(ans, dp[i]);
	}
	cout << ans << endl;
}
