#include "closing.h"
#include <bits/stdc++.h>
#define pb push_back
#define int ll
using namespace std;

using ll = long long;
using ii = pair<int, int>;


int32_t max_score(int32_t N, int32_t X, int32_t Y, long long K,
              std::vector<int32_t> U, std::vector<int32_t> V, std::vector<int32_t> W)
{
    ll n = N, x = X, y = Y, k = K;
    vector<vector<pair<ll, ll>>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u = U[i], v = V[i], w = W[i];
        g[u].pb({v, w});
        g[v].pb({u, w});
    }
    vector<array<ll, 2>> dist(n);
    ll aa = 0;
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        for (auto [v, w] : g[u]) {
            if (v == p) continue;
            dist[v][aa] = dist[u][aa] + w;
            self(self, v, u);
        }
    };
    dfs(dfs, x, x);
    aa = 1;
    dfs(dfs, y, y);
    vector<int> m1, m2;
    for (int i = 1; i < (1 << n); ++i) {
        int foi = 0;
        auto expl = [&] (auto&& self, int u, int p) -> void {
            foi++;
            for (auto [v, w] : g[u]) {
                if (v == p) continue;
                if (i >> v & 1) self(self, v, u);
            }
        };
        if (i >> x & 1) expl(expl, x, x);
        if (foi == __builtin_popcount(i)) m1.pb(i);
    }
    for (int i = 1; i < (1 << n); ++i) {
        int foi = 0;
        auto expl = [&] (auto&& self, int u, int p) -> void {
            foi++;
            for (auto [v, w] : g[u]) {
                if (v == p) continue;
                if (i >> v & 1) self(self, v, u);
            }
        };
        if (i >> y & 1) expl(expl, y, y);
        if (foi == __builtin_popcount(i)) m2.pb(i);
    }
    int ans = 0;
    for (auto a : m1) {
        for (auto b : m2) {
            int cost = 0, t = 0;
            for (int i = 0; i < n; ++i) {
                int z = 0;
                if (a >> i & 1) z = max(z, dist[i][0]), t++;
                if (b >> i & 1) z = max(z, dist[i][1]), t++;
                cost += z;
            }
            if (cost <= k) ans = max(ans, t);
        }
    }
    return ans;
}
