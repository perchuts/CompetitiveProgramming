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
    vector<iii> edg(m);
    for (auto& [x, y, z] : edg) cin >> y >> z >> x, --y, --z;
    vector<int> par(n), lvl(n);
    auto reset = [&] () {
        iota(all(par), 0);
        lvl = vector<int>(n, 1);
    };
    auto findp = [&] (auto&& self, int u) -> int {
        return par[u] = (par[u] == u ? u : self(self, par[u]));
    };
    auto merge = [&] (int u, int v) {
        u = findp(findp, u), v = findp(findp, v);
        if (u == v) return false;
        if (lvl[u] < lvl[v]) swap(u, v);
        par[v] = u;
        lvl[u] += lvl[v];
        return true;
    };
    reset();
    vector<int> ord(m); iota(all(ord), 0);
    sort(all(ord), [&] (int x, int y) { return edg[x] < edg[y]; });
    vector<iii> tree;
    for (int i : ord) {
        auto [w, u, v] = edg[i];
        if (merge(u, v)) tree.pb({w, u, v});
    }
    reset();
    vector<array<int, 4>> ev;
    for (auto [w, u, v] : tree) ev.pb({w, m, u, v});
    int id = 0;
    for (auto [w, u, v] : edg) ev.pb({w, id++, u, v});
    sort(all(ev));
    vector<int> ans(m);
    for (auto [w, tt, u, v] : ev) {
        if (tt == m) merge(u, v);
        else ans[tt] = (findp(findp, u) != findp(findp, v));
    }
    for (auto x : ans) cout << (x ? "YES" : "NO") << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
