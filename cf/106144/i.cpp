#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define _ ios_base::sync_with_stdio(0);cin.tie(0);

const int MAX = 1e6 + 10;

vector<int> g[MAX];
vector<int> gi[MAX];
bool vis[MAX];
int sc[MAX], sv[MAX];
int comp[MAX];
stack<int> S;
int n;

void dfs(int k) {
        vis[k] = 1;
        for (int i = 0; i < (int) g[k].size(); ++i)
                if (!vis[g[k][i]]) dfs(g[k][i]);
        S.push(k);
}
void scc(int k, int c) {
        vis[k] = 1;
        comp[k] = c;
        for (int i = 0; i < (int) gi[k].size(); ++i) {
                if (!vis[gi[k][i]]) scc(gi[k][i], c);
        }
}

void kosaraju() {
        for (int i = 0; i < n; ++i) vis[i] = 0;
        for (int i = 0; i < n; ++i) if (!vis[i]) dfs(i);

        for (int i = 0; i < n; ++i) vis[i] = 0;
        while (S.size()) {
                int u = S.top();
                S.pop();
                if (!vis[u]) scc(u, u);
        }
}


void solve() {
        cin >> n;
        vector<int> cor(n), qnt(n);
        for (auto& x : cor) cin >> x, --x, qnt[x]++;
        vector<vector<int>> gt(n);
        for (int i = 0; i < n-1; ++i) {
                int u, v; cin >> u >> v; --u, --v;
                gt[u].push_back(v), gt[v].push_back(u);
        }
        int hh = n;
        vector<int> subt(n), vist(n);
        auto dfs1 = [&] (auto&& self, int u, int p) -> int {
                subt[u] = 1;
                for (auto v : gt[u]) {
                        if (vist[v] or v == p) continue;
                        subt[u] += self(self, v, u);
                }
                return subt[u];
        };
        auto findc = [&] (auto&& self, int u, int p, int tam) -> int {
                for (auto v : gt[u]) {
                        if (vist[v] or v == p) continue;
                        if (2 * subt[v] > tam) return v;
                }
                return u;
        };
        int act_cen = -1;
        vector<int> version(n), vis_w(n), fez_w(n), add(n);
        auto dfs2 = [&] (auto&& self, int u, int p, int tipo) -> void {
                if (tipo == 0) {
                        version[u] = hh++;
                        if (u != p) {
                                g[version[u]].push_back(version[p]);
                                gi[version[p]].push_back(version[u]);
                        }
                        g[version[u]].push_back(cor[u]);
                        gi[cor[u]].push_back(version[u]);
                        if (vis_w[cor[u]] == act_cen) fez_w[cor[u]] = act_cen;
                }
                if (tipo == 1) vis_w[cor[u]] = act_cen;
                if (tipo == 2) {
                        if (fez_w[cor[u]] == act_cen) {
                                g[cor[u]].push_back(version[u]);
                                gi[version[u]].push_back(cor[u]);
                        }
                }
                for (auto v : gt[u]) {
                        if (v == p or vist[v]) continue;
                        self(self, v, u, tipo);
                }
        };
        auto decomp = [&] (auto&& self, int u) -> void {
                dfs1(dfs1, u, u);
                int c = findc(findc, u, u, subt[u]);
                act_cen = c;
                version[c] = hh++;
                vis_w[cor[c]] = act_cen;
                g[version[c]].push_back(cor[c]);
                gi[cor[c]].push_back(version[c]);
                vist[c] = 1;
                for (auto v : gt[c]) {
                        if (vist[v]) continue;
                        dfs2(dfs2, v, c, 0), dfs2(dfs2, v, c, 1);
                }
                for (auto v : gt[c]) {
                        if (vist[v]) continue;
                        dfs2(dfs2, v, c, 2);
                }
                for (auto v : gt[c]) {
                        if (vist[v]) continue;
                        self(self, v);
                }
        };
        decomp(decomp, 0);
        int N = n;
        n = hh;
        kosaraju();
        for (int i = 0; i < N; ++i) {
                sv[comp[i]] += (qnt[i] != 0);
                sc[comp[i]] += qnt[i];
        }
        ll ans = 0;
        for (int i = 0; i < hh; ++i) {
                g[i].clear(), gi[i].clear();
                ans += ll(sv[i]) * sc[i];
                sv[i] = sc[i] = 0;
        }
        cout << ans << endl;
}

int32_t main() {_
        int t; cin >> t;
        while (t--) solve();
}
