#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

const int INF = 1e18;

template<typename T> struct mcmf {
	struct edge {
		int to, rev, flow, cap;
		bool res;
		T cost;
		edge() : to(0), rev(0), flow(0), cap(0), cost(0), res(false) {}
		edge(int to_, int rev_, int flow_, int cap_, T cost_, bool res_)
			: to(to_), rev(rev_), flow(flow_), cap(cap_), res(res_), cost(cost_) {}
	};

	vector<vector<edge>> g;
	vector<int> par_idx, par;
	T inf;
	vector<T> dist;

	mcmf(int n) : g(n), par_idx(n), par(n), inf(numeric_limits<T>::max()/3) {}
	void add(int u, int v, int w, T cost) {
		edge a = edge(v, g[v].size(), 0, w, cost, false);
		edge b = edge(u, g[u].size(), 0, 0, -cost, true);

		g[u].push_back(a);
		g[v].push_back(b);
	}

	bool dijkstra(int s, int t, vector<T>& pot) {
		priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> q;
		dist = vector<T>(g.size(), inf);
		dist[s] = 0;
		q.emplace(0, s);
		while (q.size()) {
			auto [d, v] = q.top();
			q.pop();
			if (dist[v] < d) continue;
			for (int i = 0; i < g[v].size(); i++) {
				auto [to, rev, flow, cap, res, cost] = g[v][i];
				cost += pot[v] - pot[to];
				if (flow < cap and dist[v] + cost < dist[to]) {
					dist[to] = dist[v] + cost;
					q.emplace(dist[to], to);
					par_idx[to] = i, par[to] = v;
				}
			}
		}
		return dist[t] < inf;
	}

	pair<int, T> max_flow(int s, int t, int flow = INF) {
		vector<T> pot(g.size(), 0);

		int f = 0;
		T ret = 0;
		while (f < flow and dijkstra(s, t, pot)) {
			for (int i = 0; i < g.size(); i++)
				if (dist[i] < inf) pot[i] += dist[i];

			int mn_flow = flow - f, u = t;
			while (u != s) {
				mn_flow = min(mn_flow,
						g[par[u]][par_idx[u]].cap - g[par[u]][par_idx[u]].flow);
				u = par[u];
			}

			ret += pot[t] * mn_flow;

			u = t;
			while (u != s) {
				g[par[u]][par_idx[u]].flow += mn_flow;
				g[u][g[par[u]][par_idx[u]].rev].flow -= mn_flow;
				u = par[u];
			}

			f += mn_flow;
		}

		return make_pair(f, ret);
	}
};

int32_t main() {
	fast_io;

	int n, m, s;
	cin >> n >> m >> s;

	vector<string> _grid(n);
	for (auto &x : _grid) cin >> x;

	vector<vector<int>> grid(n, vector<int>(m));
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
		grid[i][j] = _grid[i][j] - '0';

	vector<tuple<char, int, int, int>> rest(s);
	for (auto &[c, i, j, k] : rest) {
		cin >> c >> i >> j >> k;
		--i, --j;
	}
	
	vector<vector<int>> hor(n, vector<int>(m));	
	vector<vector<int>> vert(n, vector<int>(m));	

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == 0) continue;

			int last = -1;
			for (int id = 0; id < s; id++) {
				auto [c, xi, xj, k] = rest[id];
				if (c == 'H' && xi == i && xj > last && xj < j) {
					last = xj;
					hor[i][j] = id;
				}
			}

			last = -1;
			for (int id = 0; id < s; id++) {
				auto [c, xi, xj, k] = rest[id];
				if (c == 'V' && xj == j && xi > last && xi < i) {
					last = xi;
					vert[i][j] = id;
				}
			}
		}
	}

	vector<int> tot(s);
	for (int i = 0; i < n; i++) {
	for (int j = 0; j < m; j++) {
		if (grid[i][j] == 0) continue;
		int h = hor[i][j];
		tot[h] += grid[i][j];
		int v = vert[i][j];
		tot[v] += grid[i][j];
	}
	}

	mcmf<int> g(s + 2);
	int src = s, snk = s + 1;

	int sum = 0;
	for (int i = 0; i < s; i++) {
		auto [c, xi, xj, k] = rest[i];

		if (c == 'H') {
			if (tot[i] > k) g.add(i, snk, tot[i] - k, 0);
			else g.add(src, i, k - tot[i], 0), sum += k - tot[i];
		} else {
			if (tot[i] > k) g.add(src, i, tot[i] - k, 0), sum -= k - tot[i];
			else g.add(i, snk, k - tot[i], 0);
		}
	}


	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == 0) continue;
			int h = hor[i][j];
			int v = vert[i][j];

			g.add(h, v, 9-grid[i][j], 1);
			g.add(v, h, grid[i][j]-1, 1);
		}
	}
	
	auto [mx, b] = g.max_flow(src, snk);

	if (mx < sum) cout << "IMPOSSIBLE" << endl;
	else cout << b << endl;
}
