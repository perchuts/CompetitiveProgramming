#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define endl '\n'
#define pb push_back
using namespace std;

using ll = long long;

int32_t main() {_
	int n, m; cin >> n >> m;
	vector<vector<int>> g(n);
	for (int i = 0; i < m; ++i) {
		int u, v; cin >> u >> v; --u, --v;
		g[u].pb(v), g[v].pb(u);
	}
	vector<int> vis(n);
	vector<tuple<int, int, int>> ans;
	map<pair<int, int>, int> used;
	auto dfs = [&] (auto&& self, int u, int p) -> int {
		vis[u] = 1;
		vector<int> available;
		for (auto v : g[u]) {
			if (v == p) continue;
			if (vis[v]) {
				if (!used[{u, v}] and !used[{v, u}]) available.push_back(v);
				continue;
			}
			if (self(self, v, u)) available.pb(v);
		}
		for (int i = 1; i < available.size(); i += 2) {
			ans.push_back({available[i], u, available[i-1]});
			used[{available[i], u}] = used[{available[i-1], u}] = 1;
		}
		if ((available.size() & 1) and u != p) {
			used[{available.back(), u}] = 1;
			ans.push_back({available.back(), u, p});
			return 0;
		}
		return 1;
	};
	for (int i = 0; i < n; ++i) {
		if (!vis[i]) dfs(dfs, i, i);
	}
	cout << ans.size() << endl;
	for (auto [u, v, w] : ans) cout << u + 1 << " " << v + 1 << " " << w + 1 << endl;
}
