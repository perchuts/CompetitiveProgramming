#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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

void s() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    vector<int> c(n), vis(n);
    bool ok = 1;
    auto dfs = [&] (auto&& self, int u) -> void {
        vis[u] = 1;
        for (auto v : g[u]) {
            if (!vis[v]) {
                c[v] = 1 ^ c[u];
                self(self, v);
            } else ok &= (c[u] != c[v]);
        }
    };
    dfs(dfs, 0);
    if (ok) for (int i = 0; i < n-1; ++i) cout << char('0' + (c[i] == c[n-1]));
    else for (int i = 0; i < n-1; ++i) cout << 1;
    cout << endl;
}

void f() {
    int n; cin >> n;
    string s; cin >> s;
    array<vector<int>, 2> v;
    for (int i = 0; i < n-1; ++i) v[s[i]-'0'].pb(i);
    vector<ii> edg;
    if (v[0].empty()) {
        for (int j = 1; j < n; ++j) edg.pb({0, j});
        edg.pb({1, 2});
    } else {
        for (int j = 0; j < sz(v[0]); ++j) edg.pb({n-1, v[0][j]});
        for (int j = 0; j < sz(v[1]); ++j) edg.pb({v[0][0], v[1][j]});
    }
    cout << sz(edg) << endl;
    for (auto [x, y] : edg) cout << x+1 << " " << y+1 << endl;
}

int32_t main() {_
    string S; cin >> S;
    int t; cin >> t;
    while (t--) {
        if (S[0] == 'f') f();
        else s();
    }
#ifndef gato
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
