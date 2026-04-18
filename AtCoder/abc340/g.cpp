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
    vector<int> c(n);
    for (auto& x : c) cin >> x, --x;
    vector<vector<int>> g(n);
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    vector<int> in(n), out(n), qq(n, 1);
    vector<vector<int>> bichos(n), sexo(n), dp(n, vector<int>(1));
    int ans = 0, tt = 0;
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        in[u] = ++tt;
        int tot = 1;
        sexo[c[u]].pb(u);
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
            ans = (ans + qq[u] + mod - 1) % mod;
            tot = tot * qq[u] % mod;
            qq[u] = 1;
       }
        out[u] = tt;
        sexo[c[u]].pop_back();
        // deixar ele nao me usar at all
        if (!sexo[c[u]].empty()) qq[sexo[c[u]].back()] = qq[sexo[c[u]].back()] * (tot + 1) % mod;
        int i = sz(dp[c[u]]);
        bichos[c[u]].pb(u);
        int l = 1, r = i-1, tr = 0;
        while (l <= r) {
            int md = l + (r-l+1) / 2;
            if (out[bichos[c[u]][md-1]] < in[bichos[c[u]][i-1]]) tr = md, l = md+1;
            else r = md-1;
        }
        dp[c[u]].pb(dp[c[u]].back() + dp[c[u]][tr] + 1);
        if (dp[c[u]].back() >= mod) dp[c[u]].back() -= mod;
    };
    dfs(dfs, rnd(0, n-1), -1);
    for (int i = 0; i < n; ++i) ans += dp[i].back();
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
