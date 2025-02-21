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
    vector<vector<ii>> g(n);
    for (int i = 0; i < m; ++i) {
        int l, r, d; cin >> l >> r >> d;
    --l, --r;
        g[l].pb({r, d});
        g[r].pb({l, -d});
    }
    vector<int> ans(n), vis(n);
    bool ok = 1;
    auto dfs = [&] (auto&& self, int u) -> void {
        vis[u] = 1;
        for (auto [v, d] : g[u]) {
            if (vis[v]) ok &= (ans[v] == ans[u] + d);
            else ans[v] = ans[u] + d, self(self, v);
        }
    };
    for (int i = 0; i < n; ++i) {
        if (!vis[i]) dfs(dfs, i);
    }
    cout << (ok ? "Yes" : "No") << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
