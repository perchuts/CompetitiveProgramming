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

void solve(){
    int n, m; cin >> n >> m;
    vector<ii> edg;
    vector<int> par(n), lvl(n);
    iota(all(par), 0);
    auto findp = [&] (auto&& self, int u) -> int { return par[u] = (par[u] == u ? u : self(self, par[u])); };
    auto unite = [&] (int u, int v) {
        u = findp(findp, u), v = findp(findp, v);
        if (u == v) return;
        if (lvl[u] < lvl[v]) swap(u, v);
        par[v] = u;
        if (lvl[u] == lvl[v]) lvl[u]++;
    };
    for (int i = 0; i < m; ++i) {
        int x, y, z; cin >> x >> y >> z;
        --x, --y;
        if (z % 2) edg.pb({x, y});
        else unite(x, y);
    }
    int ans = 0;
    vector<int> vis(n);
    vector<vector<int>> g(n);
    for (auto [x, y] : edg) g[findp(findp, x)].pb(findp(findp, y)), g[par[y]].pb(par[x]);
    auto dfs = [&] (auto&& self, int u) -> void {
        vis[u] = true;
        for (auto v : g[u]) {
            if (vis[v]) continue;
            self(self, v);
        }
    };
    for (int i = 0; i < n; ++i) {
        if (findp(findp, i) != i or vis[i]) continue;
        ans++, dfs(dfs, i);
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
