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

pair<int, vector<int>> solve(int n, int k, vector<int> w, vector<int> c, vector<vector<int>> g) {
    vector<set<int>> bags(n);
    vector<vector<int>> undef(n);
    int ans = 0;
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        int big = -1;
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
            if (big == -1 or sz(bags[big]) < sz(bags[v])) big = v;
        }
        if (big == -1) {
            if (c[u]) bags[u].insert(c[u]);
            else undef[u].push_back(u);
            return;
        }
        int big2 = -1;
        for (auto v : g[u]) {
            if (v == p) continue;
            if (big2 == -1 or sz(undef[v]) > sz(undef[big2])) big2 = v;
        }
        swap(undef[u], undef[big2]);
        swap(bags[u], bags[big]);
        if (c[u] == 0) undef[u].push_back(u);
        int bad1 = -1, bad2 = -1;
        for (auto v : g[u]) {
            if (v == p or v == big) continue;
            for (auto val : bags[v]) {
                if (bags[u].find(val) != end(bags[u])) {
                    if (bad1 == -1) bad1 = val;
                    else if (bad2 == -1 and val != bad1) bad2 = val;
                } else bags[u].insert(val);
            }
        }
        for (auto v : g[u]) {
            if (v == p or v == big2) continue;
            for (auto x : undef[v]) undef[u].pb(x);
        }
        if (c[u] == 0) {
            if (bad2 != -1) {
                for (auto v : undef[u]) c[v] = bad2;
                undef[u].clear();
                ans += w[u];
            }
            else if (bad1 != -1) {
                for (auto v : undef[u]) c[v] = bad1;
                undef[u].clear();
            }
            else if (!bags[u].empty()) {
                for (auto v : undef[u]) c[v] = *begin(bags[u]);
                undef[u].clear();
            }
        } else {
            if ((bad1 != -1 and bad1 != c[u]) or (bad2 != -1)) {
				ans += w[u];
			}
            for (auto v : undef[u]) c[v] = c[u];
            undef[u].clear();
            bags[u].insert(c[u]);
        }
    };
    dfs(dfs, 0, 0);
    assert(sz(undef[0]) == n or sz(undef[0]) == 0);
    for (auto x : undef[0]) c[x] = 1;
    return pair(ans, c);
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n, k; cin >> n >> k;
        vector<int> w(n), c(n);
        for (auto& x : w) cin >> x;
        for (auto& x : c) cin >> x;
        vector<vector<int>> g(n);
        for (int i = 0; i < n-1; ++i) {
            int u, v; cin >> u >> v; --u, --v;
            g[u].pb(v), g[v].pb(u);
        }
        auto [cost, ans] = solve(n, k, w, c, g);
        cout << cost << endl;
        for (auto x : ans) cout << x << ' ';
        cout << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 6), k = rnd(1, 3);
        vector<vector<int>> g(n);
        vector<int> w(n), c(n);
        for (auto& x : w) x = rnd(1, 5);
        for (auto& x : c) x = rnd(0, k);
        vector<ii> e;
        for (int i = 1; i < n; ++i) {
            int pp = rnd(0, i-1);
            e.pb({i, pp});
            g[pp].pb(i), g[i].pb(pp);
        }
        auto [cost, ans] = solve(n, k, w, c, g);
        auto cc = ans;
        int real_cost = 0;
        vector<map<int, int>> cols(n);
        auto go = [&] (auto&& self, int u, int p) -> void {
            cols[u][cc[u]] += 1;
            int foi = 0;
            for (auto v : g[u]) {
                if (v == p) continue;
                self(self, v, u);
                for (auto [xx, yy] : cols[v]) {
                    if (xx != cc[u] and cols[u][xx] != 0) foi = 1;
                    cols[u][xx] += yy;
                }
            }
            if (foi) real_cost += w[u];
        };
        go(go, 0, 0);
        if (real_cost != cost or (*min_element(all(cc)) == 0)) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << k << endl;
            for (auto x : w) cout << x << ' ';
            cout << endl;
            for (auto x : c) cout << x << ' ';
            cout << endl;
            for (auto [x, y] : e) cout << x + 1 << ' ' << y + 1 << endl;
            cout << "Your output: " << cost << endl;
            for (auto x : cc) cout << x << ' ';
            cout << endl;
            cout << "real cost: " << real_cost << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
