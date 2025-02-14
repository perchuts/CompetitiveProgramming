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
    for (int i = 1; i < n; ++i) {
        int u, v, c; cin >> u >> v >> c;
        --u, --v;
        g[u].pb({v, c});
        g[v].pb({u, c});
    }
    vector<int> seg(4*n), lz(4*n);
    auto push = [&] (int i, int l, int r) {
        seg[i] -= lz[i];
        if (l != r) lz[2*i] += lz[i], lz[2*i+1] += lz[i];
        lz[i] = 0;
    };
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int y, int k) -> void {
        push(i, l, r);
        if (r < x or y < l) return;
        if (x <= l and r <= y) {
            lz[i] += k;
            push(i, l, r);
            return;
        }

        int md = (l + r) / 2;
        self(self, 2*i, l, md, x, y, k);
        self(self, 2*i+1, md+1, r, x, y, k);
        seg[i] = max(seg[2*i+1], seg[2*i]);
    };
    vector<int> tin(n), tout(n), par(n), who(n);
    vector<ii> edg(n);
    int t = 0;
    auto dfs = [&] (auto&& self, int u, int p, int cost) -> void {
        edg[u] = {p, cost};
        par[u] = u;
        tin[u] = t;
        who[t] = u;
        for (auto [v, c] : g[u]) {
            if (v == p) continue;
            self(self, v, u, c);
        }
        tout[u] = t++;
        upd(upd, 1, 0, n-1, tin[u], tout[u], -cost);
    };
    dfs(dfs, 0, 0, 0);
    int ans = 0;
    auto go = [&] (auto&& self, int u) -> int {
        if (par[u] == u) {
            upd(upd, 1, 0, n-1, tin[u], tout[u], edg[u].second);
            par[u] = edg[u].first;
            return par[u];
        }
        return par[u] = self(self, par[u]);
    };
    for (int i = 0; i < n; ++i) {
        int eu = 1, l = 0, r = n-1;
        while (l != r) {
            int md = (l+r)/2;
            push(eu, l, r);
            push(2*eu, l, md);
            push(2*eu+1, md+1, r);
            if (seg[2*eu] >= seg[2*eu+1]) eu = 2*eu, r = md;
            else l = md+1, eu = 2*eu+1;
        }
        ans += seg[eu];
        int cur = who[l];
        while (cur) cur = go(go, cur);
        cout << 2*ans << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
