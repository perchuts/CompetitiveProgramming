#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 1e18+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

vector<int> solve(int n, int m, vector<iii> edg) {
    vector<vector<iii>> g(n);
    int idd = 0;
    for (auto& [u, v, w] : edg) {
        g[u].pb({v, w, idd});
        g[v].pb({u, w, idd});
        idd++;
    }
    vector<vector<ii>> g2(n);
    vector<int> dist(n, inf); dist[0] = 0;
    priority_queue<ii, vector<ii>, greater<>> pq;
    pq.push({0, 0});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue;
        for (auto [v, w, id] : g[u]) {
            if (ckmin(dist[v], d + w)) pq.push({d + w, v});
        }
    }
    idd = 0;
    vector<int> ord(n), nice(n); iota(all(ord), 0);
    sort(all(ord), [&] (int x, int y) { return dist[x] > dist[y]; });
    nice[n-1] = 1;
    for (auto i : ord) {
        if (!nice[i]) continue;
        for (auto [j, w, id] : g[i]) {
            if (dist[i] == dist[j] + w) {
                nice[j] = 1;
                g2[i].pb({j, id});
                g2[j].pb({i, id});
            }
        }
    }
    vector<int> ans(m, 0), dp(n), lvl(n); vector<ii> par(n);
    if (dist[n-1] == inf) return ans;
    auto dfs = [&] (auto&& self, int u, int p) -> int {
        lvl[u] = 1 + lvl[p];
        for (auto [v, id] : g2[u]) {
            if (lvl[v] == 0) {
                par[v] = {u, id};
                dp[u] += self(self, v, u);
            } else if (lvl[v] > lvl[u]) {
                dp[u]--;
            } else {
                dp[u]++;
            }
        }
        dp[u]--;
        return dp[u];
    };
    dfs(dfs, 0, 0);
    int cur = n-1;
    while (cur) {
        auto [prox, id] = par[cur];
        if (dp[cur] == 0) ans[id] = 1;
        cur = prox;
    }
    return ans;
}

vector<int> brute(int n, int m, vector<iii> edg) {
    vector<vector<iii>> g(n);
    int idd = 0;
    for (auto& [u, v, w] : edg) {
        g[u].pb({v, w, idd});
        g[v].pb({u, w, idd});
        idd++;
    }
    int opt;
    vector<vector<ii>> g2(n);
    {
        vector<int> dist(n, inf); dist[0] = 0;
        priority_queue<ii, vector<ii>, greater<>> pq;
        pq.push({0, 0});
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d != dist[u]) continue;
            for (auto [v, w, id] : g[u]) {
                if (ckmin(dist[v], d + w)) pq.push({d + w, v});
            }
        }
        opt = dist[n-1];
    }
    vector<int> ans(m);
    if (opt == inf) return ans;
    for (int i = 0; i < m; ++i) {
        vector<int> dist(n, inf); dist[0] = 0;
        priority_queue<ii, vector<ii>, greater<>> pq;
        pq.push({0, 0});
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d != dist[u]) continue;
            for (auto [v, w, id] : g[u]) {
                if (id == i) continue;
                if (ckmin(dist[v], d + w)) pq.push({d + w, v});
            }
        }
        ans[i] = (dist[n-1] != opt);
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    int n, m; cin >> n >> m;
    vector<iii> edg(m); 
    for (auto& [u, v, w] : edg) cin >> u >> v >> w, --u, --v;
    auto ans = solve(n, m, edg);
    for (auto x : ans) cout << (x ? "Yes" : "No") << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(4, 30), m = rnd(1, 2*n);
        ckmin(m, n*(n-1)/2);
        vector<iii> edg(m);
        vector<vector<int>> foi(n, vector<int>(n));
        for (auto& [u, v, w] : edg) {
            u = rnd(0, n-2), v = rnd(u+1, n-1), w = rnd(1, 5);
            while (foi[u][v]) u = rnd(0, n-2), v = rnd(u+1, n-1), w = rnd(1, 5);
            foi[u][v] = 1;
        }
        auto my = solve(n, m, edg); auto ans = brute(n, m, edg);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << m << endl;
            for (auto [u, v, w] : edg) cout << u+1 << ' ' << v+1 << ' ' << w << endl;
            cout << "Your output: ";
            for (auto x : my) cout << (x ? "Yes" : "No") << endl;
            cout << "Answer: ";
            for (auto x : ans) cout << (x ? "Yes" : "No") << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
