#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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

vector<int> solve(int n, vector<int> c, vector<vector<int>> g){
    vector<int> foi(n), ans(n), subt(n), atv(n), atv2(n);
    for (auto x : c) ans[x]++;
    auto fc = [&] (auto&& self, int u, int p, int tam) -> int {
        for (auto v : g[u]) {
            if (v == p or foi[v]) continue;
            if (subt[v] * 2 > tam) return self(self, v, u, tam);
        }
        return u;
    };
    auto pre = [&] (auto&& self, int u, int p) -> void {
        subt[u] = 1;
        for (auto v : g[u]) {
            if (foi[v] or v == p) continue;
            self(self, v, u);
            subt[u] += subt[v];
        }
    };  
    int S = 0, Scur = 0;
    auto dfs = [&] (auto&& self, int u, int p, int tipo) -> void {
        int cor = c[u];
        atv2[cor]++;
        if (atv2[cor] == 1) {
            if (tipo == 0) ans[cor] += atv[cor] * subt[u];
            else if (tipo == 1) atv[cor] += subt[u];
            else if (tipo == 2) atv[cor] -= subt[u];
            else if (tipo == 3) ans[cor] += subt[u] * (S - atv[cor] - Scur);
        }
        for (auto v : g[u]) {
            if (v == p or foi[v]) continue;
            self(self, v, u, tipo);
        }
        atv2[cor]--;
    };
    auto solve = [&] (auto&& self, int u) -> void {
        pre(pre, u, u);
        u = fc(fc, u, u, subt[u]);
        pre(pre, u, u);
        foi[u] = 1;
        atv2[c[u]]++;
        for (auto v : g[u]) {
            if (foi[v]) continue;
            dfs(dfs, v, v, 0);
            dfs(dfs, v, v, 1);
        }
        S = subt[u];
        for (auto v : g[u]) {
            if (foi[v]) continue;
            dfs(dfs, v, v, 2);
            Scur = subt[v];
            dfs(dfs, v, v, 3);
            dfs(dfs, v, v, 1);
        }
        int tot = 1;
        for (auto v : g[u]) {
            if (foi[v]) continue;
            dfs(dfs, v, v, 2);
            ans[c[u]] += subt[v] * tot, tot += subt[v];
        }
        atv2[c[u]]--;
        for (auto v : g[u]) {
            if (!foi[v]) self(self, v);
        }
    };
    solve(solve, 0);
    return ans;
}

vector<int> brute(int n, vector<int> c, vector<vector<int>> g) {
    vector<int> resp(n), lvl(n), par(n);
    auto pre = [&] (auto&& self, int u, int p) -> void {
        par[u] = p, lvl[u] = 1 + lvl[p];
        for (auto v : g[u]) if (v != p) self(self, v, u);
    };
    pre(pre, 0, 0);
    auto go = [&] (int u, int v) {
        vector<int> mark(n);
        while (u != v) {
            mark[c[u]] = mark[c[v]] = 1;
            if (lvl[u] > lvl[v]) u = par[u];
            else if (lvl[u] < lvl[v]) v = par[v];
            else u = par[u], v = par[v];
        }
        mark[c[u]] = 1;
        for (int i = 0; i < n; ++i) resp[i] += mark[i];
    };
    for (int i = 0; i < n; ++i) for (int j = i; j < n; ++j) go(i, j);
    return resp;
}

int32_t main(){_
#ifndef gato
    int n; cin >> n;
    vector<int> c(n);
    for (auto& x : c) cin >> x, --x;
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    auto resp = solve(n, c, g);
    for (auto x : resp) cout << x << endl;
#else
    int t = 1;
    while (true) {

        int n = rnd(1, 30);
        vector<vector<int>> g(n);
        vector<ii> edg;
        vector<int> c(n);
        for (auto& x : c) x = rnd(0, n-1);
        for (int i = 1; i < n; ++i) {
            int pp = rnd(0, i-1);
            edg.pb({pp, i});
            g[pp].pb(i), g[i].pb(pp);
        }
        auto my = solve(n, c, g);
        auto ans = brute(n, c, g);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : c) cout << x + 1 << ' ';
            cout << endl;
            for (auto [x, y] : edg) cout << x + 1 << ' ' << y + 1 << endl;
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
