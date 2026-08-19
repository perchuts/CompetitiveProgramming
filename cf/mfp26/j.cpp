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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve() {
    int n, k; cin >> n >> k;
    vector<iii> edg;
    int ans = 2 * k;
    for (int i = 0; i < n-1; ++i) {
        int u, v, w; cin >> u >> v >> w; --u, --v;
        edg.pb({u, v, w});
    }
    auto get = [&] (vector<iii> e) {
        vector<vector<ii>> g(n);
        for (auto [u, v, w] : e) {
            g[u].pb({v, w});
            g[v].pb({u, w});
        }
        vector<int> dist(n);
        int vis = 0;
        auto dfs = [&] (auto&& self, int u, int p) -> void {
            vis++;
            for (auto [v, w] : g[u]) {
                if (v == p) continue;
                dist[v] = w + dist[u];
                self(self, v, u);
            }
        };
        dfs(dfs, 0, 0);
        assert(vis == n);
        int opt = 1;
        for (int i = 2; i < n; ++i) if (dist[i] > dist[opt]) opt = i;
        dist[opt] = 0;
        dfs(dfs, opt, opt);
        return *max_element(all(dist));
    };
    ckmin(ans, get(edg));
    for (int i = 0; i < n-1; ++i) {
        vector<int> comp(n), dist(n), par(n), wp(n);
        vector<vector<ii>> g(n);
        for (int j = 0; j < n-1; ++j) {
            if (i == j) continue;
            auto [u, v, w] = edg[j];
            g[u].pb({v, w}), g[v].pb({u, w});
        }
        auto dfs = [&] (auto&& self, int u, int p, int color) -> void {
            comp[u] = color;
            par[u] = p;
            for (auto [v, w] : g[u]) {
                if (v == p) continue;
                dist[v] = w + dist[u];
                wp[v] = w;
                self(self, v, u, color);
            }
        };
        auto [u, v, w] = edg[i];
        // cor[u] = 0
        // cor[v] = 1
        dfs(dfs, u, u, 0), dfs(dfs, v, v, 1);
        int cur_ans = *max_element(all(dist));
        vector<vector<int>> cen(2);
        for (int z = 0; z < 2; ++z) {
            int diam = (z ? v : u);
            for (int j = 0; j < n; ++j) {
                if (comp[j] == z and dist[j] > dist[diam]) diam = j;
            }
            dist[diam] = wp[diam] = 0;
            dfs(dfs, diam, diam, z);
            int other = diam;
            for (int j = 0; j < n; ++j) {
                if (comp[j] == z and dist[j] > dist[other]) other = j;
            }
            int d1 = dist[other], d2 = 0;

            while (other != diam and d2 + wp[other] <= d1 - wp[other]) {
                d2 += wp[other], d1 -= wp[other];
                other = par[other];
            }
            cen[z].pb(other);
            if (par[other] != other) cen[z].pb(par[other]);
        }
        for (auto c1 : cen[0]) {
            for (auto c2 : cen[1]) {
                auto e2 = edg;
                e2.erase(begin(e2)+i);
                e2.pb({c1, c2, k});
                ckmin(ans, max(cur_ans, get(e2)));
            }
        } 
    }
    cout << ans << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
