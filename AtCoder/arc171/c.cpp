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
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    vector<vector<int>> dp(n);
    auto merge = [&] (vector<int> a, vector<int> b) {
        int x1 = sz(a), x2 = sz(b);
        vector<int> c(x1+1);
        for (int i = 0; i < x1; ++i) {
            for (int j = 0; j < x2; ++j) {
                // posso ignorar o gremio daqui
                int ways = a[i] * b[j] % mod;
                c[i] = (c[i] + ways) % mod;
                // posso fazer o gremio aqui e agora
                c[i+1] = (c[i+1] + ways * (i + 1) * (j + 1)) % mod;
            }
        }
        return c;
    };
    auto dfs = [&] (auto&& self, int u, int p) -> void { 
        dp[u] = {1};
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
            dp[u] = merge(dp[u], dp[v]);
        }
    };
    dfs(dfs, 0, 0);
    int ans = 0;
    for (auto x : dp[0]) ans += x;
    ans %= mod;
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
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
