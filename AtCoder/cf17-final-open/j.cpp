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
    vector<int> w(n);
    for (auto& x : w) cin >> x;
    vector<vector<ii>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v, wi; cin >> u >> v >> wi; --u, --v;
        g[u].pb({v, wi});
        g[v].pb({u, wi});
    }
    vector<ii> p(n, {-1, 0});
    vector<int> subt(n), vis(n);
    vector<vector<ii>> cs(n);
    auto dfs = [&] (auto&& self, int u, int p) -> int {
        subt[u] = 1;
        for (auto [v, wi] : g[u]) {
            if (vis[v] or v == p) continue;
            subt[u] += self(self, v, u);
        }
        return subt[u];
    };
    auto find_cen = [&] (auto&& self, int u, int p, int nn) -> int {
        for (auto [v, wi] : g[u]) { 
            if (vis[v] or v == p) continue;
            if (2 * subt[v] > nn) return self(self, v, u, nn);
        }
        return u;
    };
    int cc;
    auto compute = [&] (auto&& self, int u, int p, int tw) -> void {
        cs[cc].pb({u, tw+w[u]});
        for (auto [v, wi] : g[u]) {
            if (v == p or vis[v]) continue;
            self(self, v, u, tw+wi);
        }
    };
    auto decomp = [&] (auto&& self, int u) -> void {
        int c = find_cen(find_cen, u, u, dfs(dfs, u, u));
        vis[c] = 1, cc = c;
        compute(compute, c, c, 0);
        for (auto [v, wi] : g[c]) {
            if (vis[v] == 0) p[v] = {c, wi}, self(self, v);
        }
    };
    decomp(decomp, 0);
    vector<int> par(n), lvl(n);
    auto findp = [&] (auto&& self, int u) -> int { return par[u] = (par[u] == u ? u : self(self, par[u])); };
    auto merge = [&] (int u, int v) {
        u = findp(findp, u), v = findp(findp, v);
        if (u == v) return false;
        if (lvl[u] < lvl[v]) swap(u, v);
        par[v] = u;
        if (lvl[u] == lvl[v]) ++lvl[u];
        return true;
    };
    iota(all(par), 0);
    int comps = n, ans = 0;
    vector<ii> opt(n);
    while (comps > 1) {
        for (int i = 0; i < n; ++i) findp(findp, i), opt[i] = {1e18, -1};
        for (int c = 0; c < n; ++c) { 
            array<int, 4> opts; opts[0] = opts[2] = 1e18, opts[1] = opts[3] = -1;
            for (auto [u, cost] : cs[c]) {
                if (cost < opts[2]) {
                    if (par[u] == opts[1]) ckmin(opts[0], cost);
                    else if (par[u] == opts[3]) ckmin(opts[2], cost);
                    else if (cost <= opts[0]) opts[2] = opts[0], opts[3] = opts[1], opts[0] = cost, opts[1] = par[u];
                    else opts[2] = cost, opts[3] = par[u];
                    if (opts[0] > opts[2]) swap(opts[0], opts[2]), swap(opts[1], opts[3]);
                }
            }
            for (auto [u, cost] : cs[c]) {
                if (par[u] == opts[1]) ckmin(opt[par[u]], pair(cost + opts[2], opts[3]));
                else ckmin(opt[par[u]], pair(cost + opts[0], opts[1]));
            }
        }
        for (int i = 0; i < n; ++i) {
            if (opt[i].second == -1) continue;
            if (merge(i, opt[i].second)) {
                comps--, ans += opt[i].first;
            }
        }
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
