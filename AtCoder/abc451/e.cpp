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
    int n; cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) cin >> a[i][j], a[j][i] = a[i][j];
    // a[i][j] = h[i] + h[j] - h[f(i, j)]
    vector<ii> edg;
    vector<int> vis(n); vis[0] = 1;
    priority_queue<iii, vector<iii>, greater<>> pq;
    for (int i = 1; i < n; ++i) {
        pq.push({a[0][i], i, 0});
    }
    for (int i = 0; i < n-1; ++i) {
        while (true) {
            auto [d, v, u] = pq.top(); pq.pop();
            if (vis[v]) continue;
            edg.pb({u, v});
            vis[v] = true;
            for (int j = 0; j < n; ++j) {
                if (!vis[j]) pq.push({a[v][j], j, v});
            }
            break;
        }
    }
    vector<vector<ii>> g(n);
    for (auto [u, v] : edg) {
        g[u].pb({v, a[u][v]});
        g[v].pb({u, a[u][v]});
    }
    auto get = [&] (int src) {
        vector<int> dist(n, inf); dist[src] = 0;
        queue<int> q; q.push(src);
        while (!q.empty()) {
            auto u = q.front(); q.pop();
            for (auto [v, w] : g[u]) {
                if (dist[v] == inf) dist[v] = dist[u] + w, q.push(v);
            }
        }
        return dist;
    };
    bool ok = 1;
    for (int i = 0; i < n; ++i) ok &= (get(i) == a[i]);
    cout << (ok ? "Yes" : "No") << endl;
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
