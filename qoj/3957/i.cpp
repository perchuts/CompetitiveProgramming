#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;

int32_t main() {_
	int n; cin >> n;
	int m; cin >> m;
	vector<vector<int>> g(n);
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	auto bfs = [&] (int s) {
		vector<int> dist(n, n);
		queue<int> q;
		dist[s] = 0;
		q.push(s);
		while (q.size()) {
			int u = q.front(); q.pop();
			for (int v : g[u]) {
				if (dist[v] > dist[u] + 1) {
					dist[v] = dist[u] + 1;
					q.push(v);
				}
			}
		}
		return dist;
	};

	auto d1 = bfs(0);
	auto dn = bfs(n - 1);

	bool ok = false;
	for (int u = 0; u < n; u++) {
		for (int v : g[u]) {
			ok |= d1[u] + 1 + dn[v] == d1[n - 1] + 1;
		}
	}
	cout << (ok ? "" : "im") << "possible\n";
}
