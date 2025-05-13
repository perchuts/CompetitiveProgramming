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
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb({v, 0});
        g[v].pb({u, 1});
    }
    vector dp(n, vector(3, vector(3, inf)));
    auto dfs = [&] (auto&& self, int u, int p, int pdir) -> void {
        int sum = 0;
        for (auto [v, dir] : g[u]) {
            if (v == p) continue;
            self(self, v, u, dir^1);
            sum += dp[v][2][0];
            if (ckmin(dp[u][dir^1][0], dp[v][dir^1][0] - dp[v][2][0])) dp[u][dir^1][1+(dir^1)] = dp[v][dir^1][1+(dir^1)];
        }
        dp[u][2][0] = sum+1, dp[u][2][1] = dp[u][2][2] = u;
        if (ckmin(dp[u][2][0], sum + dp[u][0][0])) dp[u][2][1] = dp[u][0][1];
        if (ckmin(dp[u][2][0], sum + dp[u][1][0])) dp[u][2][2] = dp[u][1][2];
        if (ckmin(dp[u][2][0], sum + dp[u][1][0] + dp[u][2][0])) dp[u][2][1] = dp[u][0][1], dp[u][2][2] = dp[u][1][2];
    };
    dfs(dfs, 0, 0, -1);
    cout << dp[0][2][0]-1 << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
