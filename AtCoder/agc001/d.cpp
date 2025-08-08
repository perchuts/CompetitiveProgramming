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

vector<vector<int>> solve(int n, int m, vector<int> a) {
    vector<vector<int>> v(2, vector<int>());
    for (auto x : a) v[x&1].pb(x);
    if (sz(v[1]) > 2) return {};
    if (sz(a) == 1) {
        if (n == 1) return {a, a};
        else if (n&1) return {a, {2, n-2}};
        return {a, {1, n-1}};
    }
    if (v[1].empty()) {
        v[0][0]--;
        v[0].back()++;
        return {a, v[0]};
    }
    if (sz(v[1]) == 1) {
        a.clear();
        a.pb(v[1][0]);
        for (auto x : v[0]) a.pb(x);
        vector<int> b = {v[1][0]+1};
        for (auto x : v[0]) b.pb(x);
        b.back()--;
        return {a, b};
    }
    a.clear(); a.pb(v[1][0]);
    for (auto x : v[0]) a.pb(x);
    a.pb(v[1][1]);
    auto b = a;
    if (v[1][0] > 1) b[0]--, b.back()++;
    else if (v[1][1] > 1) b[0]++, b.back()--;
    else b[0]++, b.pop_back();
    return {a, b};
}

vector<vector<int>> brute(int n, int m, vector<int> a) {
    vector<vector<int>> ret;
    sort(all(a));
	do {
        vector<int> b;
        auto gen = [&] (auto&& self, int falta) -> bool {
            if (falta < 0) return false;
            if (falta == 0) {
                vector<vector<int>> ans = {a, b};
                vector<vector<int>> g(n);
                for (int __ = 0; __ < 2; ++__) {
                    for (int i = 0, j = 0; j < n; j += ans[__][i], i++) {
                        int x = j, y = j + ans[__][i] - 1;
                        while (x < y) g[x].pb(y), g[y].pb(x), x++, y--;
                    }
                }
                vector<int> vis(n);
                auto dfs = [&] (auto&& self2, int u) -> int {
                    vis[u] = 1;
                    int tt = 1;
                    for (auto v : g[u]) {
                        if (vis[v]) continue;
                        tt += self2(self2, v);
                    }
                    return tt;
                };
                if (dfs(dfs, 0) == n) {
                    ret = ans;
                    return true;
                }
                return false;
            }
            b.pb(1);
            while (b.back() <= falta) {
                if (self(self, falta-b.back())) return true;
                b.back()++;
            }
            b.pop_back();
            return false;
        };
        gen(gen, n);
	} while (next_permutation(all(a)));
    return ret;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    int n, m; cin >> n >> m;
    vector<int> a(m);
    for (auto &x : a) cin >> x;
    auto ans = solve(n, m, a);
    if (ans.empty()) cout << "Impossible" << endl;
    else {
        for (auto x : ans[0]) cout << x << ' ';
        cout << endl;
        cout << sz(ans[1]) << endl;
        for (auto x : ans[1]) cout << x << ' ';
        cout << endl;
    }
#else
    int t = 1;
    while (true) {
        int lim = 1000;
        int m = rnd(1, lim), n = 0;
        vector<int> a(m);
        for (auto& x : a) x = rnd(1, lim), n += x;
        if (n > lim) continue;
        auto ans = solve(n, m, a);
        //auto ans = brute(n, m, a);
        vector<vector<int>> g(n);
        auto oa = a;
        if (ans.empty()) continue;
        a = ans[0];
        for (int __ = 0; __ < 2; ++__) {
            for (int i = 0, j = 0; j < n; j += ans[__][i], i++) {
                int x = j, y = j + ans[__][i] - 1;
                while (x < y) g[x].pb(y), g[y].pb(x), x++, y--;
            }
        }
        vector<int> vis(n);
        auto dfs = [&] (auto&& self, int u) -> int {
            vis[u] = 1;
            int ret = 1;
            for (auto v : g[u]) {
                if (vis[v]) continue;
                ret += self(self, v);
            }
            return ret;
        };
        int v = dfs(dfs, 0);
        if (v != n) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << m << endl;
            for (auto x : oa) cout << x << ' ';
            cout << endl;
            cout << "Your output: " << endl;
            for (auto x : a) cout << x << ' ';
            cout << endl;
            for (auto x : ans[1]) cout << x << ' ';
            cout << endl;
            cout << "Visited only " << v << " vertices" << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
