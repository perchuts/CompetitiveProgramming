#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;

int32_t main() {_
	int n, m; cin >> n >> m;
	vector<vector<int>> g(n);
	map<pair<int, int>, int> id;
	for (int i = 0; i < m; ++i) {
		int u, v; cin >> u >> v; --u, --v;
		g[u].pb(v), g[v].pb(u);
		id[{u, v}] = id[{v, u}] = i;
	}
	vector<int> ord(n);
	for (auto& x : ord) cin >> x, --x;
	if (ord[0] != 0) { 
		cout << "impossible" << endl;
		return 0;
	}
	vector<vector<int>> t(n);
	vector<int> par(n), online(n), vis(n), lvl(n), is_adj(n);
	stack<int> st;
	for (int i = 0; i < n - 1; ++i) {
		online[ord[i]] = vis[ord[i]] = 1, st.push(ord[i]), lvl[ord[i]] = st.size();
		for (auto v : g[ord[i+1]]) is_adj[v] = 1;
		for (auto v : g[ord[i]]) {
			if (online[v] == 0 and vis[v] == 1){ 
				// nao eh ordem de dfs!
				cout << "impossible" << endl;
				return 0;
			}
		}
		while (!st.empty()) {
			if (is_adj[st.top()]) break;
			online[st.top()] = false;
			st.pop();
		}
		if (st.empty()) {
			cout << "impossible" << endl;
			return 0;
		}
		int p = st.top();
		for (auto v : g[ord[i+1]]) is_adj[v] = 0;
		par[ord[i+1]] = p;
		t[ord[i+1]].pb(p), t[p].pb(ord[i+1]);
	}
	vector<int> pos(n);
	for (int i = 0; i < n; ++i) pos[ord[i]] = i;
	vector<int> ans(m, 1);
	const int penis = 10000;
	auto dfs = [&] (auto&& self, int u, int p) -> void  {
		sort(begin(t[u]), end(t[u]), [&] (int x, int y) {
				return pos[x] < pos[y];
				});
		if (u == 0) {
			for (int i = 0; i < t[0].size(); ++i) ans[id[{0, t[0][i]}]] = ((int)t[0].size() - i) * penis;
		} else {
			for (int i = 1; i < t[u].size(); ++i) ans[id[{u, t[u][i]}]] = ((int)t[u].size() - i) * penis;
		}
		for (auto v : t[u]) {
			if (v == p) continue;
			self(self, v, u);
		}
	};
	dfs(dfs, 0, 0);
	for (auto x : ans) cout << x << " ";
	cout << endl;
}
