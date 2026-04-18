#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll

using namespace std;

using ll = long long;

int32_t main() {_
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<vector<int>> g(n), gr(n);
		vector<int> p(n), vis(n), is_cycle(n);
		for (auto& x : p) cin >> x, --x;
		for (int i = 0; i < n; ++i) {
			g[i].pb(p[i]);
			gr[p[i]].pb(i);
		}
		auto mark = [&] (auto&& self, int u) -> void {
			vis[u] = 3;
			for (auto v : gr[u]) {
				if (vis[v] == 3) continue;
				self(self, v);
			}
		};
		vector<vector<int>> cycles;
		for (int i = 0; i < n; ++i) {
			if (vis[i]) continue;
			int cur = i;
			while (!vis[cur]) vis[cur] = 1, cur = p[cur];
			cycles.pb({});
			while (vis[cur] != 2) {
				cycles.back().pb(cur);
				is_cycle[cur] = 1;
				vis[cur] = 2;
				cur = p[cur];
			}
			mark(mark, cycles.back()[0]);
		}
		vector<vector<int>> dp(n, vector<int>(2));
		auto dfs = [&] (auto&& self, int u) -> void {
			dp[u][1] = 1;
			for (auto v : gr[u]) {
				if (is_cycle[v]) continue;
				self(self, v);
				dp[u][0] += dp[v][1];
				dp[u][1] += min(dp[v][0], dp[v][1]);
			}
		};
		for (int i = 0; i < n; ++i) {
			if (is_cycle[i]) dfs(dfs, i);
		}
		int ans = 0;
		auto solve = [&] (vector<int> bichos) {
			int dp0 = 0, dp1 = n * 69;
			for (auto u : bichos) {
				int ndp0 = min(dp0, dp1) + dp[u][1];
				int ndp1 = dp0 + dp[u][0];
				dp0 = ndp0;
				dp1 = ndp1;
			}
			return min(dp0, dp1);
		};
		for (auto cyc : cycles) {
			if (cyc.size() == 1) {
				ans += dp[cyc[0]][1];
				continue;
			}
			int k = cyc.back();
			cyc.pop_back();
			int opt = solve(cyc) + dp[k][1];
			cyc.push_back(k);
			reverse(begin(cyc), end(cyc));
			k = cyc.back();
			cyc.pop_back();
			reverse(begin(cyc), end(cyc));
			opt = min(opt, solve(cyc) + dp[k][1]);
			ans += opt;
		}
		cout << ans << endl;
	}
}
