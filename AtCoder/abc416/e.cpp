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
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n, vector<int>(n, 1e18));
    for (int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w; --u, --v;
        ckmin(adj[u][v], w);
        ckmin(adj[v][u], w);
    }
    int k, t; cin >> k >> t;
    vector<int> sexo, foi(n);
    for (int i = 0; i < k; ++i) {
        int x; cin >> x;
        foi[x-1] = 1;
        sexo.pb(x-1);
    }

    for (auto x : sexo) for (auto y : sexo) ckmin(adj[x][y], t);

    for (int i = 0; i < n; ++i) adj[i][i] = 0;

    for (int k = 0; k < n; ++k) 
        for (int i = 0; i < n; ++i) 
            for (int j = 0; j < n; ++j) 
                ckmin(adj[i][j], adj[i][k] + adj[k][j]);
    int q; cin >> q;
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int u, v, w; cin >> u >> v >> w; --u, --v;
            ckmin(adj[u][v], w), ckmin(adj[v][u], w);
            for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) ckmin(adj[i][j], min(adj[i][u] + adj[v][j], adj[j][u] + adj[i][v]) + w);
        } else if (op == 2) {
            int x; cin >> x; --x;
            if (foi[x]) continue;
            foi[x] = 1;
            for (auto y : sexo) ckmin(adj[x][y], t);
            vector<int> dist_aero(n, 1e18);
            for (int i = 0; i < n; ++i) {
                if (foi[i]) dist_aero[i] = 0;
                else for (int j = 0; j < n; ++j) if (foi[j]) ckmin(dist_aero[i], adj[i][j]);
            }
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    ckmin(adj[i][j], min(dist_aero[i] + adj[x][j], dist_aero[j] + adj[x][i]) + t);
                }
            }
            sexo.pb(x);
        } else {
            int ans = 0;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (adj[i][j] < inf * n) ans += adj[i][j];
                }
            }
            cout << ans << endl;
        }
    }
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

