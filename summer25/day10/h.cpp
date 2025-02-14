#include <bits/stdc++.h>
using namespace std;

#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

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

	vector<T> spfa(int s) {
		deque<int> q;
		vector<bool> is_inside(g.size(), 0);
		dist = vector<T>(g.size(), inf);

		dist[s] = 0;
		q.push_back(s);
		is_inside[s] = true;

		while (!q.empty()) {
			int v = q.front();
			q.pop_front();
			is_inside[v] = false;

			for (int i = 0; i < g[v].size(); i++) {
				auto [to, rev, flow, cap, res, cost] = g[v][i];

				if (flow < cap and dist[v] + cost < dist[to]) {
					dist[to] = dist[v] + cost;

					if (is_inside[to]) continue;
					if (!q.empty() and dist[to]>dist[q.front()]) q.push_back(to);
					else q.push_front(to);
					is_inside[to] = true;
				}
			}
		}
		return dist;
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

	pair<int, T> min_cost_flow(int s, int t, int flow = 2) {
		vector<T> pot(g.size(), 0);
		pot = spfa(s);

		int f = 0;
		T ret = 0;
		while (f < flow and dijkstra(s, t, pot)) {
			for (int i = 0; i < g.size(); i++)
				if (dist[i] < inf) pot[i] += dist[i];

			int mn_flow = flow - f, u = t;
			while (u != s) {
				mn_flow = min(mn_flow,
						g[par[u]][par_idx[u]].cap -
						g[par[u]][par_idx[u]].flow);
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

	int n, m;
	cin >> n >> m;

	vector<vector<int>> grid(n, vector<int>(m));
	for (auto& x : grid) for (auto& y : x) cin >> y;

	auto get = [&] (int i, int j) {
		return i * m + j;
	};
	auto in = [&] (int i, int j) {
		return get(i, j);
	};
	auto out = [&] (int i, int j) {
		return n*m + get(i, j);
	};

	mcmf<int> mf(2*n*m);

	using T = pair<int, int>;
	const int N = 2*n*m;
	vector<vector<T>> g(N); // {v, cost}

	vector<tuple<int, int, int>> edges;
	//mf.add(in(0, 0), out(0, 0), 2, 0);
	//mf.add(in(n-1, m-1), out(n-1, m-1), 2, 0);

	for (int i = 1; i < n; i++) {
		for (int j = 0; j < m; j++) {
			edges.emplace_back(out(i - 1, j), in(i, j), 0);
			//mf.add(out(i - 1, j), in(i, j), 1, 0);
		}
	}
	for (int j = 1; j < m; j++) {
		for (int i = 0; i < n; i++) {
			edges.emplace_back(out(i, j - 1), in(i, j), 0);
			//mf.add(out(i, j - 1), in(i, j), 1, 0);
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (i == 0 && j == 0) continue;
			if (i == n-1 && j == m-1) continue;
			//mf.add(in(i, j), out(i, j), 1, -grid[i][j]);
			edges.emplace_back(out(i, j), in(i, j), -grid[i][j]);
		}
	}

	const int inf = 1e9;
	int ret = 0;
	set<pair<int, int>> st;
	for (int it = 0; it < 2; it++) {
		for (int i = 0; i < N; i++) g[i].clear();
		for (auto [u, v, w] : edges) {
			if (!st.count({u, v})) {
				g[u].emplace_back(v, w);
			} else {
				g[v].emplace_back(u, w);
			}
		}
		g[in(0, 0)].emplace_back(out(0, 0), 0);
		g[in(n-1, m-1)].emplace_back(out(n-1, m-1), 0);

		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
		vector<int> dist = vector<int>(g.size(), inf);
		vector<pair<int, int>> par(N, pair(-1, -1));
		dist[0] = 0;
		q.emplace(0, 0);
		while (q.size()) {
			auto [d, u] = q.top();
			q.pop();
			if (d > dist[u]) continue;

			cout << u << " " << par[u].first << endl;
			cout.flush();

			for (auto [v, w] : g[u]) {
				if (dist[v] > dist[u] + w) {
					dist[v] = dist[u] + w;
					par[v] = {u, w};
					q.emplace(dist[v], v);
				}
			}
		}

		int at = out(n - 1, m - 1);
		while (at != 0) {
			auto [p, w] = par[at];
			st.insert({p, at});
			ret += w;
			at = par[at].first;
		}
	}

	cout << -ret << endl;
}
