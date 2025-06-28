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
    vector<vector<ii>> g(n);
    vector<iii> edg(n-1);
    for (auto& [u, v, w] : edg) {
        cin >> u >> v >> w; --u, --v;
        g[u].pb({v, w}), g[v].pb({u, w});
    }
    vector<int> in(n), out(n), lvl(n+1), bit(2*n+1);
    vector<vector<int>> par(n+1, vector<int>(18, n));
    auto insert = [&] (int x, int k) { while (x <= 2*n) bit[x] += k, x += x & (-x); };
    auto query = [&] (int x) {
        int ans = 0;
        while (x) ans += bit[x], x -= x & (-x);
        return ans;
    };
    int t = 1;
    auto pre = [&] (auto&& self, int u, int p, int w) -> void {
        in[u] = t++, par[u][0] = p, lvl[u] = lvl[p]+1;
        //cout << "+" << u << " ";
        for (int i = 1; i < 18; ++i) par[u][i] = par[par[u][i-1]][i-1];
        insert(in[u], w);
        for (auto [v, w2] : g[u]) {
            if (v == p) continue;
            self(self, v, u, w2);
        }
        //cout << "-" << u << " ";
        out[u] = t++;
        insert(out[u], -w);
    };
    pre(pre, 0, n, 0);
    auto lca = [&] (int u, int v) {
        if (lvl[u] < lvl[v]) swap(u, v);
        for (int i = 17; ~i; --i) {
            if (lvl[par[u][i]] >= lvl[v]) u = par[u][i];
        }
        if (u == v) return u;
        for (int i = 17; ~i; --i) {
            if (par[u][i] != par[v][i]) u = par[u][i], v = par[v][i];
        }
        return par[u][0];
    };
    int q; cin >> q;
    cout << endl;
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int i, w2; cin >> i >> w2; --i;
            auto& [u, v, w] = edg[i];
            if (lvl[u] < lvl[v]) swap(u, v);
            insert(in[u], w2-w), insert(out[u], w-w2);
            w = w2;
        } else {
            int u, v; cin >> u >> v; --u, --v;
            int l = lca(u, v);
            cout << query(in[u]) + query(in[v]) - 2 * query(in[l]) << endl;
        }
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
