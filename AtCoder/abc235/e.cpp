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
    int n, m, q; cin >> n >> m >> q;
    vector<tuple<int, int, int, int>> edg;
    for (int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        --u, --v;
        edg.pb({w, u, v, -1});
    }
    for (int i = 0; i < q; ++i) {
        int u, v, w; cin >> u >> v >> w;
        --u, --v;
        edg.pb({w, u, v, i});
    }
    sort(all(edg));
    vector<int> ans(q), par(n), lvl(n);
    auto findp = [&] (auto&& self, int u) -> int {
        return par[u] = (u == par[u] ? u : self(self, par[u]));
    };
    iota(all(par), 0);
    auto unite = [&] (int u, int v, bool use) {
        u = findp(findp, u), v = findp(findp, v);
        if (u == v) return false;
        if (use == false) return true;
        if (lvl[u] < lvl[v]) swap(u, v);
        par[v] = u;
        if (lvl[u] == lvl[v]) lvl[u]++;
        return true;
    };
    for (auto [w, u, v, tipo] : edg) {
        if (tipo == -1) unite(u, v, true);
        else ans[tipo] = unite(u, v, false);
    }
    for (auto x : ans) cout << (x ? "Yes" : "No") << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
