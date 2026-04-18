#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
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

vector<int> solve(int n, int m, int q, vector<vector<int>> g, vector<vector<int>> a, vector<vector<int>> v) {
    vector<int> lvl(n), used(n), par(n), lx(n), rx(n);
	int T = 0;
    auto pre = [&] (auto&& self, int u, int p) -> void {
        lvl[u] = 1 + lvl[p], par[u] = p, lx[u] = ++T;
        for (auto V : g[u]) {
            if (V == p) continue;
            self(self, V, u);
        }
		rx[u] = T;
    };
	// is u anc of v?
    pre(pre, 0, 0);
	auto is_anc = [&] (int u, int w) { return (lx[u] <= lx[w] and rx[w] <= rx[u]); };
    int mn = 0;
    vector<iii> z;
    vector<vector<int>> bichos(n);
	vector<pair<int, int>> info(m);
    for (int i = 0; i < m; ++i) {
        int x = a[i][0];
        for (auto u : a[i]) {
            if (lvl[u] < lvl[x]) x = u;
        }
		info[i].first = x;
        z.pb({x, 0, i});
    }
    sort(all(z), [&] (iii x, iii y) { return lvl[get<0>(x)] > lvl[get<0>(y)]; } );
    for (auto [u, type, gr] : z) {
        bool ok = 0;
        for (auto w : a[gr]) ok |= (used[w]);
        if (!ok) {
			mn++, used[u] = 1;
			info[gr].second = info[gr].first;
			for (auto x : a[gr]) bichos[x].pb(gr);
		}
		else {
			int cnt = 0, cur = 0;
			for (auto w : a[gr]) {
				if (used[w]) {
					if (cnt == 0 or lvl[w] > lvl[cur]) cur = w;
					cnt++;
				}
			}
			int save = cur;
			while (cur != u) cnt -= used[cur], cur = par[cur];
			cnt -= used[u];
			if (cnt == 0) {
				info[gr].second = save;
				for (auto x : a[gr]) if (is_anc(save, x)) bichos[x].pb(gr);
			}
		}
    }
    vector<multiset<int>> mt(n+1);
    vector<int> seg(4*n+10);
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int y, bool type) -> void {
        if (l == r) {
            if (!type) mt[l].erase(mt[l].find(y));
            else mt[l].insert(y);
            seg[i] = (mt[l].empty() ? 0 : (*prev(end(mt[l]))));
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x, y, type);
        else self(self, 2*i+1, md+1, r, x, y, type);
        seg[i] = max(seg[2*i], seg[2*i+1]);
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> int {
        if (r < x or y < l) return 0;
        if (x <= l and r <= y) return seg[i];
        int md = (l+r)/2;
        return max(self(self, 2*i, l, md, x, y), self(self, 2*i+1, md+1, r, x, y));
    };
    vector<int> dp(n), ps(n), stk;
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        stk.pb(u);
        ps[u] = used[u] + ps[p];
        for (auto gr : bichos[u]) {
			auto [x, st] = info[gr];
            if (u != st) upd(upd, 1, 1, n, lvl[p], lvl[x], 0);
            upd(upd, 1, 1, n, lvl[u], lvl[x], 1);
        }
        int w = query(query, 1, 1, n, 1, lvl[u]-1);
        if (used[u]) dp[u] = ps[u];
        else dp[u] = 1 + (w ? dp[stk[w-1]] : 0);
        for (auto V : g[u]) {
            if (V == p) continue;
            self(self, V, u);
        }
        for (auto gr : bichos[u]) {
			auto [x, st] = info[gr];
            if (u != st) upd(upd, 1, 1, n, lvl[p], lvl[x], 1);
            upd(upd, 1, 1, n, lvl[u], lvl[x], 0);
        }
        stk.pop_back();
    };
    dfs(dfs, 0, 0);
    vector<int> ans(q+1, mn);
    for (int i = 0; i < q;++i) {
        int w = v[i][0];
        for (auto& x : v[i]) if (lvl[x] < lvl[w]) w = x;
        z.pb({w, 1, i});
    }
    sort(all(z), [&] (iii x, iii y) { 
        if (get<0>(x) == get<0>(y)) return get<1>(x) < get<1>(y);
        return lvl[get<0>(x)] > lvl[get<0>(y)];
    });
    for (int i = 0; i < n; ++i) used[i] = 0;
    for (auto [u, type, gr] : z) {
        if (type) {
            bool ok = 0;
            for (auto w : v[gr]) ok |= (used[w]);
            if (!ok) ans[gr+1] += (dp[u] != ps[u]);
        } else {
            bool ok = 0;
            for (auto w : a[gr]) ok |= (used[w]);
            if (!ok) used[u] = 1;
        }
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n, m, q; cin >> n >> m >> q;
        vector<vector<int>> g(n);
        for (int i = 0; i < n-1; ++i) {
            int u, v; cin >> u >> v; --u, --v;
            g[u].pb(v), g[v].pb(u);
        }
        vector<vector<int>> a(m), v(q);
        for (auto& w : a) {
            int l; cin >> l;
            w.resize(l);
            for (auto& x : w) cin >> x, --x;
        }
        for (auto& w : v) {
            int l; cin >> l;
            w.resize(l);
            for (auto& x : w) cin >> x, --x;
        }
        auto ans = solve(n, m, q, g, a, v);
        for (auto x : ans) cout << x << endl;
    }
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
