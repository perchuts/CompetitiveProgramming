#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define endl '\n'
#define pb push_back
using namespace std;

using ll = long long;

int32_t main() {_
	int n, m; cin >> n >> m;
	vector<vector<pair<int, int>>> g(n);
	for (int i = 0; i < m; ++i) {
		int u, v, w; cin >> u >> v >> w;
		g[u].pb({v, w});
		g[v].pb({u, w});
	}
	int inf = 1e18;
	auto get = [&] (int src) {
		vector<int> dist(n, inf);
		dist[src] = 0;
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
		pq.push({0, src});
		while (!pq.empty()) {
			auto [d, u] = pq.top(); pq.pop();
			if (d != dist[u]) continue;
			for (auto [v, w] : g[u]) {
				if (dist[v] > dist[u] + w) {
					dist[v] = dist[u] + w;
					pq.push({dist[v], v});
				}
			}
		}
		return dist;
	};
	vector<array<int, 3>> bichos(n);
	vector<int> vals;
	for (int i = 0; i < 3; ++i) {
		auto dist = get(i);
		for (int j = 0; j < n; ++j) bichos[j][i] = dist[j], vals.push_back(dist[j]);
	}
	sort(begin(vals), end(vals));
	vals.erase(unique(begin(vals), end(vals)), end(vals));
	int N = vals.size();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 3; ++j) {
			// 1 indexado
			bichos[i][j] = lower_bound(begin(vals), end(vals), bichos[i][j]) - begin(vals) + 1;
		}
	}
	vector<int> bad(n);
	auto process = [&] () {
		vector<int> ord(n); iota(begin(ord), end(ord), 0);
		sort(begin(ord), end(ord), [&] (int x, int y) { return bichos[x][0] < bichos[y][0]; });
		vector<int> bit(N+1, inf);
		auto add = [&] (int x, int k) {
			while (x <= N) bit[x] = min(bit[x], k), x += x & (-x);
		};
		auto query = [&] (int x) {
			int ans = inf;
			while (x) ans = min(ans, bit[x]), x -= x & (-x);
			return ans;
		};
		for (int l = 0, r = 0; r != n; l = r) {
			vector<int> now;
			while (r != n and bichos[ord[l]][0] == bichos[ord[r]][0]) now.push_back(ord[r++]);
			for (auto i : now) {
				int opt = query(bichos[i][1]);
				if (opt <= bichos[i][2]) bad[i] = 1;
			}
			for (auto i : now) add(bichos[i][1], bichos[i][2]);
		}
	};
	for (int vai = 0; vai < 3; ++vai) {
		for (int i = 0; i < n; ++i) swap(bichos[i][0], bichos[i][vai]);
		process();
		for (int i = 0; i < n; ++i) swap(bichos[i][0], bichos[i][vai]);
	}
	int ans = 0;
	for (int i = 0; i < n; ++i) ans += (bad[i] == 0);
	cout << ans << endl;
}
