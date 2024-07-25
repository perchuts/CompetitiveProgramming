#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 4e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

vector<int> g[maxn], gi[maxn]; // grafo invertido
int vis[maxn];
stack<int> S;
int comp[maxn], tam[maxn]; // componente conexo de cada vertice

void dfs(int k) {
	vis[k] = 1;
	for (int i = 0; i < (int) g[k].size(); i++)
		if (!vis[g[k][i]]) dfs(g[k][i]);

	S.push(k);
}

void scc(int k, int c) {
	vis[k] = 1, comp[k] = c, tam[c] += (c!=k?tam[k]:0);
	for (int i = 0; i < (int) gi[k].size(); i++)
		if (!vis[gi[k][i]]) scc(gi[k][i], c);
}

void kosaraju(vector<ii> &nodes, vector<iii> &edges) {
	for (auto [x, y, z] : edges) g[x].pb(y), gi[y].pb(x);
	for (auto [x, y] : nodes) tam[x] = y;
	for (auto [x, y] : nodes) if (!vis[x]) dfs(x);
	for (auto [x, y] : nodes) vis[x] = 0;
	while (S.size()) {
		int u = S.top();
		S.pop();
		if (!vis[u]) scc(u, u);
	}
	for (auto [x, y] : nodes) vis[x] = 0, g[x].clear(), gi[x].clear();
}

int aparece[maxn];
ll resp[maxn];

void dnc(vector<ii> &nodes, vector<iii> &edges, int L, int R, ll ans) {
	for (auto [x, y] : nodes) aparece[x] = tam[x] = vis[x] = 0, comp[x] = -1;
	int md = (L + R) / 2;
	vector<iii> left_edges, right_edges;
	vector<ii> right_nodes, left_nodes;
	for (int i = 0; i < sz(edges); ++i) {
		auto [x,y,z] = edges[i];
		if (z <= md) left_edges.pb(edges[i]), aparece[x] |= 1, aparece[y] |= 1;
	}
	
	for (auto [x, y] : nodes) if (aparece[x]) left_nodes.push_back({x, y});
	kosaraju(left_nodes, left_edges);
	ll new_ans = ans;
	for (auto [u, tt] : left_nodes) {
		if (comp[u] == u) {
			if (tt != tam[u]) new_ans += ll(tam[u]) * tam[u] - (tt > 1 ? ll(tt) * tt : 0);
		} else if (tt != 1) new_ans -= ll(tt) * tt;
	}
	for (auto [x, y] : left_nodes) aparece[x] = 0;
	if (L == R) {
		resp[L] = new_ans;
		return;
	}
	left_edges.clear();
	left_nodes.clear();
	for (auto [x, y, z] : edges) {
		if (z <= md && comp[x] == comp[y]) {
			left_edges.pb({x, y, z});
			aparece[x] |= 1;
			aparece[y] |= 1;
		}
		else {
			int actX = (comp[x] == -1 ? x : comp[x]);
			int actY = (comp[y] == -1 ? y : comp[y]);
			right_edges.pb({actX, actY, z});
			aparece[actX] |= 2;
			aparece[actY] |= 2;
		}
	}
	for (auto [u, tt] : nodes) {
		if (aparece[u]&1) left_nodes.push_back({u, tt});
		if (aparece[u]&2) {
			if (comp[u] != -1) assert(u == comp[u]);
			right_nodes.push_back({u, max(tt, tam[u])});
		}
	}
	dnc(left_nodes, left_edges, L, md, ans), dnc(right_nodes, right_edges, md+1, R, new_ans);
}

int32_t main(){_
	int n, m, q; cin >> n >> m >> q;
	vector<iii> edg;
	for (int i = 0; i < q; ++i) {
		int x, y; cin >> x >> y; y += n; --x, --y;
		char c; cin >> c;
		if (c == 'R') edg.pb({y, x, i});
		else edg.pb({x, y, i});
	}
	vector<ii> nodes;
	for (int i = 0; i < n + m; ++i) nodes.pb({i, 1});
	dnc(nodes, edg, 0, q-1, 0);
	for (int i = 0; i < q; ++i) cout << resp[i] << endl;
}
