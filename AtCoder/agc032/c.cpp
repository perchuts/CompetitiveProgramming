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
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    for (int i = 0; i < n; ++i) {
        if (sz(g[i]) & 1) {
            cout << "No" << endl;
            exit(0);
        }
    }
    vector<int> bichos;
    for (int i = 0; i < n; ++i) {
        if (sz(g[i]) > 4) {
            cout << "Yes" << endl;
            exit(0);
        }
        if (sz(g[i]) == 4) bichos.pb(i);
    }
    if (sz(bichos) <= 1) {
        cout << "No" << endl;
        exit(0);
    }
    if (sz(bichos) > 2) {
        cout << "Yes" << endl;
        exit(0);
    }
    int a = bichos[0], b = bichos[1];
    vector<int> vis(n);
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        vis[u] = 1;
        for (auto v : g[u]) {
            if (v == p or v == b) continue;
            if (vis[v]) {
                cout << "Yes" << endl;
                exit(0);
            }
            self(self, v, u);
        }
    };
    dfs(dfs, a, a);
    cout << "No" << endl;
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
