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
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    } 
    vector<int> a(n), b(k), mask(1<<k);
    for (auto& x : a) cin >> x;
    auto subt = a;
    for (auto& x : b) cin >> x;
    for (int i = 0; i < (1 << k); ++i) for (int j = 0; j < k; ++j) if (i >> j & 1) mask[i] ^= b[j];
    vector<vector<int>> dp(n, vector<int>(1<<k));
    int ans = 0;
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        dp[u][0] = 1;
        vector<int> temp(1<<k);
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
            subt[u] ^= subt[v];
            for (int i = 0; i < (1 << k); ++i) temp[i] = 0;
            for (int i = 0; i < (1 << k); ++i) {
                for (int j = 0; j < (1 << k); ++j) {
                    temp[i^j] = (temp[i^j] + dp[u][i] * dp[v][j]) % mod; 
                }
            }
            swap(dp[u], temp);
        }
        temp = dp[u];
        for (int i = 0; i < (1 << k); ++i) {
            int z = mask[i] ^ subt[u];
            int x = 0;
            for (int j = 0; j < k; ++j) if (z == b[j]) x = (1 << j);
            if (x) {
                if (u == 0) ans = (ans + dp[u][i]) % mod;
                temp[i^x] = (temp[i^x] + dp[u][i]) % mod;
            }
        }
        dp[u] = temp;
    };
    dfs(dfs, 0, 0);
    cout << ans << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
