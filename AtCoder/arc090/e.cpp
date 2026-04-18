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
    int n, m, s, t; cin >> n >> m >> s >> t; --s, --t;
    vector<vector<ii>> g(n);
    vector<iii> edg(m);
    for (auto& [u, v, w] : edg) {
        cin >> u >> v >> w; --u, --v;
        g[u].pb({v, w});
        g[v].pb({u, w});
    }
    auto get = [&] (int src) {
        vector<int> dist(n, 1e18);
        dist[src] = 0;
        priority_queue<ii, vector<ii>, greater<>> pq;
        pq.push({0, src});
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d != dist[u]) continue;
            for (auto [v, w] : g[u]) {
                if (ckmin(dist[v], d + w)) pq.push({d+w, v});
            }
        }
        return dist;
    };
    auto getw = [&] (vector<int> d) {
        vector<vector<int>> gg(n);
        vector<int> deg(n), ways(n);
        for (auto [u, v, w] : edg) {
            if (d[u] == d[v] + w) gg[v].pb(u), deg[u]++;
            if (d[v] == d[u] + w) gg[u].pb(v), deg[v]++;
        }
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (deg[i] == 0) ways[i] = 1, q.push(i);
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto v : gg[u]) {
                ways[v] = (ways[v] + ways[u]) % mod;
                deg[v]--;
                if (deg[v] == 0) q.push(v);
            }
        }
        return ways;
    };
    vector<vector<int>> d(2), dp(2);
    d[0] = get(s), d[1] = get(t);
    dp[0] = getw(d[0]), dp[1] = getw(d[1]);
    int ans = 0, D = d[0][t];
    for (auto [u, v, w] : edg) {
        for (int tt = 0; tt < 2; ++tt) {
            if (d[0][u] * 2 < D and d[0][v] * 2 > D and d[0][u] + d[1][v] + w == D) {
                int ways = dp[0][u] * dp[1][v] % mod;
                ans = (ans + ways*ways) % mod;
            }
            swap(u, v);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (d[0][i] * 2 == D) {
            int ways = dp[0][i] * dp[1][i] % mod;
            ans = (ans + ways*ways) % mod;
        }
    }
	int penis = dp[0][t] * dp[1][s] % mod;
	ans = (penis - ans + mod) % mod;
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
