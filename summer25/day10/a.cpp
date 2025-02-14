#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

const int MAX = 1e5 + 10;
const int INF = 1e17;

int comp[MAX];
int id[MAX];

int n, m;
int dist[MAX];
vector<pair<int, int>> ar;
vector<int> w;

bool bellman_ford(int a) {
	for (int i = 0; i < n; i++) dist[i] = INF;
	dist[a] = 0;

	for (int i = 0; i <= n; i++) {
		for (int j = 0; j < ar.size(); j++) {
			if (dist[ar[j].second] > dist[ar[j].first] + w[j]) {
				if (i == n) return 1;
				dist[ar[j].second] = dist[ar[j].first] + w[j];
			}
		}
	}

	return 0;
}

void dijkstra(int a) {
	for (int i = 0; i < n; i++) dist[i] = INF;
	dist[a] = 0;

	vector<vector<pair<int, int>>> g(n);
	for (int i = 0; i < ar.size(); i++) {
		auto [a, b] = ar[i];
		int wi = w[i];
		g[a].emplace_back(b, wi);
	}
	
	using T = pair<int, int>;
	priority_queue<T, vector<T>, greater<T>> pq;
	pq.emplace(dist[a], a);
	while (pq.size()) {
		auto [d, u] = pq.top(); pq.pop();
		if (d > dist[u]) continue;
		for (auto [v, wi] : g[u]) {
			if (dist[v] > dist[u] + wi) {
				dist[v] = dist[u] + wi;
				pq.emplace(dist[v], v);
			}
		}
	}
}

void spfa(int s) {
	deque<int> q;
	vector<int> is_inside(n, 0);
	for (int i = 0; i < n; i++) dist[i] = INF;
	dist[s] = 0;

	vector<vector<pair<int, int>>> g(n);
	for (int i = 0; i < ar.size(); i++) {
		auto [a, b] = ar[i];
		int wi = w[i];
		g[a].emplace_back(b, wi);
	}

	q.push_back(s);
	is_inside[s] = true;
	while (q.size()) {
		int u = q.front(); q.pop_front();
		is_inside[u] = false;

		for (auto [v, wi] : g[u]) {
			if (dist[v] > dist[u] + wi) {
				dist[v] = dist[u] + wi;
				if (is_inside[v]) continue;
				if (!q.empty() && dist[v] > dist[q.front()]) q.push_back(v);
				else q.push_front(v);
				is_inside[v] = true;
			}
		}
	}
}

int32_t main() {
	fast_io;

	cin >> n >> m;
	vector<tuple<int, int, int>> edges(m);
	for (auto &[a, b, wi] : edges) {
		cin >> a >> b >> wi;
		--a, --b;
	}

	int tot = 0;
	vector<int> cic(m, true);
	vector<vector<pair<int, int>>> g(n);
	for (int i = 0; i < m; i++) {
		auto [a, b, wi] = edges[i];

		g[a].emplace_back(b, i);
		g[b].emplace_back(a, i);
	}

	vector<int> vis(n, 0);
	stack<int> s;

	int t = 0;
	auto go = [&] (auto&& self, int i, int pai, int pid) -> int { 
		int lo = id[i] = t++;
		s.push(i);
		vis[i] = 2;

		for (auto [j, idx] : g[i]) {
			if (j == pai) continue;
			if (!vis[j]) lo = min(lo, self(self, j, i, idx));
			else if (vis[j] == 2) lo = min(lo, id[j]);
		}

		if (lo == id[i]) {
			if (pid != -1) {
				cic[pid] = false;
			}
			while (1) {
				int u = s.top(); s.pop();
				vis[u] = 1, comp[u] = i;
				if (u == i) break;
			}
		}

		return lo;
	};
	for (int i = 0; i < n; i++) {
		if (!vis[i]) go(go, i, -1, -1);
	}

	fill(vis.begin(), vis.end(), 0);
	auto dfs = [&] (auto&& self, int u) -> void {
		vis[u] = true;
		for (auto [v, idx] : g[u]) {
			if (!vis[v]) {
				if (cic[idx] == false) {
					ar.emplace_back(u, v);
					w.emplace_back(-get<2>(edges[idx]));
				}
				self(self, v);
			}
		}
	};
	dfs(dfs, 0);

	for (int i = 0; i < m; i++) {
		auto [a, b, wi] = edges[i];
		if (cic[i]) {
			ar.emplace_back(a, b);
			ar.emplace_back(b, a);
			w.push_back(wi);
			w.push_back(wi);
		}
	}

	spfa(0);	

	int mn = INF;
	for (int i = 1; i < n; i++) {
		mn = min(mn, dist[i]);
	}

	for (int i = 0; i < m; i++) {
		if (cic[i]) tot += get<2>(edges[i]);
		else tot += 2*get<2>(edges[i]);
	}

	tot += min(0ll, mn);
	cout << tot << endl;
}
