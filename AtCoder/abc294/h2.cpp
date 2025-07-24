
int solve_edge(int n, int m, int k, vector<ii> edg) {
    int ans = 0;
    // must do a MITM using connected components.
    // can brute force: one half of the edge subset
    // the size of the other subset (actually just parity matters)
    for (int i = 0; i < (1 << m); ++i) {
        vector<int> par(n); iota(all(par), 0);
        auto findp = [&] (auto&& self, int u) -> int {
            return par[u] = (par[u] == u ? u : self(self, par[u]));
        };
        auto merge = [&] (int u, int v) {
            u = findp(findp, u), v = findp(findp, v);
            if (u == v) return;
            par[u] = v;
        };
        int t = 0;
        for (int j = 0; j < m; ++j) {
            if (i >> j & 1) t ^= 1, merge(edg[j].first, edg[j].second);
        }
        int tot = 1;
        for (int j = 0; j < n; ++j) {
            if (findp(findp, j) == j) tot = tot * k % mod;
        }
        if (t) ans = (ans + mod - tot) % mod;
        else ans = (ans + tot) % mod;
    }
    return ans;
}

int solve_node(int n, int m, int k, vector<ii> edg) {
    vector<vector<int>> adj(n, vector<int>(n));
    for (auto [u, v] : edg) adj[u][v] = adj[v][u] = 1;
    vector<int> can(1<<n, 1);
    for (int i = 1; i < (1<<n); ++i) {
        for (int j = 0; j < n; ++j) {
            for (int w = j+1; w < n; ++w) {
                if (adj[j][w] and (i >> j & 1) and (i >> w & 1)) can[i] = false;
            }
        }
    }
    vector<vector<int>> dp(1<<n, vector<int>(min(n, k)+1));
    dp[0][0] = 1;
    for (int i = 1; i < (1<<n); ++i) {
        for (int tot = 1; tot <= min(n, k); ++tot) {
            for (int j = i; j; j = (j-1)&i) {
                if (can[j] and 2 * j > i) dp[i][tot] = (dp[i][tot] + (k-tot+1) * dp[i-j][tot-1]) % mod;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= min(n, k); ++i) ans = (ans + dp.back()[i]) % mod;
    return ans;
}
