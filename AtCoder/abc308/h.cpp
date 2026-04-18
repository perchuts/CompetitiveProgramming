#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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
    int n, m; cin >> n >> m;
    vector<vector<ii>> g(n);
    vector<vector<int>> a(n, vector<int>(n, inf/2));
    for (int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w; --u, --v;
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
    cout << (ans == inf ? -1 : ans) << endl;
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
