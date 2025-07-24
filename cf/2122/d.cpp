#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
//#define gato
#define int ll

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 1e18;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

ii solve(int n, int m, vector<ii> edg) {
    vector<vector<int>> g(n);
    for (auto [u, v] : edg) g[u].pb(v), g[v].pb(u);
    vector<int> dp(n, inf); dp[0] = 0;
    for (int t = 0; ; ++t) {
        vector<int> ndp(n, inf);
        for (int i = 0; i < n; ++i) {
            ckmin(ndp[i], dp[i]+1);
            int l = g[i][t%sz(g[i])];
            ckmin(ndp[l], dp[i]);
        }
        swap(dp, ndp);
        if (dp.back() != inf) return {t+1, dp.back()};
    }
    return {998, 6969};
}

ii brute(int n, int m, vector<ii> edg) {
    vector<vector<int>> dp(n, vector<int>(n*n*n+1, inf));
    dp[0][0] = 0;
    vector<vector<int>> g(n);
    for (auto [x, y] : edg) g[x].pb(y), g[y].pb(x);
    priority_queue<iii, vector<iii>, greater<>> qq;
    qq.push({0, 0, 0});
    while (!qq.empty()) {
        auto [d, u, tt] = qq.top(); qq.pop();
        if (d != dp[u][tt] or tt == n*n*n) continue;
        int deg = sz(g[u]);
        if (ckmin(dp[u][tt+1], d+1)) qq.push({d+1, u, tt+1});
        int v = g[u][tt%deg];
        if (ckmin(dp[v][tt+1], d)) qq.push({d, v, tt+1});
    }
    for (int i = 1; ; ++i) if (dp[n-1][i] != inf) return {i, dp[n-1][i]};
    return {inf, inf};
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        vector<ii> edg(m);
        for (auto& [x, y] : edg) cin >> x >> y, --x, --y;
        auto [a, b] = solve(n, m, edg);
        cout << a << ' ' << b << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 5), m = rnd(n-1, n*(n-1)/2);
        vector<ii> edg;
        vector<vector<int>> mark(n, vector<int>(n));
        for (int i = 0; i < n-1; ++i) {
            int x = rnd(0, i);
            mark[x][i+1] = mark[i+1][x] = 1;
            edg.pb({x, i+1});
        }
        for (int i = 0; i < m-n+1; ++i) {
            int x = rnd(0, n-2), y = rnd(x+1, n-1);
            while (mark[x][y]) x = rnd(0, n-2), y = rnd(x+1, n-1);
            mark[x][y] = mark[y][x];
            edg.pb({x, y});
        }
        auto ans = brute(n, m, edg);
        auto my = solve(n, m, edg);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << m << endl;
            for (auto [x, y] : edg) cout << x + 1 << ' ' << y + 1 << endl;
            cout << "Your output: " << my.first << ' ' << my.second;
			cout << endl;
            cout << "Answer: " << ans.first << ' ' << ans.second;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
