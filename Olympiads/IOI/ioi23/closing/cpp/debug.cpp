#include "closing.h"
#include <bits/stdc++.h>
#define pb push_back
#define int ll
using namespace std;

using ll = long long;
using ii = pair<int, int>;

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}


int32_t max_score(int32_t N, int32_t X, int32_t Y, long long K,
              std::vector<int32_t> U, std::vector<int32_t> V, std::vector<int32_t> W)
{
    int n = N, x = X, y = Y, k = K;
    vector<vector<ii>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u = U[i], v = V[i], w = W[i];
        g[u].pb({v, w});
        g[v].pb({u, w});
    }
    vector<array<int, 2>> dist(n);
    int aa = 0;
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
    // brute force intersection
    int ans = 0;
    vector<ii> opcoes;
    int S = 0;
    for (int i = 0; i <= x; ++i) {
        int sc = S;
        for (int j = 0; j <= n-1-y; ++j) {
            if (sc > K) break;
            opcoes.pb({sc, i+j});
            if (j != n-1-y) sc += dist[y+j+1][1];
        }
        if (i != x) S += dist[x-1-i][0];
    }
    sort(begin(opcoes), end(opcoes));

    {
        vector<ii> o2 = {opcoes[0]};
        for (int i = 1; i < (int)opcoes.size(); ++i) {
            if (opcoes[i].second > o2.back().second) o2.pb(opcoes[i]);
        }
        swap(o2, opcoes);
    }
    //for (auto [x, y] : opcoes) cout << x << " " << y << endl;

    S = 0;

    // no intersection
    for (int i = x; i < y; ++i) {
        S += dist[i][0];
        int sc = S;
        for (int j = y; j > i; --j) {
            sc += dist[j][1];
            if (sc > k) break;
            int w = upper_bound(begin(opcoes), end(opcoes), pair(k-sc, n+6969)) - begin(opcoes) - 1;
            ans = max(ans, (i-x+1) + (y-j+1) + opcoes[w].second);
        }
    }

    vector<array<int, 2>> ps(n);
    for (int i = 1; i < n; ++i) ps[i][0] = ps[i-1][0] + dist[i][0], ps[i][1] = ps[i-1][1] + dist[i][1];

    auto get = [&] (int i, int l, int r) {
        if (r < l) return 0LL;
        return ps[r][i] - (l == 0 ? 0 : ps[l-1][i]);
    };

    for (int l = 0; l <= y; ++l) {
        int meio = 0;
        for (int r = l; r < n; ++r) {
            meio += max(dist[r][0], dist[r][1]);
            if (meio > k) break;
            if (r < x) continue;
            int need = meio;
            need += get(0, x, l-1);
            need += get(1, r+1, y);
            if (need > k) continue;
            int p1 = min(l, x);
            int p2 = max(r, y);
            while (p1 > 0 and need + dist[p1-1][0] <= k) need += dist[p1-1][0], p1--;
            while (p2 < n-1 and need + dist[p2+1][1] <= k) need += dist[p2+1][1], p2++;
            ans = max(ans, r-p1+1 + p2-l+1);
            while (p1 > min(l, x)) {
                need -= dist[p1][0], p1++;
                while (p2 < n-1 and need + dist[p2+1][1] <= k) need += dist[p2+1][1], p2++;
                ans = max(ans, r-p1+1 + p2-l+1);
            }
        }
    }
    return ans;
}

int brute(int N, int X, int Y, int K, vector<int32_t> U, vector<int32_t> V, vector<int32_t> W) {
    int n = N, x = X, y = Y, k = K;
    vector<vector<ii>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u = U[i], v = V[i], w = W[i];
        g[u].pb({v, w});
        g[v].pb({u, w});
    }
    vector<array<int, 2>> dist(n);
    int aa = 0;
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
    int ans = 0;
    for (int l1 = 0; l1 <= x; ++l1) {
        for (int r1 = x; r1 < n; ++r1) {
            for (int l2 = 0; l2 <= y; ++l2) {
                for (int r2 = y; r2 < n; ++ r2) {
                    int cost = 0;
                    for (int i = 0; i < n; ++i) {
                        int z = 0;
                        if (l1 <= i and i <= r1) z = max(z, dist[i][0]);
                        if (l2 <= i and i <= r2) z = max(z, dist[i][1]);
                        cost += z;
                    }
                    if (cost <= k) ans = max(ans, r1-l1+1 + r2-l2+1);
                }
            }
        }
    }
    return ans;
}

int32_t main() {
    int t = 1;
    while (true) {
        int n = rnd(2, 10), k = rnd(0, 502);
        vector<int32_t> u(n-1), v(n-1), w(n-1);
        for (int i = 0; i < n-1; ++i) u[i] = i, v[i] = i+1, w[i] = rnd(1, 2*k+10);
        int x = rnd(0, n-2), y = rnd(x+1, n-1);
        int my = max_score(n, x, y, k, u, v, w);
        int ans = brute(n, x, y, k, u, v, w);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << " " << x << " " << y << " " << k << endl;
            for (int i = 0; i < n-1; ++i) cout << u[i] << " " << v[i] << " " << w[i] << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
}
