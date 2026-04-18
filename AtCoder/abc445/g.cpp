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
// Kuhn
//
// Computa matching maximo em grafo bipartido
// 'n' e 'm' sao quantos vertices tem em cada particao
// chamar add(i, j) para add aresta entre o cara i
// da particao A, e o cara j da particao B
// (entao i < n, j < m)
// Para recuperar o matching, basta olhar 'ma' e 'mb'
// 'recover' recupera o min vertex cover como um par de
// {caras da particao A, caras da particao B}
//
// O(|V| * |E|)
// Na pratica, parece rodar tao rapido quanto o Dinitz

// Dinitz
//
// O(min(m * max_flow, n^2 m))
// Grafo com capacidades 1: O(min(m sqrt(m), m * n^(2/3)))
// Todo vertice tem grau de entrada ou saida 1: O(m sqrt(n))

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
	int dfs(int v, int s, int f = inf) {
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

void solve() {
    int n, a, b; cin >> n >> a >> b;
    vector<string> grid(n);
    for (auto& x : grid) cin >> x;
    // se a+b eh impar, entao isso corresponde a encontrar o minimum vertex cover do grafo (que eh bipartido!)
    // entao a+b eh par.
    // como resolver?
    vector<vector<int>> g(n*n);
    vector<ii> edg;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '#') continue;
            for (int _1 = 0; _1 < 2; ++_1) {
                for (int _2 = 0; _2 < 2; ++_2) {
                    for (int _3 = 0; _3 < 2; ++_3) {
                        int i2 = i + a, j2 = j + b;
                        if (min(i2, j2) >= 0 and max(i2, j2) < n and grid[i2][j2] == '.') {
                            g[n*i+j].pb(n*i2+j2);
                            if (make_pair(i, j) < make_pair(i2, j2)) {
                                edg.pb({n*i+j, n*i2+j2});
                            }
                        }
                        swap(a, b);
                    }
                    b *= -1;
                }
                a *= -1;
            }
        }
    }
    vector<int> vis(n*n, -1);
    bool ok = 1;
    auto dfs = [&] (auto&& self, int u) -> void {
        for (auto v : g[u]) {
            if (vis[v] == -1) {
                vis[v] = 1 ^ vis[u];
                self(self, v);
            } else if (vis[v] == vis[u]) {
                ok = 0;
            }
        }
    };
    for (int i = 0; i < n*n; ++i) {
        if (grid[i/n][i%n] == '#') continue;
        if (vis[i] == -1) {
            vis[i] = 0;
            dfs(dfs, i);
        }
    }
    if (!ok) return;
    dinitz dz(n*n+2);
    int src = n*n, sink = n*n+1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (vis[n*i+j] == 0) {
                dz.add(src, n*i+j, 1);
            }
            if (vis[n*i+j] == 1) {
                dz.add(n*i+j, sink, 1);
            }
        }
    }
    for (auto [x, y] : edg) {
        if (vis[x] == 1) swap(x, y);
        
        dz.add(x, y, inf);
    }
    auto s = get_cut(dz, src, sink);
    auto ans = grid;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) if (ans[i][j] != '#') ans[i][j] = 'o';
    for (auto [x, y] : s) {
        if (x != src and x != sink) ans[x/n][x%n] = '.';
        if (y != src and y != sink) ans[y/n][y%n] = '.';
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << endl;
    }
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
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
