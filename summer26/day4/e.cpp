#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define endl '\n'
#define pb push_back

using namespace std;

using ll = long long;

void solve() {
	int n, m, k; cin >> n >> m >> k; swap(m, k);
	vector<vector<int>> gg(n), g(n);
	vector<int> par(n), lvl(n); iota(begin(par), end(par), 0);
	auto findp = [&] (auto&& self, int u) -> int { return par[u] = (par[u] == u ? u : self(self, par[u])); };
	auto merge = [&] (int u, int v) {
		u = findp(findp, u), v = findp(findp, v);
		if (u == v) return;
		if (lvl[u] < lvl[v]) swap(u, v);
		par[v] = u;
		if (lvl[u] == lvl[v]) ++lvl[u];
	};
	for (int i = 0; i < m; ++i) {
		int u, v, w; cin >> u >> v >> w;
		--u, --v;
		if (w == 1) gg[u].pb(v), gg[v].pb(u);
		else merge(u, v);
	}
	// n - 1 - 2 * z
	// se isso eh zero, ent eh impossivel descobrir
	if (2 * k == n-1) {
		cout << "No" << endl;
		return;
	}
	for (int i = 0; i < n; ++i) {
		for (auto j : gg[i]) {
			g[findp(findp, i)].pb(findp(findp, j));
		}
	}
	vector<int> vis(n), comps;
	auto dfs = [&] (auto&& self, int u) -> int {
		int ans = 1;
		vis[u] = 1;
		for (auto v : g[u]) {
			if (vis[v]) continue;
			ans -= self(self, v);
		}
		return ans;
	};
	for (int i = 0; i < n; ++i) {
		if (vis[i]) continue;
		comps.pb(abs(dfs(dfs, i)));
	}
	// tem 2 formas de escrever n - 1 - 2 * z = X?
	// entao pega o que mudou (x -> -x. ent temos \sum 2 * deltai * xi = 0. -> \sum deltai * xi = 0). logo
	// se tem 2 formas de escrever X, tem subset com soma 0
	// se tem subset com soma zero e 1 forma de escrever X, flipa as variaveis q participam do subset de soma 0 -> temos outra forma de escrever X!!
	// entao a condicao de descoberta eh equivalente a nao ter subset de soma 0 (ou 2 subsets de soma igual, se quisermos evitar o delta[i])
	for (auto x : comps) cout << x << " ";
	cout << endl;
}

int32_t main() {_
	int t; cin >> t;
	while (t--) solve();
}
