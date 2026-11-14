#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;

int32_t main() {_
	int n, m; cin >> n >> m;
	vector<tuple<int, int, int>> edg(m);
	for (auto& [w, u, v] : edg) cin >> u >> v >> w, --u, --v;
	sort(rbegin(edg), rend(edg));
	vector<int> par(n), lvl(n, 1);
	iota(begin(par), end(par), 0);
	auto findp = [&] (auto&& self, int u) -> int {
		return par[u] = (par[u] == u ? u : self(self, par[u]));
	};
	auto unite = [&] (int u, int v) {
		u = findp(findp, u), v = findp(findp, v);
		if (u == v) return;
		if (lvl[u] < lvl[v]) swap(u, v);
		par[v] = u;
		lvl[u] += lvl[v];
	};
	vector<vector<int>> g(n);
	vector<int> vis(n), qt(3);
	bool ok = true;
	auto dfs = [&] (auto&& self, int u) -> void {
		qt[vis[u]] += lvl[u];
		for (auto v : g[u]) {
			if (vis[v]) ok &= (vis[v] != vis[u]);
			else vis[v] = 3 - vis[u], self(self, v);
		}
	};
	int ans = 0;
	for (int l = 0, r = 0; l != m; l = r) {
		while (r != m and get<0>(edg[l]) == get<0>(edg[r])) r++;
		for (int i = l; i < r; ++i) {
			auto [w, u, v] = edg[i];
			u = findp(findp, u);
			v = findp(findp, v);
			if (u == v) {
				cout << "impossible" << endl;
				return 0;
			}
			g[u].pb(v), g[v].pb(u);
		}
		for (int i = l; i < r; ++i) {
			auto [w, u, v] = edg[i];
			u = findp(findp, u);
			v = findp(findp, v);
			if (!vis[u]) {
				vis[u] = 1;
				dfs(dfs, u);
				ans += min(qt[1], qt[2]);
				qt[1] = qt[2] = 0;
			}
		}
		for (int i = l; i < r; ++i) {
			auto [w, u, v] = edg[i];
			u = findp(findp, u);
			v = findp(findp, v);
			g[u].clear(), g[v].clear();
			vis[u] = vis[v] = 0;
			unite(u, v);
		}
	}
	if (!ok) {
		cout << "impossible" << endl;
		return 0;
	}
	cout << "possible" << endl;
	cout << ans << endl;
}
