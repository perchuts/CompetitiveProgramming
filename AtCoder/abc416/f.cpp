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

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(k+1, vector<int>(3)));
    auto merge = [&] (int u, int v) {
        vector<vector<int>> ndp = dp[u];
        for (int i = 0; i <= k; ++i) {
            for (int j = 0; i+j <= k; ++j) {
                ckmax(ndp[i+j][0], dp[u][i][0] + dp[v][j][2]);
                ckmax(ndp[i+j][1], dp[u][i][1] + dp[v][j][2]);
                ckmax(ndp[i+j][1], dp[u][i][0] + dp[v][j][1] + a[u]);
                ckmax(ndp[i+j][2], dp[u][i][2] + dp[v][j][2]);
            }
        }
        for (int i = 1; i <= k; ++i) {
            for (int j = 1; i+j <= k+1; ++j) {
                ckmax(ndp[i+j-1][2], dp[u][i][1] + dp[v][j][1]);
            }
        }
        for (int i = 0; i <= k; ++i) ckmax(ndp[i][2], max(ndp[i][0], ndp[i][1]));
        dp[u] = ndp;
    };
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        dp[u][1][1] = dp[u][1][2] = a[u];
        dp[u][0][1] = -1e18;
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
            merge(u, v);
        }
    };
    dfs(dfs, 0, 0);
    int ans = 0;
    for (int i = 1; i <= k; ++i) ckmax(ans, dp[0][i][2]);
    cout << ans << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
