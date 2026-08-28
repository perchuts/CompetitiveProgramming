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
    vector<int> a(n);
    vector<vector<int>> g(n);
    for (auto& x : a) cin >> x;
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    if (n == 2) {
        cout << (a[0] == a[1] ? "YES" : "NO") << endl;
        return;
    }
    vector<int> used(n);
    auto dfs = [&] (auto&& self, int u, int p) -> int {
        if (sz(g[u]) == 1) return a[u];
        int S = 0;
        vector<int> vals;
        int tot = 0, mx = 0;
        for (auto v : g[u]) {
            if (v == p) continue;
            int x = self(self, v, u);
            tot += x;
            ckmax(mx, x);
            S += a[v];
            used[u] -= used[v];
        }
        used[u] += S - a[u];
        if (used[u] < 0) {
            cout << "NO" << endl;
            exit(0);
        }
        if (min(tot-mx, tot/2) < used[u]) {
            cout << "NO" << endl;
            exit(0);
        }
        return tot - 2 * used[u];
    };
    int root = 0;
    for (int i = 1; i < n; ++i) if (sz(g[i]) > 1) root = i;
    if (dfs(dfs, root, root) == 0) {;
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
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
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
