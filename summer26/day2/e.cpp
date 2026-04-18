#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define pb push_back

using namespace std;

using ll = long long;

const int mod = 998244353;

int penis[505][505], dp[505][505][505], subt[505];

void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) { int u, v; cin >> u >> v; --u, --v; g[u].pb(v), g[v].pb(u); }
    auto add = [&] (int& x, int y) { x += y; if (x >= mod) x -= mod; };
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        // dp[u][MEX][USADOS]
        int eh_folha = 1;
        subt[u] = 1;
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
            //dp[u] = merge(dp[u], dp[v]);
            subt[u] += subt[v];
            eh_folha = 0;
        }
        if (eh_folha) { dp[u][1][1] = dp[u][0][0] = 1; return; }
        dp[u][0][0] = 1;
        int tam = 0, cur_mex = 0;
        for (auto v : g[u]) {
            if (v == p) continue;
            int ntam = tam + subt[v];
            int n_mex = max(cur_mex, subt[v]);
            for (int i = 0; i <= n_mex; ++i) {
                for (int j = 0; j <= ntam; ++j) {
                    penis[i][j] = 0;
                }
            }
            for (int i = 1; i <= cur_mex; ++i) {
                for (int j = 0; j <= tam; ++j) {
                    add(dp[u][i][j], dp[u][i-1][j]);
                }
            }
            int tv = subt[v]+1;
            for (int i = 1; i < tv; ++i) {
                for (int j = 0; j < tv; ++j) {
                    add(dp[v][i][j], dp[v][i-1][j]);
                }
            }
            for (int i = 0; i <= n_mex; ++i) {
                for (int j1 = 0; j1 <= tam; ++j1) {
                    for (int j2 = 0; j2 < tv; ++j2) {
                        ll ways = (ll)dp[u][min(cur_mex, i)][j1] * dp[v][min(tv-1, i)][j2] % mod;
                        add(penis[i][j1+j2], ways);
                    }
                }
            }
            for (int i = n_mex; i; --i) {
                for (int j = 0; j <= ntam; ++j) {
                    add(penis[i][j], mod - penis[i-1][j]);
                    if (penis[i][j] >= mod) penis[i][j] -= mod;
                    dp[u][i][j] = penis[i][j];
                }
            }
            tam = ntam;
            cur_mex = n_mex;
        }
        for (int i = 0; i <= subt[u]; ++i) {
            for (int j = 0; j <= subt[u]; ++j) {
                penis[i][j] = 0;
            }
        }
        // penis[x][d] = \sum dp[u][a][b], b-a = d, a <= x
        // precisar de 0 e mex = 0 so tem um jeito!
        penis[0][0] = 1;
        for (int mex = 1; mex <= subt[u]; ++mex) {
            for (int y = 0; y + mex <= subt[u]; ++y) {
                penis[mex][y] = penis[mex-1][y];
                add(penis[mex][y], dp[u][mex][mex+y]);
            }
        }
        for (int mex = 1; mex <= subt[u]; ++mex) {
            for (int use = mex; use <= subt[u]; ++use) {
                add(dp[u][mex][use], penis[mex-1][use-mex]);
            }
        }
    };
    dfs(dfs, 0, 0);
    int ans = 0;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            add(ans, dp[0][i][j]);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= subt[i]; ++j) {
            for (int k = 0; k <= subt[i]; ++k) {
                dp[i][j][k] = 0;
            }
        }
    }
    cout << ans << endl;
}

int32_t main() {_
    int t; cin >> t;
    while (t--) solve();
}
