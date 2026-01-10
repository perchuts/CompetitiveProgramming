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
    string s; cin >> s;
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb(v);
        g[v].pb(u);
    }
    vector<vector<vector<int>>> bichos(n);
    vector<vector<int>> todos_os_bichos(n);
    vector<vector<array<int, 2>>> dp(n, vector<array<int, 2>>(n));
    vector<int> ans(n), par(n);
    auto add = [&] (int& x, int y, int u = -1) {
        x += y;
        if (x >= mod) x -= mod;
        if (u != -1) {
        ans[u] += y;
        if (ans[u] >= mod) ans[u] -= mod;
        }
    };
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        bichos[u] = {{u}};
        todos_os_bichos[u] = {u};
        // only one
        add(dp[u][u][0], 1, u);
        for (auto v : g[u]) {
            if (v == p) continue;
            par[v] = u;
            self(self, v, u);
            ans[u] = (ans[u] + ans[v]) % mod;
            // so the idea is that once we fix both strings, there is only one way to walk through them in this dp.
            for (int i = sz(bichos[u])-1; ~i; --i) {
                for (int j = sz(bichos[v])-1; ~j; --j) {
                    for (auto w1 : bichos[v][j]) {
                        for (auto w2 : bichos[u][i]) {
                            if (s[w1] == s[w2]) {
                                // first letter of pair -- start
                                add(dp[w1][w2][0], 1, u);
                                add(dp[w2][w1][0], 1, u);
                            }
                            if (s[par[w1]] == s[w2]) {
                                // second letter of pair
                                add(dp[w2][par[w1]][0], dp[w2][w1][1], u);
                            }
                            if (w2 != u and s[par[w2]] == s[w1]) { 
                                add(dp[w1][par[w2]][0], dp[w1][w2][1], u);
                            }
                            // only here we know [w1][w2], [w2][w1]

                            // first letter of pair -- not start
                            add(dp[par[w1]][w2][1], dp[w1][w2][0]);
                            if (w2 != u) add(dp[par[w2]][w1][1], dp[w2][w1][0]);

                            // go up to find next letter
                            add(dp[par[w1]][w2][0], dp[w1][w2][0]);
                            if (w2 != u) add(dp[par[w2]][w1][0], dp[w2][w1][0]);

                            // go up to find missing letter 
                            add(dp[w2][par[w1]][1], dp[w2][w1][1]);
                            if (w2 != u) add(dp[w1][par[w2]][1], dp[w1][w2][1]);
                        }
                    }
                }
            }
            if (sz(bichos[v]) >= sz(bichos[u])) bichos[u].resize(sz(bichos[v])+1);
            for (int i = 0; i < sz(bichos[v]); ++i) {
                for (auto x : bichos[v][i]) bichos[u][i+1].pb(x);
            }
            // here, we consider a string which both endpoints started in v's subtree.
            for (int i = sz(bichos[v])-1; ~i; --i) {
                for (auto x : bichos[v][i]) {
                    // ignore u
                    add(dp[x][u][1], dp[x][v][1]);
                    // ignore u
                    add(dp[u][x][0], dp[v][x][0]);
                    // use u
                    add(dp[u][x][1], dp[v][x][0]);
                    if (s[u] == s[x]) {
                        add(dp[x][u][0], dp[x][v][1], u);
                    }
                    if (s[u] == s[par[x]]) {
                        add(dp[u][par[x]][0], dp[v][x][0]);
                        add(dp[u][par[x]][0], dp[v][x][0]);
                    }
                }
            }
        }
        add(dp[u][u][0], dp[u][u][1], u);
    };
    dfs(dfs, 0, n);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        cout << "i = " << i << " j = " << j << ": " << dp[i][j][0] << " " << dp[i][j][1] << endl;
    }
    for (auto x : ans) cout << x << " ";
    cout << endl;
    cout << "####" << endl;
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
