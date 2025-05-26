#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

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

vector<int> solve(int n, int q, vector<int> c, vector<vector<int>> g, vector<ii> qu){
    vector<vector<int>> sp(n, vector<int>(20));
    vector<int> lvl(n), dp1(n, 0), sub(n), dp(n);
    auto pre = [&] (auto&& self, int u, int p) -> void {
        sub[u] = c[u];
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
            if (sub[v]) dp1[u] += dp1[v] + 2;
            sub[u] += sub[v];
        }
    };
    vector<int> dist(n);
    auto pre2 = [&] (auto&& self, int u, int p) -> void {
        if (u != p) {
            if (sub[u]) dist[u] = 0;
            else dist[u] = dist[p] + 1;
            if (sub[u] == sub[0]) dp[u] = dp[p]-2;
            else if (sub[u]) dp[u] = dp[p];
            else dp[u] = 2 + dp[p];
        } else dp[u] = dp1[u];
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
        }
    };
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        sp[u][0] = p;
        for (int i = 1; i < 20; ++i) sp[u][i] = sp[sp[u][i-1]][i-1];
        for (auto v : g[u]) {
            if (v == p) continue;
            lvl[v] = lvl[u] + 1;
            self(self, v, u);
        }
    };
    pre(pre, 0, 0);
    pre2(pre2, 0, 0);
    dfs(dfs, 0, 0);
    auto get = [&] (int u, int v) {
        if (lvl[u] < lvl[v]) swap(u, v);
        int _u = u, _v = v;
        for (int i = 19; ~i; --i) {
            int pu = sp[u][i];
            if (lvl[pu] >= lvl[v]) u = pu;
        }
        auto calc = [&] (int lca, int x) {
            int d = lvl[x]-lvl[lca];
            //cout << "calc: ";
            //cout << lca+1 << ' ' << x+1 << endl;
            if (dist[x] == 0) return -d;
            if (dist[x] <= d) return -d + 2*dist[x];
            return d;
        };
        if (u == v) return dp[v] + calc(u, _u);
        for (int i = 19; ~i; --i) {
            int pu = sp[u][i];
            int pv = sp[v][i];
            if (pu != pv) u = pu, v = pv;
        }
        int lca = sp[u][0];
        return dp[lca] + calc(lca, _u) + calc(lca, _v);
    };
    vector<int> ans;
    for (auto [u, v] : qu) {
        if (u == v) ans.pb(dp[u]);
        else ans.pb(get(u, v));
    }
    return ans;
}

vector<int> brute(int n, int q, vector<int> c, vector<vector<int>> g, vector<ii> qu){
    vector<int> ans;
    for (auto [x, y] : qu) {
        vector<int> par(n), vis(n), subt = c;
        auto pre = [&] (auto&& self, int u, int p) -> void {
            par[u] = p;
            for (auto v : g[u]) {
                if (v == p) continue;
                self(self, v, u);
                subt[u] += subt[v];
            }
        };
        pre(pre, x, x);
        int cost = 0;
        auto calc = [&] (auto&& self, int u, int p) -> void {
            vis[u] = true;
            for (auto v : g[u]) {
                if (v == p) continue;
                if (subt[v]) cost += 2, self(self, v, u);
            }
        };
        calc(calc, x, x);
        int eu = y;
        while (eu != x) {
            if (vis[eu]) cost--;
            else cost++;
            eu = par[eu];
        }
        ans.pb(cost);
    }
    return ans;
}
int32_t main(){_
#ifndef gato
    int n, q; cin >> n >> q;
    vector<int> c(n);
    for (auto& x : c) cin >> x;
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v; --u, -- v;
        g[u].pb(v), g[v].pb(u);
    }
    vector<ii> qu(q);
    for (auto& [x, y] : qu) cin >> x >> y, --x, --y;
    auto ans = solve(n, q, c, g, qu);
    for (auto x : ans) cout << x << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 100), q = 20;
        vector<int> c(n);
        vector<vector<int>> g(n);
        int s = 0;
        for (auto& x : c) x = rnd(0, 1), s += x;
        if (!s) continue;
        vector<ii> edg;
        for (int i = 1; i < n; ++i) {
            int j = rnd(0, i-1);
            edg.pb({i+1, j+1});
            g[i].pb(j), g[j].pb(i);
        }
        vector<ii> qu(q);
        for (auto& [x, y] : qu) x = rnd(0, n-1), y = rnd(0, n-1);
        auto my = solve(n, q, c, g, qu);
        auto ans = brute(n, q, c, g, qu);
        if (ans != my) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << q << endl;
            for (auto x : c) cout << x << ' ';
            cout << endl;
            for (auto [x, y] : edg) cout << x << ' ' << y << endl;
            for (auto [x, y] : qu) cout << x+1 << ' ' << y+1 << endl;
            cout << "Your output: ";
            for (auto x : my) cout << x << ' ';
            cout << endl;
            cout << "Answer: ";
            for (auto x : ans) cout << x << ' ';
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
