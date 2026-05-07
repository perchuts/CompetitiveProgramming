#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
// 2-SAT
//
// solve() retorna um par, o first fala se eh possivel
// atribuir, o second fala se cada variavel eh verdadeira
//
// O(|V|+|E|) = O(#variaveis + #restricoes)

struct sat {
	int n, tot;
	vector<vector<int>> g;
	vector<int> vis, comp, id, ans;
	stack<int> s;

	sat() {}
	sat(int n_) : n(n_), tot(n), g(2*n) {}

	int dfs(int i, int& t) {
		int lo = id[i] = t++;
		s.push(i), vis[i] = 2;
		for (int j : g[i]) {
			if (!vis[j]) lo = min(lo, dfs(j, t));
			else if (vis[j] == 2) lo = min(lo, id[j]);
		}
		if (lo == id[i]) while (1) {
			int u = s.top(); s.pop();
			vis[u] = 1, comp[u] = i;
			if ((u>>1) < n and ans[u>>1] == -1) ans[u>>1] = ~u&1;
			if (u == i) break;
		}
		return lo;
	}

	void add_impl(int x, int y) { // x -> y = !x ou y
		x = x >= 0 ? 2*x : -2*x-1;
		y = y >= 0 ? 2*y : -2*y-1;
		g[x].push_back(y);
		g[y^1].push_back(x^1);
	}
	void add_cl(int x, int y) { // x ou y
		add_impl(~x, y);
	}
	void add_xor(int x, int y) { // x xor y
		add_cl(x, y), add_cl(~x, ~y);
	}
	void add_eq(int x, int y) { // x = y
		add_xor(~x, y);
	}
	void add_true(int x) { // x = T
		add_impl(~x, x);
	}
	void at_most_one(vector<int> v) { // no max um verdadeiro
		g.resize(2*(tot+v.size()));
		for (int i = 0; i < v.size(); i++) {
			add_impl(tot+i, ~v[i]);
			if (i) {
				add_impl(tot+i, tot+i-1);
				add_impl(v[i], tot+i-1);
			}
		}
		tot += v.size();
	}

	pair<bool, vector<int>> solve() {
		ans = vector<int>(n, -1);
		int t = 0;
		vis = comp = id = vector<int>(2*tot, 0);
		for (int i = 0; i < 2*tot; i++) if (!vis[i]) dfs(i, t);
		for (int i = 0; i < tot; i++)
			if (comp[2*i] == comp[2*i+1]) return {false, {}};
		return {true, ans};
	}
}; 

void first_solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    vector<int> c(n);
    for (auto& x : c) cin >> x, --x;
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    auto get_small_sides = [&] () {
        vector<int> vis(n);
        vector<vector<int>> lv(2);
        auto dfs = [&] (auto&& self, int u, int lvl) -> void {
            lv[lvl].pb(u), vis[u] = 1;
            for (auto v : g[u]) {
                if (!vis[v]) self(self, v, lvl ^ 1);
            }
        };
        vector<int> caras;
        for (int i = 0; i < n; ++i) {
            if (vis[i]) continue;
            lv[0].clear(), lv[1].clear();
            dfs(dfs, i, 0);
            int choice = (sz(lv[1]) < sz(lv[0]));
            for (auto x : lv[choice]) caras.pb(x);
        }
        return caras;
    };
    auto z = get_small_sides();
    vector<int> hint;
    for (auto x : z) hint.pb(c[x]);
    cout << sz(hint) << endl;
    for (auto x : hint) cout << x + 1 << endl;
}

void second_solve() {
    int n, m, k; cin >> n >> m >> k;
    vector<vector<int>> g(n);
    vector<int> a(k);
    for (auto& x : a) cin >> x, --x;
    vector<ii> edg;
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        edg.pb({u, v});
        g[u].pb(v), g[v].pb(u);
    }
    auto get_small_sides = [&] () {
        vector<int> vis(n);
        vector<vector<int>> lv(2);
        auto dfs = [&] (auto&& self, int u, int lvl) -> void {
            lv[lvl].pb(u), vis[u] = 1;
            for (auto v : g[u]) {
                if (!vis[v]) self(self, v, lvl ^ 1);
            }
        };
        vector<int> caras;
        for (int i = 0; i < n; ++i) {
            if (vis[i]) continue;
            lv[0].clear(), lv[1].clear();
            dfs(dfs, i, 0);
            int choice = (sz(lv[1]) < sz(lv[0]));
            for (auto x : lv[choice]) caras.pb(x);
        }
        return caras;
    };
    auto z = get_small_sides();
    assert(sz(z) == k);
    vector<int> ans(n, -1);
    for (int i = 0; i < k; ++i) ans[z[i]] = a[i];
    sat sexo(3*n); 
    vector<int> viz(n, -1);
    for (auto [u, v] : edg) {
        for (int i = 0; i < 3; ++i) {
            sexo.add_impl(n*i+u, ~(n*i+v));
            sexo.add_impl(n*i+v, ~(n*i+u));
        }
        if (ans[u] != -1) viz[v] = u;
        if (ans[v] != -1) viz[u] = v;
    }
    for (int i = 0; i < n; ++i) {
        if (ans[i] != -1) {
            sexo.add_true(n*ans[i]+i);
            for (int j = 0; j < 3; ++j) if (j != ans[i]) sexo.add_true(~(n*j+i));
        }
        else if (viz[i] == -1) sexo.add_true(i), sexo.add_true(~(n+i)), sexo.add_true(~(2*n+i));
        else {
            int nao_cor = ans[viz[i]];
            vector<int> cc;
            for (int j = 0; j < 3; ++j) if (j != nao_cor) cc.pb(j);
            sexo.add_xor(cc[0]*n+i, cc[1]*n+i);
            sexo.add_true(~(nao_cor*n+i));
        }
    }
    auto [can, solution] = sexo.solve();
    assert(can);
    for (int i = 0; i < n; ++i) {
        if (ans[i] == -1) {
            if (solution[i]) ans[i] = 0;
            else if (solution[n+i]) ans[i] = 1;
            else assert(solution[2*n+i]), ans[i] = 2;
        }
    }
    for (auto x : ans) cout << x + 1 << " ";
    cout << endl;
}

void solve() {
    string s; cin >> s;
    if (s == "first") {
        int t; cin >> t;
        while (t--) first_solve();
    }
    else {
        int t; cin >> t;
        while (t--) second_solve();
    }
}

int32_t main() {_
#ifndef gato
    solve();
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
