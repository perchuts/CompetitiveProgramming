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

int solve(int n, int m, vector<iii> edg) {
    vector<vector<int>> cost(n, vector<int>(n));
    for (auto [u, v, w] : edg) cost[u][v] = cost[v][u] = w;
    vector<int> bit(n);
    vector<vector<int>> dp(1<<n, vector<int>(n, 1e18)), bits(1<<n);
    for (int i = 0; i < (1 << n); ++i) {
        for (int j = 0; j < n; ++j) bit[j] = i >> j & 1;
        for (int j = 0; j < n; ++j) if (bit[j]) bits[i].pb(j);
    }
    for (int i = 1; i < (1 << n); ++i) {
        for (int j = 0; j < n; ++j) bit[j] = (i >> j & 1);
        if (bit[0] and !bit[n-1]) dp[i][0] = 0;
        for (int j = (i-1)&i; j; j = (j-1)&i) {
            int tot = 0;
            for (auto u : bits[j]) {
                for (auto v : bits[i-j]) {
                    tot += cost[u][v];
                }
            }
            for (auto u : bits[j]) {
                for (auto v : bits[i-j]) {
                    if (cost[u][v]) ckmin(dp[i][u], dp[i-j][v] + tot - cost[u][v]);
                }
            }
        }
    }
    return dp.back().back();
}

int brute(int n, int m, vector<iii> edg) {
    vector<vector<int>> cost(n, vector<int>(n, -1e18));
    for (auto [u, v, w] : edg) cost[u][v] = cost[v][u] = w;
    vector<int> c(1<<n), bit(n);
    vector<vector<int>> dp(1<<n, vector<int>(n, 1e18));
    vector<vector<int>> bits(1<<n);
    for (int i = 0; i < (1 << n); ++i) {
        for (int j = 0; j < n; ++j) bit[j] = i >> j & 1;
        for (int j = 0; j < n; ++j) {
            if (bit[j]) bits[i].pb(j);
        }
        for (int u = 0; u < n; ++u) {
            for (int v = u+1; v < n; ++v) {
                if (bit[u] != bit[v] and cost[u][v] >= 0) {
                    c[i] += cost[u][v];
                }
            }
        }
    }
    for (int i = 1; i < (1 << n); ++i) {
        for (int j = 0; j < n; ++j) bit[j] = (i >> j & 1);
        if (bit[0] and !bit[n-1]) dp[i][0] = c[i];
        for (int j = (i-1)&i; j; j = (j-1)&i) {
            for (auto u : bits[j]) {
                for (auto v : bits[i-j]) {
                    ckmin(dp[i][u], dp[i-j][v] + c[j] - 2*cost[u][v]);
                }
            }
        }
    }
    return dp.back().back()/2;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    int n, m; cin >> n >> m;
    vector<iii> edg(m);
    for (auto& [x, y, z] : edg) cin >> x >> y >> z, --x, --y;
    cout << solve(n, m, edg) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 5), m = rnd(n-1, n*(n-1)/2);
        vector<vector<int>> foi(n, vector<int>(n));
        vector<iii> edg;
        for (int i = 0; i < n-1; ++i) {
            int j = rnd(0, i);
            int w = rnd(1, 5);
            edg.pb({j, i+1, w});
            foi[j][i+1] = foi[i+1][j] = 1;
        }
        vector<iii> falta;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (!foi[i][j]) {
                    falta.pb({i, j, rnd(1, 5)});
                }
            }
        }
        shuffle(all(falta), rng);
        for (int i = 0; i < m-n+1; ++i) edg.pb(falta[i]);
        auto my = solve(n, m, edg);
        auto ans = brute(n, m, edg);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << " " << m << endl;
            for (auto [x, y, z] : edg) cout << x + 1 << " " << y + 1 << " " << z << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
