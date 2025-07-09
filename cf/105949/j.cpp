#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define pb push_back
typedef long long ll;

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
	int ans = 0;
	vector<int> vis(n), subt(n);
	auto dfs = [&] (auto&& self, int u, int p) -> void {
		subt[u] = 1;
		for (auto v : g[u]) {
			if (v == p or vis[v]) continue;
			self(self, v, u);
			subt[u] += subt[v];
		}
	};
	auto find_cen = [&] (auto&& self, int u, int p, int cc) -> int {
		for (auto v : g[u]) {
			if (v == p or vis[v]) continue;
			if (2 * subt[v] > cc) return self(self, v, u, cc);
		}
		return u;
	};
	vector<vector<int>> cnt(2, vector<int>(10));
	vector<string> want = {"SCCPC", "CPCCS"};
	auto calc = [&] (auto&& self, int u, int p, string& eu, int tipo) -> void {
		if (eu.size() >= 5) return;
		eu += s[u];
		if (tipo == 1) {
			for (int i = 0; i < 2; ++i) {
				bool ok = true;
				for (int j = 0; j < eu.size(); ++j) ok &= (eu[j] == want[i][5-eu.size()+j]);
				if (ok) cnt[i][eu.size()]++;
			}
		} else {
			for (int i = 0; i < 2; ++i) {
				if (eu.size() == 5) ans += (eu == want[i]);
				else {
					bool ok = true;
					for (int j = 0; j < eu.size(); ++j) ok &= (eu[j] == want[i][5-eu.size()+j]);
					if (ok) ans += cnt[i^1][5-eu.size()];
				}
			}
		}
		for (auto v : g[u]) { 
			if (vis[v] or v == p) continue;
			self(self, v, u, eu, tipo);
		}
		eu.pop_back();
	};
	auto go = [&] (auto&& self, int u) -> void {
		dfs(dfs, u, u);
		int c = find_cen(find_cen, u, u, subt[u]);
		vis[c] = true;
		for (int i = 0; i < 2; ++i) for (int j = 0; j < 5; ++j) cnt[i][j] = 0;
		for (auto v : g[c]) {
			if (vis[v]) continue;
			string bicho = "";
			bicho += s[c];
			calc(calc, v, v, bicho, 2);
			bicho.pop_back();
			calc(calc, v, v, bicho, 1);
		}
		for (auto v : g[c]) if (vis[v] == false) self(self, v);
	};
	go(go, 0);
	cout << ans << endl;
}

int32_t main() {
	fast_io;
    int t; cin >> t;
    while (t--) solve();
}
