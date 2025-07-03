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

void solve(){
    int n, m; cin >> n >> m;
    vector<int> par(2*n), val(2*n);
    vector<vector<int>> comp(2*n);
    vector<vector<int>> g(n), gr(n);
    for (int i = 0; i < 2*n; ++i) comp[i].pb(i), par[i] = i;
    auto findp = [&] (auto&& self, int u) -> int {
        return par[u] = (par[u] == u ? u : self(self, par[u]));
    };
    int ans = 0;
    auto unite = [&] (int u, int v, int c) {
        int uu = u, vv = v;
        u = findp(findp, u), v = findp(findp, v);
        if (u == v) {
            u = uu, v = vv;
            ans = gcd(ans, abs(val[u]-val[v]-c));
            return;
        }
        if (sz(comp[u]) < sz(comp[v])) swap(u, v), swap(uu, vv);
        else c *= -1;
        c = val[uu] - val[vv] + c;
        par[v] = u;
        for (auto w : comp[v]) {
            comp[u].pb(w);
            val[w] += c;
        }
    };
    vector<ii> edg(m);
    for (auto& [u, v] : edg) cin >> u >> v, --u, --v, g[u].pb(v), gr[v].pb(u);
    vector<vector<int>> can(n, vector<int>(2));
    can[0][0] = can[n-1][1] = 1;
    for (int i = 0; i < n; ++i) {
        if (!can[i][0]) continue;
        for (auto v : g[i]) can[v][0] = true;
    }
    for (int i = n-1; ~i; --i) {
        if (!can[i][1]) continue;
        for (auto v : gr[i]) can[v][1] = true;
    }
    for (auto [u, v] : edg) {
        if (can[u][0] and can[v][1]) unite(v, u+n, 0);
    }
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        if (x != -1 and can[i][0] and can[i][1]) unite(i+n, i, x);
    }
    if (findp(findp, 0) == findp(findp, 2*n-1)) ans = gcd(ans, abs(val[0]-val[2*n-1]));
    cout << (ans ? ans : -1) << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
