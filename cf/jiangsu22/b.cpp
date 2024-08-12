#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
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
vector<pair<int, int>> get_cut(dinitz& g) {
	vector<pair<int, int>> cut;
	for (int i = 0; i < g.g.size(); i++) for (auto e : g.g[i])
		if (e.flow == e.cap and e.flow == 1 and !e.res) cut.emplace_back(i, e.to);
	return cut;
}
vector<int> g[10010];
int32_t main() {
	fast_io;
	int n; cin >> n;
	if (n == 2) { cout << -1 << endl; return 0; }
	vector<int> prime(2*n + 1, 1);
	for (int i = 2; i <= 2*n; ++i) {
		if (prime[i] == 0) continue;
		for (int j = i * i; j <= 2*n; j += i) prime[j] = 0;
	}
	dinitz f(n + 10);
	int src = n + 5, sink = n + 6;
	for (int i = 1; i <= n; ++i) {
		if (i % 2 == 0) f.add(src, i, 2);
		else f.add(i, sink, 2);
		for (int j = i + 1; j <= n; ++j) {
			if (prime[i+j]) {
				if (i % 2 == 0) f.add(i, j, 1);
				else f.add(j, i, 1);
			}
		}
	}
	auto mxf = f.max_flow(src, sink);
	if (mxf != n) {
		cout << -1 << endl;
		exit(0);
	}
	auto edg = get_cut(f);
	for (auto [x, y] : edg) g[x].push_back(y), g[y].push_back(x);
	vector<int> vis(n + 1);
	vector<vector<int>> cycles;
	function<void(int)> dfs = [&] (int u) {
		cycles.back().push_back(u);
		vis[u] = 1;
		for (auto v : g[u]) 
			if (!vis[v]) dfs(v);
	};
	for (int i = 1; i <= n; ++i) {
		if (vis[i]) continue;
		cycles.push_back({});
		dfs(i);
	}
	cout << cycles.size() << endl;
	for (auto cycle : cycles) {
		cout << cycle.size() << ' ';
		for (int i = 0; i < cycle.size(); ++i) {
			cout << cycle[i] << " \n"[i == cycle.size()-1];
		}
	}
	return 0;
}

