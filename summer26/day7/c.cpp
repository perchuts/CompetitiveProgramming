#include <bits/stdc++.h>
#define int ll
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
using namespace std;

using ll = long long;

int32_t main() {_
	int n; cin >> n;
	vector<int> x(n+1), s(n+1);
	vector<vector<int>> a(n+1, vector<int>(n+1)), g(n+1);
	for (int i = 1; i <= n; ++i) {
		cin >> s[i] >> x[i];
		g[s[i]].pb(i);
		for (int j = 0; j <= n; ++j) cin >> a[i][j];
	}
	vector<vector<int>> cycles;
	vector<int> vis(n+1), is_cycle(n+1);
	auto mark = [&] (auto&& self, int u) -> void {
		vis[u] = 3;
		for (auto v : g[u]) {
			if (vis[v] == 3) continue;
			self(self, v);
		}
	};
	int base = 0;
	for (int i = 0; i <= n; ++i) {
		if (vis[i]) continue;
		int cur = i;
		while (vis[cur] == 0) {
			vis[cur] = 1;
			cur = s[cur];
		}
		cycles.pb({});
		vector<int> opt(n+1, 1e18);
		int opt_s = -1e18;
		while (vis[cur] == 1) {
			opt_s = max(opt_s, x[cur]);
			vis[cur] = 2;
			cycles.back().pb(cur);
			is_cycle[cur] = 1;
			cur = s[cur];
		}
		base -= opt_s;
		for (auto u : cycles.back()) {
			for (int j = 0; j <= n; ++j) opt[j] = min(opt[j], a[u][j] + opt_s - x[u]);
		}
		for (auto k : cycles.back()) a[k] = opt;
		mark(mark, cycles.back()[0]);
	}
	for (int i = 0; i <= n; ++i) base += x[i];
	for (auto cyc : cycles) {
		base += a[cyc[0]][n];
		int z = a[cyc[0]][n];
		for (auto u : cyc) for (int i = 0; i <= n; ++i) a[u][i] -= z;
	}
	for (int i = 1; i <= n; ++i) {
		if (is_cycle[i]) continue;
		for (int j = 0; j <= n; ++j) a[i][j] -= x[i];
	}
	auto dfs = [&] (auto&& self, int u) -> void {
		for (auto v : g[u]) {
			if (is_cycle[v]) continue;
			for (int i = 0; i <= n; ++i) a[v][i] = min(a[v][i], a[u][i]);
			self(self, v);
		}
	};
	for (auto cyc : cycles) {
		for (auto u : cyc) dfs(dfs, u);
	}
	vector<int> dp(n+1, 1e18);
	dp[0] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < i; ++j) {
			dp[i] = min(dp[i], dp[j] + a[i][j]);
		}
	}
	cout << dp[n] + base << endl;
}
