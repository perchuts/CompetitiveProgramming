#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
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

bool solve(int n, vector<int> p) {
    vector<vector<int>> g(n);
    for (int i = 0; i < n; ++i) {
        g[p[i]].pb(i);
    }
    vector<int> vis(n);
    int cur = 0;
    while (vis[cur] == 0) vis[cur] = 1, cur = p[cur];
    vector<int> cycle, is_cycle(n);
    while (vis[cur] == 1) cycle.pb(cur), is_cycle[cur] = 1, vis[cur] = 2, cur = p[cur];
    const int MX = 18;
    vector<int> dp(n), z(MX);
    if (sz(cycle) % 2 == 0) return 1;
    // eh possivel o mex desse cara ser <= X?
    //
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        for (auto v : g[u]) {
            if (v == p or is_cycle[v]) continue;
            self(self, v, u);
        }
        for (int i = 0; i < MX; ++i) z[i] = 0;
        for (auto v : g[u]) {
            if (v == p or is_cycle[v]) continue;
            z[dp[v]] = 1;
        }
        for (int i = 0; ; ++i) {
            if (z[i] == 0) {
                dp[u] = i; break;
            }
        }
    };
    for (auto x : cycle) dfs(dfs, x, x);
    bool ok = 1;
    for (auto x : cycle) ok &= (dp[x] == dp[cycle[0]]);
    return ok ^ 1;
}

bool brute(int n, vector<int> p) {
    vector<vector<int>> g(n);
    for (int i = 0; i < n; ++i) g[p[i]].pb(i);
    vector<int> a(n);
    auto go = [&] (auto&& self, int i) {
        if (i == n) {
            bool ok = 1;
            for (int j = 0; j < n; ++j) {
                int t = 0;
                for (auto w : g[j]) {
                    ok &= (a[w] != a[j]);
                    if (a[w] < a[j]) t |= (1 << a[w]);
                }
                ok &= (t == (1 << a[j]) - 1);
            }
            return ok;
        }
        for (int j = 0; j < 4; ++j) {
            a[i] = j;
            if (self(self, i+1)) return true;
        }
        return false;
    };
    return go(go, 0);
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    int n; cin >> n;
    vector<int> p(n);
    for (auto& x : p) cin >> x, --x;
    cout << (solve(n, p) ? "POSSIBLE" : "IMPOSSIBLE") << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 14);
        vector<int> p(n);
        for (int i = 1; i < n; ++i) p[i] = rnd(0, i-1);
        p[0] = rnd(1, n-1);
        bool my = solve(n, p);
        bool ans = brute(n, p);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : p )cout << x + 1<< " ";
            cout << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
