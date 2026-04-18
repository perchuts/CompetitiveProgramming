#include <bits/stdc++.h>
#define int ll
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define pb push_back
//#define gato

using namespace std;

using ll = long long;

const int mod = (1LL << 32);
struct DSU {
    vector<int> par, lazy_add, add;
    vector<vector<int>> comp;
    DSU(int n) {
        par.resize(n);
        lazy_add.resize(n);
        comp.resize(n);
        add.resize(n);
        iota(begin(par), end(par), 0);
		iota(begin(add), end(add), 1);
        for (int i = 0; i < n; ++i) comp[i].pb(i);
    }
    int findp(int u) {
        return par[u] = (par[u] == u ? u : findp(par[u]));
    }
    void merge(int u, int v, int k) {
        // ordem sempre: o U que tem o k
		++k;
        u = findp(u), v = findp(v);
		cout << "unindo comp " << u << " com comp " << v << ", valor = " << k << endl;
        assert(u != v);
        if (comp[u].size() < comp[v].size()) {
            lazy_add[v] += k;
            for (auto x : comp[u]) add[x] += lazy_add[u] - lazy_add[v], comp[v].pb(x);
            par[u] = v;
        } else {
            for (auto x : comp[v]) add[x] += k + lazy_add[v] - lazy_add[u], comp[u].pb(x);
            par[v] = u;
        }
    }
};

int solve(int n, vector<vector<int>> g) {
    int ans = 0;
    vector<pair<int, int>> edg;
    for (int i = 0; i < n; ++i) {
        for (auto j : g[i]) {
            if (i < j) edg.pb({i, j});
        }
    }
    sort(begin(edg), end(edg), [&] (pair<int, int> a, pair<int, int> b) {
        return max(a.first, a.second) < max(b.first, b.second);
    });
    vector<int> add_leq, add_geq;
    DSU ds_leq(n);
    for (auto [u, v] : edg) {
        if (u < v) swap(u, v);
        ds_leq.merge(u, v, u);
		for (int i = 0; i < n; ++i) cout << ds_leq.add[i] + ds_leq.lazy_add[ds_leq.findp(i)] << " \n"[i==n-1];
    }
    add_leq = ds_leq.add;
    for (int i = 0; i < n; ++i) add_leq[i] += ds_leq.lazy_add[ds_leq.findp(i)];
	cout << "add_leq: ";
	for (int i = 0; i < n; ++i) cout << add_leq[i] << " \n"[i==n-1];
    sort(begin(edg), end(edg), [&] (pair<int, int> a, pair<int, int> b) {
        return min(a.first, a.second) > min(b.first, b.second);
    });
    DSU ds_geq(n);
    for (auto [u, v] : edg) {
        if (u > v) swap(u, v);
        ds_geq.merge(u, v, u);
    }
    add_geq = ds_geq.add;
    for (int i = 0; i < n; ++i) add_geq[i] += ds_geq.lazy_add[ds_geq.findp(i)];
	cout << "add_geq: ";
	for (int i = 0; i < n; ++i) cout << add_geq[i] << " \n"[i==n-1];
    for (int i = 0; i < n; ++i) {
        add_leq[i] %= mod;
        add_geq[i] %= mod;
        ans = (ans + add_leq[i] * add_geq[i]) % mod;
    }
    return ans;
}

int solve_n2(int n, vector<vector<int>> g) {
    vector<int> par(n), lvl(n, 1);
    iota(begin(par), end(par), 0);
    auto findp = [&] (auto&& self, int u) -> int { return par[u] = (par[u] == u ? u : self(self, par[u])); };
    auto merge = [&] (int u, int v) {
        u = findp(findp, u), v = findp(findp, v);
        if (lvl[u] < lvl[v]) swap(u, v);
        par[v] = u;
        lvl[u] += lvl[v];
    };
    int ans = 0;
    for (int l = 0; l < n; ++l) {
        iota(begin(par), end(par), 0);
        for (int i = 0; i < n; ++i) lvl[i] = 1;
        for (int r = l; r < n; ++r) {
            for (auto k : g[r]) {
                if (l <= k and k < r) merge(k, r);
            }
            if (findp(findp, l) == findp(findp, r)) ans += lvl[par[l]] * (l+1) * (r+1);
        }
    }
    return ans;
}

int solve_slow(int n, vector<vector<int>> g) {
    vector mn(n, vector(n, n+1));
    vector mx(n, vector(n, -1LL));
    for (int i = 0; i < n; ++i) mn[i][i] = mx[i][i] = i;
    // temos uma solucao em O(N^3)
    auto dfs = [&] (auto&& self, int u, int p, int src) -> void {
        mn[src][u] = min(mn[src][p], u);
        mx[src][u] = max(mx[src][p], u);
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u, src);
        }
    };
    for (int i = 0; i < n; ++i) dfs(dfs, i, i, i);
    int ans = 0;
	vector<vector<int>> score(n+1, vector<int>(n+1));
    for (int l = 0; l < n; ++l) {
        for (int r = l; r < n; ++r) { 
            for (int k = l; k <= r; ++k) {
                if (mn[l][k] == l and mx[l][k] <= r and mx[k][r] == r and mn[k][r] >= l) score[l+1][r+1]++;
            }
        }
    }
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			ans += score[i][j] * i * j;
		}
	}
    return ans;
}

int brute(int n, vector<vector<int>> g) {
    int ans = 0;
    vector<vector<int>> mark(n+1, vector<int>(n+1));
    for (int i = 1; i < (1 << n); ++i) {
        vector<int> bit(n), vis(n);
        int root;
        for (int j = 0; j < n; ++j) {
            if (i >> j & 1) root = j;
            bit[j] = (i >> j & 1);
        }
        vector<int> eu, fronteira;
        auto dfs = [&] (auto&& self, int u, int p) -> void {
            vis[u] = 1;
            eu.pb(u);
            for (auto v : g[u]) {
                if (v == p) continue;
                if (bit[v] == 0) fronteira.pb(v);
                else self(self, v, u);
            }
        };
        dfs(dfs, root, root);
        bool ok = true;
        for (int j = 0; j < n; ++j) ok &= (vis[j] == bit[j]);
        sort(begin(eu), end(eu));
        for (auto w : fronteira) {
            ok &= (w < eu[0] or eu.back() < w);
        }
        if (!ok) continue;
        assert(mark[eu[0]+1][eu.back()+1] == 0);
        mark[eu[0]+1][eu.back()+1] = eu.size();
        ans += (eu[0]+1) * (eu.back()+1) * eu.size();
    }
    return ans;
}
mt19937 rng(time(0));

int rnd(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

int32_t main() {_
#ifndef gato
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<vector<int>> g(n);
        for (int i = 0; i < n-1; ++i) {
            int u, v; cin >> u >> v; --u, --v;
            g[u].pb(v), g[v].pb(u);
        }
        cout << solve_n2(n, g) << endl;
    }
#else
    int t = 1;
    while (t <= 10000) {
        int n = rnd(1, 30);
        vector<vector<int>> g(n);
        vector<int> p(n); iota(begin(p), end(p), 0); shuffle(begin(p), end(p), rng);
        vector<pair<int, int>> edg;
        for (int i = 0; i < n-1; ++i) {
            int u = p[i+1], v = p[rnd(0, i)];
            edg.pb({u, v});
            g[u].pb(v), g[v].pb(u);
        }
		int ans = solve_slow(n, g);
		int my = solve_n2(n, g);
		if (ans != my) {
			cout << "Wrong answer on test " << t << endl;
			cout << n << endl;
			for (auto [u, v] : edg) cout << u + 1 << " " << v+1 << endl;
			cout << "solve: " << my << endl;
			cout << "brute: " << ans << endl;
			exit(0);
		}
		cout << "Accepted on test " << t++ << endl;
    }
#endif
}
