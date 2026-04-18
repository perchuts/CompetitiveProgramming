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

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
vector<int> solve(int n, int k, vector<vector<int>> g, vector<int> lim) {
    int qt_leaf = 0, ptr = 0, T = 0;
    for (int i = 0; i < n; ++i) qt_leaf += (sz(g[i]) == 1);
    vector<int> ans(n), l(n), r(n);
    if (n == 2) {
        if (lim[0] == 2) return {0, 0};
        if (lim[1] == 2) return {1, 1};
        return vector<int>();
    }
    vector<int> ids(k); iota(all(ids), 0); sort(all(ids), [&] (int x, int y) { return lim[x] > lim[y]; });
    for (int i = 0; i < n; ++i) {
        if (sz(g[i]) == 1) {
            if (lim[ids[ptr]] == 0) {
                ptr++;
                if (lim[ids[ptr]] == 1) return vector<int>();
            }
            ans[i] = ids[ptr], lim[ids[ptr]]--;
        }
    }
    vector<set<int>> bichos(k), bichos_internos(k);
    for (int i = 0; i < n; ++i) {
        if (sz(g[i]) > 1) {
            if (lim[ids[ptr]] == 0) ptr++;
            ans[i] = ids[ptr];
            lim[ids[ptr]]--;
        }
    }
    vector<int> leaves;
    auto pre = [&] (auto&& self, int u, int p) -> void {
        l[u] = ++T;
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
        }
        if (sz(g[u]) == 1) leaves.pb(u);
        r[u] = T;
    };
    int root = 0;
    for (int i = 0; i < n; ++i) if (sz(g[i]) > 1) root = i;
    pre(pre, root, root);
    for (int i = 0; i < n; ++i) {
        bichos[ans[i]].insert(l[i]);
        if (sz(g[i]) != 1) bichos_internos[ans[i]].insert(i);
    }
    auto get_range = [&] (int cor) {
        int lx = *begin(bichos[cor]);
        int rx = *prev(end(bichos[cor]));
        return pair(lx, rx);
    };
    auto paint = [&] (int cara, int cor) {
        if (sz(g[cara]) != 1) {
            bichos_internos[ans[cara]].erase(cara);
            bichos_internos[cor].insert(cara);
        }
        bichos[ans[cara]].erase(l[cara]);
        ans[cara] = cor;
        bichos[ans[cara]].insert(l[cara]);
    };
    auto dfs = [&] (auto&& self, int u, int p) -> int {
        vector<ii> cc;
        for (auto v : g[u]) {
            if (v == p) continue;
            cc.pb({self(self, v, u), v});
        }
        if (cc.empty()) return u;
        vector<ii> bad, good;
        for (auto [cara, child] : cc) {
            auto [lx, rx] = get_range(ans[cara]);
            if (l[child] <= lx and rx <= r[child]) bad.pb({cara, child});
            else good.pb({cara, child});
        }
        if (bad.empty()) return good[0].first;
        if (sz(bad) != 1) {
            int prim = ans[bad[0].first];
            for (int i = 0; i < sz(bad)-1; ++i) paint(bad[i].first, ans[bad[i+1].first]);
            paint(bad.back().first, prim);
            return bad[0].first;
        }
        int cor = ans[bad[0].first];
        if (!bichos_internos[cor].empty()) {
            int a = *begin(bichos_internos[cor]);
            paint(a, ans[u]);
            paint(u, cor);
            return bad[0].first;
        }
        int z;
        if (!good.empty()) z = good[0].first;
        else z = (l[leaves[0]] < l[u] ? leaves[0] : leaves.back());
		//cout << "u = " << u << ", " << "sz(bad) = " << sz(bad) << endl;
		//cout << "z = " << z << endl;
        int cor_boa = ans[z];
		auto it = (bichos[cor_boa].lower_bound(l[bad[0].second]));
        if (it != end(bichos[cor_boa]) and (*it) <= r[bad[0].second]) return bad[0].first;
        paint(bad[0].first, cor_boa);
        paint(z, cor);
        return bad[0].first;
    };
	//cout << "root = " << root << endl;
    dfs(dfs, root, root);
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n, k; cin >> n >> k;
        vector<vector<int>> g(n);
        for (int i = 0; i < n-1; ++i) {
            int u, v; cin >> u >> v; --u, --v;
            g[u].pb(v), g[v].pb(u);
        };
        vector<int> lim(k);
        for (auto& x : lim) cin >> x;
        auto ans = solve(n, k, g, lim);
        if (ans.empty()) cout << -1 << endl;
        else {
            for (auto x : ans) cout << x + 1 << " ";
            cout << endl;
        }
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 50), k = rnd(1, n);
        vector<vector<int>> g(n);
        vector<ii> edg;
        vector<int> lim(k);
        int S = 0;
		int cap = min(n, 4LL);
        for (auto& x : lim) x = rnd(1, cap), S += x;
        if (S < n) continue;
        vector<int> p(n); iota(all(p), 0); shuffle(all(p), rng);
        for (int i = 1; i < n; ++i) edg.pb({p[i], p[rnd(0, i-1)]});
        for (auto& [x, y] : edg) g[x].pb(y), g[y].pb(x);
        auto my = solve(n, k, g, lim);
        if (!my.empty()) {
            vector<int> cnt(k);
            bool ok = true;
            for (auto x : my) {
                if (x < 0 or k <= x) { ok = false; break; }
                cnt[x]++;
            }
            for (int i = 0; i < k; ++i) ok &= (cnt[i] <= lim[i]);
            if (ok) {
                for (auto [a, b] : edg) {
                    vector<int> temp(k);
                    auto dfs = [&] (auto&& self, int u, int p) -> void {
                        temp[my[u]]++;
                        for (auto v : g[u]) {
                            if (u == a and v == b) continue;
                            if (u == b and v == a) continue;
                            if (v == p) continue;
                            self(self, v, u);
                        }
                    };
                    dfs(dfs, 0, 0);
                    bool bad = 1;
                    for (int i = 0; i < k; ++i) bad &= (temp[i] == 0 or temp[i] == cnt[i]);
                    if (bad) { ok = 0; break; }
                }
            }
            if (!ok) {
                cout << "Wrong answer on test " << t << endl;
                cout << 1 << endl;
                cout << n << " " << k << endl;
                for (auto [x, y] : edg) cout << x + 1 << " " << y + 1 << endl;
                for (auto x : lim) cout << x << " ";
                cout << endl;
                cout << "Your output: ";
                for (auto x : my) cout << x + 1 << " ";
                cout << endl;
                exit(0);
            }
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
