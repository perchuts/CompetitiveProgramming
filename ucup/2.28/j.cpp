#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define pb push_back
#define int ll
#define endl '\n'

using namespace std;

using ll = long long;

int32_t main() {_
	int n, q; cin >> n >> q;
	vector<vector<int>> g(n);
	for (int i = 0; i < n-1; ++i) {
		int u, v; cin >> u >> v; --u, --v;
		g[u].pb(v), g[v].pb(u);
	}
	vector<int> par(n), ini(n), fim(n), subt(n);
	int tt = 0;
	auto dfs = [&] (auto&& self, int u, int p) -> void {
		par[u] = p;
		ini[u] = ++tt;
		subt[u] = 1;
		for (auto v : g[u]) {
			if (v == p) continue;
			self(self, v, u);
			subt[u] += subt[v];
		}
		fim[u] = tt;
	};
	dfs(dfs, 0, 0);
	auto is_anc = [&] (int u, int v) {
		return (ini[u] <= ini[v] and fim[v] <= fim[u]);
	};
	vector<int> vis(n);
	while (q--) {
		int k; cin >> k;
		vector<int> a(k);
		for (auto& x : a) cin >> x, --x;
		int i = 0, ok = true, m = a.size();
		auto check = [&] (auto&& self, int u, int id) -> bool {
			if (vis[u] == true) return false;
			vis[u] = true;
			int cur = id+1;
			while (cur < min(id+subt[u], m)) { 
				int v = a[cur];
				if (par[v] != u or self(self, v, cur) == false) return false;
				cur += subt[v];
			}
			return true;
		};
		set<int> foi;
		while (i < m) {
			auto prim = foi.lower_bound(ini[a[i]]);
			if (prim != end(foi) and *prim <= fim[a[i]]) {
				ok = false;
				break;
			}
			foi.insert(ini[a[i]]);
			ok &= check(check, a[i], i);
			if (!ok) break;
			int prox = i + subt[a[i]];
			if (prox < m) {
				int v = a[prox];
				if (!is_anc(par[v], a[i]) or is_anc(v, a[i])) { ok = 0; break; }
			}
			i += subt[a[i]];
		}
		for (auto x : a) vis[x] = 0;
		cout << (ok ? "Yes" : "No") << endl;
	}
}
