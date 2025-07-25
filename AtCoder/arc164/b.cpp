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
    vector<ii> edg(m);
    for (auto& [x, y] : edg) cin >> x >> y, --x, -- y;
    vector<int> c(n), comp(n, -1);
    for (auto& x : c) cin >> x;
    vector<vector<int>> g(n);
    for (auto [x, y] : edg) {
        if (c[x] != c[y]) g[x].pb(y), g[y].pb(x);
    }
    auto dfs = [&] (auto&& self, int u, int src) -> void {
        comp[u] = src;
        for (auto v : g[u]) {
            if (comp[v] != -1) continue;
            self(self, v, src);
        }
    };
    for (int i = 0; i < n; ++i) if (comp[i] == -1) dfs(dfs, i, i);
    for (auto [x, y] : edg) {
        if (c[x] == c[y] and comp[x] == comp[y]) {
            cout << "Yes" << endl;
            exit(0);
        }
    }
    cout << "No" << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
