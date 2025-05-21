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
    int n, q; cin >> n >> q;
    vector<int> c(n);
    vector<vector<int>> g(n);
    for (auto& x : c) cin >> x;
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    vector<vector<ii>> sp(n, vector<ii>(20, pair(0, inf)));
    vector<int> lvl(n), sexo(n, inf);
    auto pre = [&] (auto&& self, int u, int p) -> void {
        if (c[u]) sexo[u] = 0;
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
            ckmin(sexo[u], sexo[v] + 1);
        }
    };
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        ckmin(sexo[u], sexo[p]+1);
        sp[u][0] = {p, min(sexo[p], sexo[u])};
        for (int i = 1; i < 20; ++i) {
            auto [x1, y1] = sp[u][i-1];
            auto [x2, y2] = sp[x1][i-1];
            sp[u][i] = pair(x2, min(y1, y2));
        }
        for (auto v : g[u]) {
            if (v == p) continue;
            lvl[v] = lvl[u] + 1;
            self(self, v, u);
        }
    };
    pre(pre, 0, 0);
    dfs(dfs, 0, 0);
    auto get = [&] (int u, int v) {
        if (lvl[u] < lvl[v]) swap(u, v);
        int ans = inf, dd = lvl[u] + lvl[v];
        for (int i = 19; ~i; --i) {
            auto [pu, mxw] = sp[u][i];
            if (lvl[pu] >= lvl[v]) u = pu, ckmin(ans, mxw);
        }
        if (u == v) return 2*ans + dd - 2*lvl[u];
        for (int i = 19; ~i; --i) {
            auto [pu, mxw] = sp[u][i];
            auto [pv, mxw2] = sp[v][i];
            if (pu != pv) u = pu, v = pv, ckmin(ans, min(mxw, mxw2));
        }
        return 2*min(ans, min(sp[u][0].second, sp[v][0].second)) + dd - 2 * lvl[sp[u][0].first];
    };
    while (q--) {
        int u, v; cin >> u >> v; --u, --v;
        if (u == v) cout << 2 * sexo[u] << endl;
        else cout << get(u, v) << endl;
        
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
