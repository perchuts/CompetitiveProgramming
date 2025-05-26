#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
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
// Dinitz
//
// O(min(m * max_flow, n^2 m))
// Grafo com capacidades 1: O(min(m sqrt(m), m * n^(2/3)))
// Todo vertice tem grau de entrada ou saida 1: O(m sqrt(n))
const int INF = inf;
struct dinitz {
	const bool scaling = false; // com scaling -> O(nm log(MAXCAP)),
	int lim;                    // com constante alta
	struct edge {
		int to, cap, rev, flow;
		bool res;
		edge(int to_, int cap_, int rev_, bool res_)
			: to(to_), cap(cap_), rev(rev_), flow(0), res(res_) {}
	};

	vector<vector<edge>> g;
	vector<int> lev, beg;
	ll F;
	dinitz(int n) : g(n), F(0) {}

	void add(int a, int b, int c) {
		g[a].emplace_back(b, c, g[b].size(), false);
		g[b].emplace_back(a, 0, g[a].size()-1, true);
	}
	bool bfs(int s, int t) {
		lev = vector<int>(g.size(), -1); lev[s] = 0;
		beg = vector<int>(g.size(), 0);
		queue<int> q; q.push(s);
		while (q.size()) {
			int u = q.front(); q.pop();
			for (auto& i : g[u]) {
				if (lev[i.to] != -1 or (i.flow == i.cap)) continue;
				if (scaling and i.cap - i.flow < lim) continue;
				lev[i.to] = lev[u] + 1;
				q.push(i.to);
			}
		}
		return lev[t] != -1;
	}
	int dfs(int v, int s, int f = INF) {
		if (!f or v == s) return f;
		for (int& i = beg[v]; i < g[v].size(); i++) {
			auto& e = g[v][i];
			if (lev[e.to] != lev[v] + 1) continue;
			int foi = dfs(e.to, s, min(f, e.cap - e.flow));
			if (!foi) continue;
			e.flow += foi, g[e.to][e.rev].flow -= foi;
			return foi;
		}
		return 0;
	}
	ll max_flow(int s, int t) {
		for (lim = scaling ? (1<<30) : 1; lim; lim /= 2)
			while (bfs(s, t)) while (int ff = dfs(s, t)) F += ff;
		return F;
	}
};

// Recupera as arestas do corte s-t
vector<pair<int, int>> get_cut(dinitz& g, int s, int t) {
	g.max_flow(s, t);
	vector<pair<int, int>> cut;
	vector<int> vis(g.g.size(), 0), st = {s};
	vis[s] = 1;
	while (st.size()) {
		int u = st.back(); st.pop_back();
		for (auto e : g.g[u]) if (!vis[e.to] and e.flow < e.cap)
			vis[e.to] = 1, st.push_back(e.to);
	}
	for (int i = 0; i < g.g.size(); i++) for (auto e : g.g[i])
		if (vis[i] and !vis[e.to] and !e.res) cut.emplace_back(i, e.to);
	return cut;
}
void solve(){
    int n; cin >> n;
    vector<int> cnt(5);
    for (auto& x : cnt) cin >> x;
    vector<vector<int>> adj_c(5);
    vector<int> adj_v(n);
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        for (int j = 0; j < x; ++j) {
            int k; cin >> k;
            --k;
            adj_c[k].pb(i);
            adj_v[i] |= (1 << k);
        }
    }
    vector<vector<int>> g(n);
    vector<int> lvl(n), pai(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    auto pre = [&] (auto&& self, int u, int p) -> void {
        lvl[u] = lvl[p] + 1, pai[u] = p;
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
        }
    };
    pre(pre, 0, 0);
    auto get = [&] (int u, int v) {
        int _u = u, _v = v;
        while (lvl[_u] > lvl[_v]) _u = pai[_u];
        while (lvl[_u] < lvl[_v]) _v = pai[_v];
        while (_u != _v) _u = pai[_u], _v = pai[_v];
        int lca = _u;
        vector<int> p1, p2;
        while (u != lca) p1.pb(u), u = pai[u];
        while (v != lca) p2.pb(v), v = pai[v];
        p2.pb(lca);
        reverse(all(p2));
        for (auto x : p2) p1.pb(x);
        return p1;
    };
    vector<vector<int>> path;
    int p; cin >> p;
    for (int i = 0; i < p; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        path.pb(get(u, v));
        if (sz(path.back()) > 5) {
            cout << -1 << endl;
            exit(0);
        }
    }
    vector<vector<vector<ii>>> valid(p);
    vector<int> pot(6, 1);
    //for (int i = 0; i < p; ++i) {
    //    cout << "path: ";
    //    for (auto x : path[i]) csout << x+1 << ' ';
    //    cout << endl;
    //    cout << "valid choices: ";
    //    cout << sz(valid[i]) << endl;
    //    for (auto x : valid[i]) {
    //        for (auto [y, z] : x) cout << z << ' ';
    //        cout << endl;
    //    }
    //}
    //cout.flush();
    for (int i = 1; i <= 5; ++i) pot[i] = 5 * pot[i-1];
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < pot[sz(path[i])]; ++j) {
            bool ok = 1;
            int eu = j % 5;
            vector<ii> bicho; bicho.pb({path[i][0], eu});
            for (int k = 1; k < sz(path[i]); ++k) {
                int w = (j / pot[k]) % 5;
                bicho.pb({path[i][k], w});
                ok &= (eu < w), eu = w;
            }
            if (ok) {
                for (auto [x, y] : bicho) ok &= (adj_v[x] >> y & 1);
                if (ok) valid[i].pb(bicho);
            }
        }
    }
    vector<int> color(n, -1);
    vector<int> tam_viz(32), vis(n), fudido(n);
    int fixado = 0;
    for (int i = 0; i < p; ++i) {
        for (auto u : path[i]) fudido[u] = 1;
    }
    for (int i = 0; i < n; ++i) fixado += fudido[i];
    for (int i = 1; i < 32; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (i >> j & 1) {
                for (auto u : adj_c[j]) {
                    if (fudido[u]) continue;
                    vis[u] = 1;
                }
            }
        }
        for (int j = 0; j < n; ++j) tam_viz[i] += vis[j], vis[j] = 0;
    }
    int tudo = 31;
    auto go = [&] (auto&& self, int i) -> int {
        if (i == p) {
            // calculate min cut
            for (int cortar = 0; cortar < 32; ++cortar) {
                int tot = tam_viz[tudo - cortar];
                for (int j = 0; j < 5; ++j) {
                    if (cortar >> j & 1) tot += cnt[j];
                }
                if (tot < n-fixado) return false;
            }
            return true;
        }
        // save
        vector<int> bef, cnt_b = cnt;
        for (auto x : path[i]) bef.pb(color[x]);
        int id = 0;
        for (auto vals : valid[i]) {
            bool ok = 1;
            for (auto [node, cor] : vals) {
                if (color[node] != -1 and color[node] != cor) { ok = 0; break; }
                if (color[node] == -1) {
                    if (cnt[cor] == 0) { ok = 0; break; }
                    cnt[cor]--, color[node] = cor;
                }
            }
            if (ok and self(self, i+1)) return true;
            // undo
            for (int j = 0; j < sz(path[i]); ++j) color[path[i][j]] = bef[j];
            cnt = cnt_b;
        }
        return false;
    };
    if (!go(go, 0)) {
        cout << -1 << endl;
        exit(0);
    }
    //for (auto x : color) cout << x+1 << ' ';
    //cout << endl;
    //cout.flush();
    dinitz dz(n+7);
    int src = n+5, sink = n+6;
    for (int i = 0; i < 5; ++i) {
        if (cnt[i]) dz.add(src, n+i, cnt[i]);
        for (auto u : adj_c[i]) if (color[u] == -1) dz.add(n+i, u, 1);
    }
    for (int i = 0; i < n; ++i) if (color[i] == -1) dz.add(i, sink, 1);
    int k = dz.max_flow(src, sink);
    assert(k == n - fixado);
    for (int i = 0; i < 5; ++i) {
        for (auto e : dz.g[n+i]) {
            if (e.res == 0 and e.flow == 1) color[e.to] = i;
        }
    }
    for (int i = 0; i < n; ++i) {
        assert(color[i] != -1);
        cout << color[i] + 1 << ' ';
    }
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
