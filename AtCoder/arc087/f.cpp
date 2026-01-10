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
    int n; cin >> n;
    vector<vector<int>> g(n);
    vector<int> subt(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v;
        --u, --v; g[u].pb(v), g[v].pb(u);
    }
    auto dfs = [&] (auto&& self, int u, int p) -> int {
        subt[u] = 1;
        for (auto v : g[u]) {
            if (v == p) continue;
            subt[u] += self(self, v, u);
        }
        return subt[u];
    };
    dfs(dfs, 0, 0);
    auto find_cen = [&] (auto&& self, int u, int p) -> int {
        for (auto v : g[u]) {
            if (v == p) continue;
            if (2 * subt[v] > n) return self(self, v, u);
        }
        return u;
    };
    int cen = find_cen(find_cen, 0, 0);
    // temos o centroide
    vector<int> tams;
    dfs(dfs, cen, cen);
    for (auto v : g[cen]) tams.pb(subt[v]);
    vector<int> fat(n+1, 1);
    for (int i = 1; i <= n; ++i) fat[i] = i * fat[i-1] % mod;
    sort(all(tams));
    if (tams.back() * 2 == n) {
        cout << (fat[n/2] * fat[n/2]) % mod << endl;
        exit(0);
    }
    vector<vector<int>> dps;
    for (auto tam : tams) {
        vector<int> dp(1, 1);
        for (int i = 1; i <= tam; ++i) {
            vector<int> ndp(i+1);
            // dp[j] = quantos pares ruins existem.
            
            for (int j = 0; j <= i; ++j) {
                // posso ter feito porra nenhuma com esse cara
                if (j != i) ndp[j] = dp[j];
                // posso ter feito o L por tras ou pela frente
                if (j) ndp[j] = (ndp[j] + 2 * dp[j-1] * (i - j) + dp[j-1]) % mod;
                // posso fazer o L duplo
                // i-1 - j + 2
                // i - j + 1
                if (j > 1) ndp[j] = (ndp[j] + dp[j-2] * (i - j + 1) * (i - j + 1)) % mod;
            }
            swap(dp, ndp);
        }
        dps.pb(dp);
    }
    vector<int> dp(1, 1);
    for (auto dp2 : dps) {
        vector<int> ndp(sz(dp) + sz(dp2) - 1);
        for (int i = 0; i < sz(dp); ++i) {
            for (int j = 0; j < sz(dp2); ++j) {
                ndp[i+j] = (ndp[i+j] + dp[i] * dp2[j]) % mod;
            }
        }
        swap(dp, ndp);
    }
    // [3][2]: 3 * 2 (self loop, P2) + 3 (self loop, self loop) + 3 (ciclo) + 3 * 2 (P3)
    // [3][3]: 3 (ciclo, self loop) + 1 (self loop) + 6 (ciclo)
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        // completar agora!
        int tot = dp[i] * fat[n-i] % mod;
        if (i&1) ans = (ans + mod - tot) % mod;
        else ans = (ans + tot) % mod;
    }
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
