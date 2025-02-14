#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

const int N = 5001;
int dp[N][4], ndp[N][4], dist[N], cnt[N];

int32_t main() {
	fast_io;

	int n; cin >> n;
	vector<vector<int>> adj(n);
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		adj[a].emplace_back(b);
		adj[b].emplace_back(a);
	}

	auto dfs = [&] (auto&& dfs, int u, int p) -> void {
		dist[u] = dist[p] + 1;
		cnt[dist[u]]++;
		for (int v : adj[u]) if (v != p) {
			dfs(dfs, v, u);
		}
	};

	int ans = 0;
	for (int r = 0; r < n; r++) {
		memset(dp, 0, sizeof dp);
		for (int u : adj[r]) {
			memset(ndp, 0, sizeof ndp);
			memset(cnt, 0, sizeof cnt);
			dist[r] = 0;
			dfs(dfs, u, r);
			for (int j = 0; j < n; j++) {
				for (int p = 0; p <= 3; p++) {
					ndp[j][p] += dp[j][p];
					if (p + 1 <= 3) {
						if (p > 0) ndp[j][p + 1] += dp[j][p] * cnt[j];
						else ndp[j][p + 1] += cnt[j];
					}
				}
				for (int p = 0; p <= 3; p++)
					dp[j][p] = ndp[j][p];
			}
		}
		for (int i = 0; i < n; i++)
			ans += dp[i][3];
	}

	cout << ans << endl;
}
