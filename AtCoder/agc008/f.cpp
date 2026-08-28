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

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int solve(int n, vector<vector<int>> g, string s) {
    vector<int> lvl(n), h(n), h_up(n);
    vector<vector<int>> children(n);
    auto pre = [&] (auto&& self, int u, int p) -> void {
        for (auto v : g[u]) {
            if (v == p) continue;
            children[u].pb(v);
            lvl[v] = 1 + lvl[u];
            self(self, v, u);
            ckmax(h[u], 1 + h[v]);
        }
        sort(all(children[u]), [&] (int a, int b) { return h[a] > h[b]; });
    };
    pre(pre, 0, 0);
    auto pre2 = [&] (auto&& self, int u) -> void {
        for (auto v : children[u]) {
            h_up[v] = h_up[u] + 1;
            if (v != children[u][0]) ckmax(h_up[v], h[children[u][0]] + 2);
            else if (sz(children[u]) > 1) ckmax(h_up[v], h[children[u][1]] + 2);
            self(self, v);
        }
    };
    pre2(pre2, 0);
    int ans = 0;
    vector<map<int, int>> mp(n);
    auto dfs = [&] (auto&& self, int u) -> void {
        for (auto v : children[u]) {
            self(self, v);
            if (sz(mp[v]) > sz(mp[u])) swap(mp[v], mp[u]);
        }
        map<int, vector<int>> caras;
        for (auto v : children[u]) {
            for (auto [lv, w] : mp[v]) {
                if (!mp[u].count(lv)) mp[u][lv] = w;
                else if (!caras.count(lv)) caras[lv] = {w, mp[u][lv]};
                else caras[lv].pb(w);
            }
        }
        cout << "looking at u = " << u << endl;
        for (auto [lv, layer] : caras) {
            sort(all(layer), [&] (int x, int y) { return h[x] < h[y]; });
            for (int i = 1; i < sz(layer); ++i) {
                int lim = lv - lvl[u] + h[layer[i]] + 1;
                ans += lim;
                //cout << "merging " << layer[i-1] << " with " << layer[i] << " -> " << lim << endl;
            }
        }
                //cout << flush;
        if (s[u] == '1') {
            //cout << "activating " << u << " at level = " << lvl[u] << endl;
            mp[u][lvl[u]] = u;
        }
    };
    dfs(dfs, 0);
    for (auto [lv, w] : mp[0]) {
        int z = max(h[w], h_up[w]);
        //cout << "final of u = " << w << ": " << start[w] << " -> " << z << endl;
        ans += z;
    }
    ans++;
    return ans;
}

int brute(int n, vector<vector<int>> g, string s) {
    set<vector<int>> sets;
    vector<vector<int>> adj(n, vector<int>(n, inf));
    for (int i = 0; i < n; ++i) adj[i][i] = 0;
    for (int i = 0; i < n; ++i) for (auto j : g[i]) adj[i][j] = 1;
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                ckmin(adj[i][j], adj[i][k] + adj[k][j]);
            }
        }
    }
    for (int d = 0; d < n; ++d) {
        for (int u = 0; u < n; ++u) {
            if (s[u] == '0') continue;
            vector<int> list;
            for (int v = 0; v < n; ++v) {
                if (adj[u][v] <= d) list.pb(v);
            }
            sets.insert(list);
        }
    }
    return sz(sets);
}

int32_t main() {_
#ifndef gato
    int n; cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) { 
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    string s; cin >> s;
    cout << solve(n, g, s) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 60);
        vector<ii> edg;
        vector<int> p(n); iota(all(p), 0); shuffle(all(p), rng);
        string s;
        for (int i = 0; i < n; ++i) s += char('0'+rnd(1, 1));
        vector<vector<int>> g(n);
        for (int i = 1; i < n; ++i) {
            int u = p[i], v = p[rnd(0, i-1)];
            g[u].pb(v), g[v].pb(u);
            edg.pb({u, v});
        }
        int my = solve(n, g, s), ans = brute(n, g, s);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto [x, y] : edg) cout << x+1 << " " << y+1 << endl;
            cout << s << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
