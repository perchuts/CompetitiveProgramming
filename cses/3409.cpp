#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
//#define gato
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

vector<int> solve(int n, int m, vector<iii> edg) {
    vector<int> par(n), lvl(n, 1); iota(all(par), 0);
    auto findp = [&] (auto&& self, int u) -> int { return par[u] = (par[u] == u ? u : self(self, par[u])); };
    auto merge = [&] (int u, int v) {
        u = findp(findp, u), v = findp(findp, v);
        if (u == v) return false;
        if (lvl[u] < lvl[v]) swap(u, v);
        par[v] = u, lvl[u] += lvl[v];
        return true;
    };
    vector<int> ord(m); iota(all(ord), 0);
    sort(all(ord), [&] (int x, int y) { return edg[x] < edg[y]; });
    vector<int> ans(m, 0);
    vector<vector<ii>> g(n);
    int base = 0;
    for (int i : ord) {
        auto [w, u, v] = edg[i];
        if (merge(u, v)) g[u].pb({v, w}), g[v].pb({u, w}), base += w, ans[i] = -1;
    }
    vector<vector<ii>> sp(n, vector<ii>(20));
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        for (int i = 1; i < 20; ++i) {
            auto [x1, y1] = sp[u][i-1];
            auto [x2, y2] = sp[x1][i-1];
            sp[u][i] = pair(x2, max(y1, y2));
        }
        for (auto [v, w] : g[u]) {
            if (v == p) continue;
            sp[v][0] = {u, w}, lvl[v] = lvl[u] + 1;
            self(self, v, u);
        }
    };
    lvl[0] = 0;
    dfs(dfs, 0, 0);
    auto get = [&] (int u, int v) {
        if (lvl[u] < lvl[v]) swap(u, v);
        int ans = 0;
        for (int i = 19; ~i; --i) {
            auto [pu, mxw] = sp[u][i];
            if (lvl[pu] >= lvl[v]) u = pu, ckmax(ans, mxw);
        }
        if (u == v) return ans;
        for (int i = 19; ~i; --i) {
            auto [pu, mxw] = sp[u][i];
            auto [pv, mxw2] = sp[v][i];
            if (pu != pv) u = pu, v = pv, ckmax(ans, max(mxw, mxw2));
        }
        return max({ans, sp[u][0].second, sp[v][0].second});
    };
    for (int i = 0; i < m; ++i) {
        if (ans[i] == -1) {
            ans[i] = base;
            continue;
        }
        auto [w, u, v] = edg[i];
        ans[i] = base + w - get(u, v);
    }
    return ans;
}

vector<int> brute(int n, int m, vector<iii> edg) {
    vector<int> ans;
    auto temp = edg;
    sort(all(temp));
    for (int forced = 0; forced < m; ++forced) {
        vector<int> par(n), lvl(n, 1); iota(all(par), 0);
        auto findp = [&] (auto&& self, int u) -> int { return par[u] = (par[u] == u ? u : self(self, par[u])); };
        auto merge = [&] (int u, int v) {
            u = findp(findp, u), v = findp(findp, v);
            if (u == v) return false;
            if (lvl[u] < lvl[v]) swap(u, v);
            par[v] = u, lvl[u] += lvl[v];
            return true;
        };
        auto [a, b, c] = edg[forced];
        int tot = a;
        merge(b, c);
        for (auto [w, u, v] : temp) {
            if (merge(u, v)) tot += w;
        }
        ans.pb(tot);
    }
    return ans;
}

int32_t main(){_
#ifndef gato
    int n, m; cin >> n >> m;
    vector<iii> edg(m);
    for (auto& [x, y, z] : edg) cin >> y >> z >> x, --y, --z;
    auto ans = solve(n, m, edg);
    for (auto x : ans) cout << x << endl;
#else
    int t = 1;
    while (true) {
        int n = 100, m = rnd(n-1, 4*n);
        vector<vector<int>> foi(n, vector<int>(n));
        vector<iii> edg;
        for (int i = 1; i < n; ++i) {
            int p = rnd(0, i-1);
            foi[p][i] = 1;
            edg.pb({rnd(1, 5), p, i});
        }
        while (sz(edg) != m) {
            int i = rnd(0, n-2), j = rnd(i+1, n-1);
            if (foi[i][j]) continue;
            foi[i][j] = 1;
            edg.pb({rnd(1, 5), i, j});
        }
        auto my = solve(n, m, edg);
        auto ans = brute(n, m, edg);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << m << endl;
            for (auto [z, u, v] : edg) cout << u+1 << ' ' << v+1 << ' ' << z << endl;
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
