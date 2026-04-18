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

void solve() {
    int n; cin >> n;
    vector<int> fat(2*n+1, 1), ifat(2*n+1), dp(2*n);
    vector<bool> is_cycle(2*n);
    vector<int32_t> par(2*n, -1), lvl(2*n), deg(2*n), tam(2*n), cycle, comp;
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    for (int i = 1; i <= 2*n; ++i) fat[i] = i * fat[i-1] % mod;
    ifat[2*n] = fexp(fat[2*n], mod-2);
    for (int i = 2*n-1; ~i; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
    vector<vector<int32_t>> g(2*n), gg(2*n);
    for (int i = 0; i < 2 * n; ++i) {
        int x, y; cin >> x >> y; --x, --y;
        g[x].pb(n+y), g[n+y].pb(x);
    }
    auto dfs = [&] (auto&& self, int u) -> void {
        comp.pb(u);
        for (auto v : g[u]) {
            if (par[v] == -1) lvl[v] = 1 + lvl[u], par[v] = u, self(self, v);
            else if (lvl[v] < lvl[u] and par[u] != v) {
                if (!cycle.empty()) {
                    cout << 0 << endl;
                    exit(0);
                }
                int cur = u;
                while (cur != v) is_cycle[cur] = 1, cycle.pb(cur), cur = par[cur];
                is_cycle[v] = 1, cycle.pb(v);
            }
        }
    };
    int ans = fat[2*n];
    for (int i = 0; i < n; ++i) {
        if (par[i] == -1) {
            cycle.clear(), comp.clear(), par[i] = i, dfs(dfs, i);
            if (!cycle.empty()) {
                int m = sz(comp), mc = sz(cycle), ways = 0;
                for (int w = 0, add = 1; w < 2; w++, add *= -1) {
                    for (auto x : comp) deg[x] = 0, tam[x] = dp[x] = 1, gg[x].clear();
                    auto dfs2 = [&] (auto&& self, int u, int want) -> void {
                        for (auto v : g[u]) {
                            if (want > v) {
                                gg[v].pb(u), deg[u]++;
                            }
                            if (v == want or is_cycle[v]) continue;
                            self(self, v, u);
                        }
                    };
                    for (int j = 0; j < mc; ++j) dfs2(dfs2, cycle[j], cycle[(j+add+mc)%mc]);
                    queue<int> q;
                    for (auto x : comp) if (deg[x] == 0) q.push(x);
                    int cur = fat[m];
                    while (!q.empty()) {
                        int u = q.front(); q.pop();
                        dp[u] = dp[u] * fat[tam[u]-1] % mod;
                        if (gg[u].empty()) {
                            cur = cur * dp[u] % mod * ifat[tam[u]] % mod;
                        }
                        for (auto v : gg[u]) {
                            tam[v] += tam[u];
                            dp[v] = dp[v] * dp[u] % mod;
                            dp[v] = dp[v] * ifat[tam[u]] % mod;
                            deg[v]--;
                            if (deg[v] == 0) q.push(v);
                        }
                    }
                    ways = (ways + cur) % mod;
                }
                ans = ans * ways % mod * ifat[m] % mod;
            } else {
                // vai ter uma componente com mais vertices que arestas! L SUP!!
                cout << 0 << endl;
                exit(0);
            }
        }
    }
    cout << ans << endl;
}

int32_t main() {_
#ifndef gato
    solve();
#else
    int t = 1;
    while (true) {
        int n = rnd(4, 30);
        vector<ii> cells(2*n);
        set<ii> foi;
        for (int i = 0; i < 2*n; ++i) {
            while (true){ 
                int x = rnd(0, n-1), y = rnd(0, n-1);
                if (foi.find({x, y}) == end(foi)) {
                    foi.insert({x, y});
                    cells[i] = {x, y};
                    break;
                }
            }
        }
        solve(n, cells);
    }
#endif
}
