#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

bool solve(int n, int m, vector<vector<int>> g) {
    vector<vector<int>> g2(n);
    vector<int> lv(n, -1), atv(n), par(n), lvl(n), deg(n);
    vector<ii> be;
    auto findp = [&] (auto&& self, int u) -> int { return par[u] = (par[u] == u ? u : self(self, par[u])); };
    int comps = n;
    auto merge = [&] (int u, int v) {
        u = findp(findp, u), v = findp(findp, v);
        if (v == u) return;
        if (lvl[u] < lvl[v]) swap(u, v);
        par[v] = u;
        lvl[u] += (lvl[u] == lvl[v]);
        comps--;
    };
    auto dfs = [&] (auto&& self, int u) -> void {
        for (auto v : g[u]) {
            if (lv[v] == -1) {
				lv[v] = 1 + lv[u], self(self, v), g2[u].pb(v), g2[v].pb(u);
			}
            else if (lv[v] > lv[u]) be.pb({u, v}), merge(u, v);
        }
    };
    iota(all(par), 0);
    lv[0] = 0, dfs(dfs, 0);
    int m2 = sz(be);
    if (comps != n - m2) return true;
    bool ok = 0;
    for (int i = 1; i < (1 << m2); ++i) {
        iota(all(par), 0);
        for (int j = 0; j < n; ++j) lvl[j] = atv[j] = deg[j] = 0;
        comps = n;
        auto dfs2 = [&] (auto&& self, int u, int p) -> int {
            for (auto v : g2[u]) {
                if (v == p) continue;
                atv[u] ^= self(self, v, u);
            }
            if (atv[u] and u != p) deg[u]++, deg[p]++;
            else {
				merge(u, p);
			}
            return atv[u];
        };
        for (int j = 0; j < m2; ++j) {
            auto [u, v] = be[j];
            if (i >> j & 1) {
                atv[u] ^= 1, atv[v] ^= 1;
                deg[u]++, deg[v]++;
			}
            else merge(u, v);
        }
        dfs2(dfs2, 0, 0);
        if (comps == 1) { 
            ok = 1; 
            for (int j = 0; j < n; ++j) ok &= (deg[j] == 0 or deg[j] == 2);
            if (ok) break;
        }
    }
    return ok;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        vector<vector<int>> g(n), g2(n);
        for (int i = 0; i < m; ++i) {
            int u, v; cin >> u >> v;
            --u, --v;
            g[u].pb(v), g[v].pb(u);
        }
        cout << (solve(n, m, g) ? "Yes" : "No") << endl;
    }
#else
#endif
}
