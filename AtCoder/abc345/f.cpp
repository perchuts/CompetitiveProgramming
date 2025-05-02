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
    int n, m, k; cin >> n >> m >> k;
    if (k&1) {
        cout << "No" << endl;
        exit(0);
    }
    vector<vector<ii>> g(n);
    vector<ii> edg(m);
    int id = 0;
    for (auto& [x, y] : edg) {
        cin >> x >> y; --x, --y;
        g[x].pb({y, id}), g[y].pb({x, id});
        id++;
    }
    vector<vector<int>> comps;
    vector<int> vis(n), mark(n);
    auto dfs = [&] (auto&& self, int u) -> void {
        comps.back().pb(u);
        vis[u] = 1;
        for (auto [v, id] : g[u]) {
            if (!vis[v]) self(self, v);
        }
    };
    for (int i = 0; i < n; ++i) { 
        if (vis[i]) continue;
        comps.pb({});
        dfs(dfs, i);
    }
    for (auto v : comps) {
        int lim = min(sz(v) / 2 * 2, k);
        for (int i = 0; i < lim; ++i) mark[v[i]] = 1;
        k -= lim;
    }
    if (k) {
        cout << "No" << endl;
        exit(0);
    }
    vector<int> ans;
    auto dfs2 = [&] (auto&& self, int u, int edg) -> int {
        vis[u] = 2;
        for (auto [v, id] : g[u]) {
            if (vis[v] == 2) continue;
            mark[u] ^= self(self, v, id);
        }
        if (mark[u]) {
            assert(edg != -1);
            ans.pb(edg+1);
            return 1;
        }
        return 0;
    };
    for (auto v : comps) dfs2(dfs2, v[0], -1);
    cout << "Yes" << endl;
    cout << sz(ans) << endl;
    for (auto x : ans) cout << x << ' ';
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
