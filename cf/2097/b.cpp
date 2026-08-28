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
    int n, m, k; cin >> n >> m >> k;
    vector<ii> p(k+1);
    for (auto& [x, y] : p) cin >> x >> y, --x, --y;
    for (int i = 0; i < k; ++i) {
        if (abs(p[i].first-p[i+1].first) + abs(p[i].second-p[i+1].second) != 2) {
            cout << 0 << endl;
            return;
        }
    }
    vector<vector<int>> g(n*m);
    auto get = [&] (int i, int j) { return m*i+j; };
    for (int i = 0; i < k; ++i) {
        auto [x1, y1] = p[i];
        auto [x2, y2] = p[i+1];
        if (abs(x1-x2) != 1) {
            int id = get((x2+x1)/2, (y2+y1)/2);
            g[id].pb(id);
        } else {
            int a = get(x1, y2), b = get(x2, y1);
            g[a].pb(b), g[b].pb(a);
        }
    }
    int v = 0, e = 0, ans = 1, loop = 0;
    vector<int> vis(n*m);
    auto dfs = [&] (auto&& self, int u) -> void {
        vis[u] = 1;
        v++;
        for (auto w : g[u]) {
            if (w == u) loop = 1;
            if (w <= u) ++e;
            if (vis[w]) continue;
            self(self, w);
        }
    };
    for (int i = 0; i < n*m; ++i) {
        if (vis[i]) continue;
        v = e = loop = 0;
        dfs(dfs, i);
        if (e > v) {
            ans = 0;
        } else if (e == v) {
            ans = ans * (2 - loop) % mod;
        } else {
            ans = ans * v % mod;
        }
    }
    cout << ans << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
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
