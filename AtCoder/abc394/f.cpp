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
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb(v);
        g[v].pb(u);
    }
    vector<int> dp1(n);
    vector<vector<ii>> lista(n);
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        vector<int> manos;
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
            manos.pb(dp1[v]);
            lista[u].pb({dp1[v], v});
        }
        sort(rbegin(manos), rend(manos));
        sort(rbegin(lista[u]), rend(lista[u]));
        dp1[u] = 1;
        if (u == p) for (int i = 0; i < 4; ++i) dp1[u] += manos[i];
        else {
            if (sz(manos) >= 3) {
                for (int i = 0; i < 3; ++i) dp1[u] += manos[i];
            }
        }
    };
    int root = -1;
    for (int i = 0; i < n; ++i) if (sz(g[i]) >= 4) root = i;
    if (root == -1) { 
        cout << -1 << endl;
        exit(0);
    }
    dfs(dfs, root, root);
    int ans = dp1[root];
    auto dfs2 = [&] (auto&& self, int u, int p) -> void {
        if (u != p and sz(g[u]) >= 4) {
            if (sz(g[p]) >= 4) {
                int ele = 1, qnt = 0;
                for (int i = 0; qnt != 3; ++i) {
                    if (lista[p][i].second != u) ele += lista[p][i].first, qnt++;
                }
                lista[u].pb({ele, p});
            } else lista[u].pb({1, p});
            sort(rbegin(lista[u]), rend(lista[u]));
            int dp2 = 1;
            for (int j = 0; j < 4; ++j) dp2 += lista[u][j].first;
            ckmax(ans, dp2);
        }
        for (auto v : g[u]) {
            if (v != p) self(self, v, u);
        }
    };
    dfs2(dfs2, root, root);
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
