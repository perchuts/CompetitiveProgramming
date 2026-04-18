#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
//#define gato

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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int correct(int n, int m, vector<iii> edg) {
    vector<vector<ii>> g(n);
    vector<vector<int>> a(n, vector<int>(n, inf/2));
    for (auto [u, v, w] : edg) {
        a[u][v] = a[v][u] = w;
        g[u].pb({v, w});
        g[v].pb({u, w});
    }
    vector<vector<vector<ii>>> opt;
    auto go = [&] (int src) -> void { 
        vector<vector<ii>> dist(n, vector<ii>(3, pair(inf, -1)));
        dist[src][0] = {0, 0};
        priority_queue<iii, vector<iii>, greater<>> pq;
        pq.push({0, src, 0});
        while (!pq.empty()) {
            auto [d, u, s] = pq.top(); pq.pop();
            bool ok = 0;
            for (int t = 0; t < 3; ++t) {
                ok |= (dist[u][t] == pair(d, s));
            }
            if (!ok) continue;
            for (auto [v, w] : g[u]) {
                if (v == src) continue;
                if (u == src) s = v;
                int d2 = w + d;
                bool found = 0;
                for (int t = 0; t < 3; ++t) {
                    if (dist[v][t].second == s) {
                        found = 1;
                        if (ckmin(dist[v][t].first, d2)) {
                            pq.push({d2, v, s});
                            int tt = t;
                            while (tt and dist[v][tt-1].first > dist[v][tt].first) swap(dist[v][tt], dist[v][tt-1]), tt--;
                        }
                        break;
                    }
                }
                if (found) continue;
                for (int t = 0; t < 3; ++t) {
                    if (dist[v][t].first >= d2 and dist[v][2].first > d2) {
                        for (int w = 2; w > t; --w) dist[v][w] = dist[v][w-1];
                        pq.push({d2, v, s});
                        dist[v][t] = {d2, s};
                        break;
                    }
                }
            }
        }
        opt.pb(dist);
    };
    for (int i = 0; i < n; ++i) go(i);
    int ans = inf;
    for (int i = 0; i < n; ++i) {
        for (auto [j, w] : g[i]) {
            for (int z = 0; z < n; ++z) {
                if (z == i or z == j) continue;
                vector<int> want;
                for (int t = 0; t < 3; ++t) {
                    if (sz(want) < 2 and opt[i][z][t].second != j and opt[i][z][t].second != -1) want.pb(opt[i][z][t].first);
                }
                if (sz(want) == 2) ckmin(ans, want[0] + want[1] + w);
            }
        }
    }
    return (ans == inf ? -1 : ans);
}

int solve(int n, int m, vector<iii> edg) {
    vector<vector<int>> a(n, vector<int>(n, inf/2)), nb(n, vector<int>(n));
    vector<vector<ii>> g(n);
    for (auto [u, v, w] : edg) {
        g[u].pb({v, w});
        g[v].pb({u, w});
        a[u][v] = a[v][u] = w;
        nb[u][v] = nb[v][u] = w;
    }
    for (int i = 0; i < n; ++i) a[i][i] = 0;
    for (int k = 0; k < n; ++k) for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) ckmin(a[i][j], a[i][k] + a[k][j]);
    int ans = inf;
    for (int i = 0; i < n; ++i) {
        if (sz(g[i]) < 3) continue;
        sort(all(g[i]), [&] (ii x, ii y) { return x.second < y.second; });
        // tente bloquear uma aresta por vez
        for (int block = 0; block < 3; ++block) {
            vector<int> act_dist(n, inf/2);
            act_dist[i] = 0;
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    if (k != g[i][block].first and nb[i][k]) ckmin(act_dist[j], nb[i][k] + a[k][j]);
                }
            }
            bool flag = 0;
            if (g[i][block].first == 2 and i == 0) {
                flag = 1;
            }
            vector<vector<int>> t(n);
            for (int u = 0; u < n; ++u) {
                for (auto [v, w] : g[u]) {
                    if (u == i and v == g[i][block].first) continue;
                    if (act_dist[v] == act_dist[u] + w) t[u].pb(v);
                }
            }
            vector<int> l(n, -1);
            auto dfs = [&] (auto&& self, int u) -> void {
                for (auto v : t[u]) if (l[v] == -1)  l[v] = l[u], self(self, v);
            };
            l[i] = i;
            for (auto v : t[i]) {
                if (l[v] == -1) l[v] = v, dfs(dfs, v);
            }
            for (int u = 0; u < n; ++u) {
                if (u == i) continue;
                for (auto [v, w] : g[u]) {
                    if (v == i and u == g[i][block].first) continue;
                    if (l[v] != l[u] and min(l[v], l[u]) >= 0) {
                        if (v == i and l[u] == u) continue;
                        ckmin(ans, act_dist[u] + act_dist[v] + w + g[i][block].second);
                    }
                }
            }
        }
    }
    return (ans == inf ? -1 : ans);
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    int n, m; cin >> n >> m;
    vector<iii> edg(m);
    for (auto& [x, y, w] : edg) cin >> x >> y >> w, --x, --y;
    cout << solve(n, m, edg) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(4, 30);
        vector<iii> edg;
        for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) {
            if (rnd(0, 1)) edg.pb({i, j, rnd(1, 10)});
        }
        int m = sz(edg);
        auto my = solve(n, m, edg);
        auto ans = correct(n, m, edg);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << " " << m << endl;
            for (auto [x, y, z] : edg) cout << x + 1 << " " << y + 1 << " " << z << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
