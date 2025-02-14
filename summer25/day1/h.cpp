#include <bits/stdc++.h>
#define sz(x) (int) x.size()
#define pb push_back
using namespace std;
#define fast_io cin.tie(0)->sync_with_stdio(0)
#define endl '\n'
typedef long long ll;

const int MAX = 2e5 + 10;
const int MAXC = 2e5 + 10;
const int BAT = 750;

vector<int> lvl(MAX), pai(MAX), tin(MAX), tout(MAX), id_pai(MAX);

vector<pair<int, int>> g[MAX];
vector<pair<int, int>> arvore;

int _t = 0;
void dfs(int u, int p) {
	arvore.pb({u, 1});
	tin[u] = _t++;
	lvl[u] = lvl[p] + 1;
	pai[u] = p;
	for (auto [v, sexo] : g[u]) if (v != p) {
		id_pai[v] = sexo;
		dfs(v, u);
	}
	tout[u] = _t++;
	arvore.pb({u, 0});
}

vector<int> is_imp(MAXC), is_queried(MAX), resp(MAX);
vector<int> freq(MAXC);
vector<int> color_imp;
vector<vector<int>> freqs(MAX);
int apareceu[MAX], edg_color[MAX], id_cor[MAX];

void pre() {
	for (auto [u, tipo] : arvore) {
		if (tipo == 0) freq[edg_color[id_pai[u]]]--;	
		else {
			if (u) {
				resp[u] = resp[pai[u]];
				freq[edg_color[id_pai[u]]]++;	
				if (is_imp[edg_color[id_pai[u]]] == 0) resp[u] += (freq[edg_color[id_pai[u]]] == 1);
			}
		}
		if (is_queried[u]) for (auto cx : color_imp) freqs[u].push_back(freq[cx]);
	}
}

int32_t main() {
	fast_io;

	int n, k, m;
	cin >> n >> k >> m;
	
	vector<pair<int, int>> edg;
	for (int i = 0; i < n - 1; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		--a, --b, --c;
		edg_color[i] = c;
		g[a].emplace_back(b, i);
		g[b].emplace_back(a, i);
		edg.emplace_back(a, b);
	}

	vector<tuple<int, int, int>> ops(m);
	for (int i = 0; i < m; i++) {
		char t; cin >> t;
		if (t == 'Z') {
			int v; cin >> v; --v;
			ops[i] = tuple(0, v, v);
		} else {
			int j, x;
			cin >> j >> x; --j, --x;
			ops[i] = tuple(1, j, x);
		}
	}

	dfs(0, 0);

	for (int block = 0; block * BAT < m; ++block) {
		color_imp.clear();
		vector<pair<int, int>> updates;
		for (int i = 0; i < max(n, k); ++i) {
			is_imp[i] = 0, freqs[i].clear(), resp[i] = 0, freq[i] = 0, is_queried[i] = 0;
			apareceu[i] = 0;
		}
		for (int j = block * BAT; j < min(m, block*BAT+BAT); ++j) {
			auto [aa, bb, cc] = ops[j];
			if (aa) is_imp[cc] = is_imp[edg_color[bb]] = 1; 
			else is_queried[bb] = 1;
		}
		for (int i = 0; i < k; ++i) if (is_imp[i]) {
			id_cor[i] = color_imp.size(); 
			color_imp.push_back(i);
		}
		pre();
		auto is_inside = [&] (int id, int u) {
			auto [x, y] = edg[id];
			if (lvl[x] < lvl[y]) swap(x, y);
			return (tin[x] <= tin[u] and tin[u] <= tout[x]);
		};
		for (int j = block * BAT; j < min(m, block*BAT+BAT); ++j) {
			auto [aa, bb, cc] = ops[j];
			if (aa) {
				updates.pb({bb, cc});
				continue;
			}
			auto sexo = freqs[bb];
			for (int z = sz(updates)-1; ~z; --z) {
				auto [yy, zz] = updates[z];
				if (apareceu[yy] or !is_inside(yy, bb)) continue;
				sexo[id_cor[edg_color[yy]]]--;
				sexo[id_cor[zz]]++;
				apareceu[yy] = 1;
			}
			int ans = resp[bb];
			for (int i = 0; i < color_imp.size(); ++i) ans += (sexo[i] != 0);
			cout << ans << endl;
			for (int z = sz(updates)-1; ~z; --z) {
				auto [yy, zz] = updates[z];
				apareceu[yy] = 0;
			}
		}
		for (auto [yy, zz] : updates) edg_color[yy] = zz;
	}
}


