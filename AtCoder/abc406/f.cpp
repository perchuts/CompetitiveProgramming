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
    int n; cin >> n;
    vector<vector<int>> g(n);
    vector<ii> edg;
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        edg.pb({u, v});
        g[u].pb(v), g[v].pb(u);
    }
    vector<int> tin(n), tout(n), seg(4*n), lvl(n);
    int t = -1;
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        tin[u] = ++t;
        lvl[u] = lvl[p] + 1;
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
        }
        tout[u] = t;
    };
    dfs(dfs, 0, 0);
    int sum = 0;
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int k) -> void {
        if (i == 1) sum += k;
        if (l == r) {
            seg[i] += k;
            return;
        }
        int md = (l + r) / 2;
        if (x <= md) self(self, 2*i, l, md, x, k);
        else self(self, 2*i+1, md+1, r, x, k);
        seg[i] = seg[2*i] + seg[2*i+1];
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> int {
        if (r < x or y < l) return 0LL;
        if (x <= l and r <= y) return seg[i];
        int md = (l + r) / 2;
        return self(self, 2*i, l, md, x, y) + self(self, 2*i+1, md+1, r, x, y);
    };
    for (int i = 0; i < n; ++i) upd(upd, 1, 0, n-1, i, 1);
    int q; cin >> q;
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int x, y; cin >> x >> y;
            --x;
            upd(upd, 1, 0, n-1, tin[x], y);
        } else {
            int e; cin >> e;
            --e;
            auto [x, y] = edg[e];
            if (lvl[x] < lvl[y]) swap(x, y);
            int want = query(query, 1, 0, n-1, tin[x], tout[x]);
            cout << abs(want-(sum-want)) << endl;
        }
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
