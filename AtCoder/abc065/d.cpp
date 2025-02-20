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
    vector<ii> v(n);
    for (auto& [x, y] : v) cin >> x >> y;
    vector<int> par(n), lvl(n);
    iota(all(par), 0);
    auto findp = [&] (auto&& self, int u) -> int {
        return par[u] = (par[u] == u ? u : self(self, par[u]));
    };
    vector<vector<int>> comps(n);
    for (int i = 0; i < n; ++i) comps[i].pb(i);
    auto unite = [&] (int u, int v) {
        u = findp(findp, u), v = findp(findp, v);
        if (u == v) return false;
        if (lvl[u] < lvl[v]) swap(u, v);
        par[v] = u;
        for (auto x : comps[v]) comps[u].pb(x);
        if (lvl[u] == lvl[v]) lvl[u]++;
        return true;
    };
    int cost = 0;
    set<ii> mx, my;
    for (int i = 0; i < n; ++i) mx.insert({v[i].first, i}), my.insert({v[i].second, i});
    while (true) {
        bool ok = 1;
        for (int i = 0; i < n; ++i) ok &= (findp(findp, i) == findp(findp, 0));
        if (ok) break;
        vector<iii> unir;
        for (int i = 0; i < n; ++i) {
            if (par[i] != i) continue;
            for (auto j : comps[i]) mx.erase({v[j].first, j}), my.erase({v[j].second, j});
            int best = 1e18;
            ii edg = {-1, -1};
            for (auto j : comps[i]) {
                auto it = mx.lower_bound({v[j].first, -inf});
                if (it != end(mx) and ckmin(best, (it->first)-v[j].first)) edg = {j, it->second};
                if (it != begin(mx)) {
                    it = prev(it);
                    if (ckmin(best, -(it->first)+v[j].first)) edg = {j, it->second};
                }
                auto it2 = my.lower_bound({v[j].second, -inf});
                if (it2 != end(my) and ckmin(best, (it2->first)-v[j].second)) edg = {j, it2->second};
                if (it2 != begin(my)) {
                    it2 = prev(it2);
                    if (ckmin(best, -(it2->first)+v[j].second)) edg = {j, it2->second};
                }
            }
            unir.pb({edg.first, edg.second, best});
            for (auto j : comps[i]) mx.insert({v[j].first, j}), my.insert({v[j].second, j});
        }
        for (auto [x, y, z] : unir) if (unite(x, y)) cost += z;
    }
    cout << cost << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
