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
    int n, m, a, b; cin >> n >> m >> a >> b; --a, --b;
    vector<vector<int>> adj(n, vector<int>(n, inf));
    for (int i = 0; i < n; ++i) adj[i][i] = 0;
    vector<iii> edg;
    for (int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w; --u, --v;
        edg.pb({u, v, w});
        adj[u][v] = adj[v][u] = w;
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                ckmin(adj[i][j], adj[i][k] + adj[k][j]);
            }
        }
    }
    int ans = 0;
    for (auto [u, v, w] : edg) {
        int d = min(adj[a][u] + adj[v][b], adj[a][v] + adj[u][b]) + w;
        if (d != adj[a][b]) ans += w;
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
