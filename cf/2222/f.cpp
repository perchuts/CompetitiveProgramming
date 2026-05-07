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
    int n, m, q; cin >> n >> m >> q;
    vector<vector<ii>> g(n);
    vector<vector<ii>> edg(m+1);
    map<ii, int> z;
    map<ii, int> we;
    for (int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        --u, --v;
        if (u < v) swap(u, v);
        z[{u, v}]++;
        we[{u, v}] = w;
        //g[u].pb({v, w});
        //g[v].pb({u, w});
    }
    for (auto [ar, qt] : z) {
        auto [u, v] = ar;
        int w;
        if (qt == 1) {
            w = we[ar];
        } else w = m;
        g[u].pb({v, w});
        g[v].pb({u, w});
    }
    vector<int> c(q);
    for (auto& x : c) cin >> x, --x;
    sort(all(c)), c.erase(unique(all(c)), end(c));
    vector<int> vis(n);
    auto dfs = [&] (auto&& self, int u) -> void {
        vis[u] = 1;
        for (auto [v, w] : g[u]) {
            if (!vis[v]) self(self, v);
        }
    };
    dfs(dfs, c[0]);
    bool ok = 1;
    for (auto x : c) ok &= vis[x];
    if (!ok) {
        cout << -1 << endl;
        return;
    }
    //cout << "Whatsapp" << endl;
    vector<int> par(q), lvl(q);
    iota(all(par), 0);
    int comps = q;
    auto findp = [&] (auto&& self, int u) -> int {
        return par[u] = (par[u] == u ? u : self(self, par[u]));
    };
    int ans = 0;
    auto unite = [&] (int u, int v, int w) {
        u = findp(findp, u), v = findp(findp, v);
        if (u == v) return 0LL;
        comps--;
        if (lvl[u] < lvl[v]) swap(u, v);
        par[v] = u;
        if (lvl[u] == lvl[v]) ++lvl[u];
        return w;
    };
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
