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
    vector<vector<int>> a(n+2, vector<int>(n+2));
    for (auto& x : a) for (auto& y : x) cin >> y;
    map<int, vector<ii>> g;
    // /: x+y
    // \: x-y
    int shift = 10 * (n + 2);
    // top
    for (int i = 0; i <= n; ++i) {
        int u = 0 + i, v = 0 - (i + 1) + shift;
        int d = a[0][i+1] - a[0][i];
        g[u].pb({v, -d});
        g[v].pb({u, d});
    }
    // down
    for (int i = 0; i <= n; ++i) {
        int u = (n+1) - i + shift, v = (n+1) + (i+1);
        int d = a[n+1][i+1] - a[n+1][i];
        g[u].pb({v, -d});
        g[v].pb({u, d});
    }
    // ou seja, o custo vira distancia de manhattan/2
    //
    for (int i = 0; i <= n; ++i) {
        int u = i + 0, v = (i+1) - 0 + shift;
        int d = a[i+1][0] - a[i][0];
        g[u].pb({v, d});
        g[v].pb({u, -d});
    }
    // right
    for (int i = 0; i <= n; ++i) {
        int u = i - (n+1) + shift, v = (i+1) + (n+1);
        int d = a[i+1][n+1] - a[i][n+1];
        g[u].pb({v, d});
        g[v].pb({u, -d});
    }
    map<int, int> vis;
    auto dfs = [&] (auto&& self, int u) -> void {
        vis[u] = true;
        for (auto [v, w] : g[u]) {
            if (vis[v]) continue;
            self(self, v);
        }
    };
    for (auto [u, adj] : g) {
        for (auto [v, w] : adj) {
            if (u < v) cout << u << " " << v << endl;
        }
    }
    dfs(dfs, 0);
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
