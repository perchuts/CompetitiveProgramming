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
        g[u].pb(v), g[v].pb(u);
    }
    vector<vector<int>> dp(n, vector<int>(2)), dp2 = dp;
    vector<vector<ii>> caras(n);
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        int s0 = 0, sm = 0;
        // dp[u][0] = nao posso usar U
        // dp[u][1]  posso usar U
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
            s0 += dp[v][1], ckmax(sm, dp[v][0] - dp[v][1] + 1);
            caras[u].pb({dp[v][0] - dp[v][1] + 1, v});
        }
        dp[u][1] = s0 + sm, dp[u][0] = s0;
    };
    dfs(dfs, 0, 0);
    int tot = dp[0][1], ans = 0;
    dp2[0] = dp[0];
    auto dfs2 = [&] (auto&& self, int u, int p) -> void {
        if (u != p) {
            int dp0 = dp2[p][0] - dp[u][1], dp1 = dp0;
            for (int i = 0; i < 2; ++i) if (caras[p][i].second != u) { ckmax(dp1, dp1 + caras[p][i].first); break; }
            caras[u].pb({dp0 - dp1 + 1, p});
            sort(rbegin(caras[u]), rend(caras[u]));
            dp2[u][0] = dp[u][0] + dp1;
        } else sort(rbegin(caras[u]), rend(caras[u]));
        ans += (dp2[u][0] == tot);
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
        }
    };
    dfs2(dfs2, 0, 0);
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
