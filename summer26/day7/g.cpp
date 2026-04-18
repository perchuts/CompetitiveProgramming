#include <bits/stdc++.h>
#define int ll
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define pb push_back
#define endl '\n'
using namespace std;

using ll = long long;

int32_t main() {_
	while (true){ 
		int n, m; cin >> n >> m;
		if (n == 0) break;
		vector<vector<int>> gg(n);
		vector<vector<pair<int, int>>> adj(n);
		for (int i = 0; i < m; ++i) {
			int u, v; cin >> u >> v; --u, --v;
			gg[u].pb(v);
			gg[v].pb(u);
		}
		for (int i = 0; i < n; ++i) gg[i].pb(i);
		for (int i = 0; i < n; ++i) { 
			sort(begin(gg[i]), end(gg[i]));
			int lst = -1;
			for (auto x : gg[i]) {
				if (x != lst+1) { 
					adj[i].push_back({lst+1, x-1});
				}
				lst = x;
			}
			if (lst != n-1) adj[i].push_back({lst+1, n-1});
		}
		vector g(2, vector(5*n, vector<pair<int, int>>()));
		vector gi(2, vector(5*n, vector<pair<int, int>>()));
		auto build = [&] (auto&& self, int i, int l, int r) -> void {
			if (l == r) {
				g[0][i].pb({0, 4*n+l});
				g[1][i].pb({1, 4*n+l});
				return;
			}
			int md = (l + r) / 2;

			g[0][i].pb({0, 2*i});
			g[0][i].pb({0, 2*i+1});

			g[1][i].pb({1, 2*i});
			g[1][i].pb({1, 2*i+1});

			self(self, 2*i, l, md);
			self(self, 2*i+1, md+1, r);
		};
		build(build, 1, 0, n-1);
		auto add = [&] (auto&& self, int i, int l, int r, int x, int y, int u) -> void {
			if (x <= l and r <= y) {
				g[0][4*n+u].pb({1, i});
				g[1][4*n+u].pb({0, i});
				return;
			}
			if (r < x or y < l) return;
			int md = (l+r)/2;
			self(self, 2*i, l, md, x, y, u);
			self(self, 2*i+1, md+1, r, x, y, u);
		};
		for (int i = 0; i < n; ++i) {
			for (auto [l, r] : adj[i]) {
				add(add, 1, 0, n-1, l, r, i);
			}
		}
		vector<vector<int>> vis(2, vector<int>(5*n));
		int ok = 0, t0, t1;
		auto dfs = [&] (auto&& self, int i, int j) -> void {
			vis[i][j] = 1;
			for (auto [i2, j2] : g[i][j]) {
				if (!vis[i2][j2] and !vis[i2^1][j2]) self(self, i2, j2);
				if (i2 == t0 and j2 == t1) ok = 1;
			}
		};
		int ans = n;
		for (int i = 0; i < n; ++i) {
			int foi = 0;
			for (int j = 0; j < 5*n; ++j) vis[0][j] = vis[1][j] = 0;
			t0 = 1, t1 = 4*n+i, ok = 0;
			dfs(dfs, 0, 4*n+i);
			foi += ok;
			for (int j = 0; j < 5*n; ++j) vis[0][j] = vis[1][j] = 0;
			t0 = 0, t1 = 4*n+i, ok = 0;
			dfs(dfs, 1, 4*n+i);
			foi += ok;
			cout << foi << " ";
			if (foi == 2) ans--;
		}
		cout << ans << endl;
	}
}
