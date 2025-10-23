#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

int32_t main() {
	fast_io;

	int n; cin >> n;
	vector<int> f(n);
	vector<int> cnt(n);
	for (auto &i : f) cin >> i, --i, ++cnt[i];

	vector<vector<int>> g(n);
	for (int i = 1; i < n; i++) {
		int u, v; cin >> u >> v; --u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	const int MAGIC = 1;
	vector<vector<int>> prec(n);
	for (int c = 0; c < n; c++) if (cnt[c] >= MAGIC) {
		auto &cur = prec[c]; cur.assign(n, n);
		
		queue<int> q;
		vector<int> dist(n, n);
		for (int i = 0; i < n; i++) if (f[i] == c) {
			q.push(i);
			dist[i] = 0;
		}

		while (q.size()) {
			int u = q.front(); q.pop();
			cur[f[u]] = min(cur[f[u]], dist[u]);
			for (int v : g[u]) if (dist[v] > dist[u] + 1) {
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
	}

	int q; cin >> q;
	while (q--) {
		int x, y; cin >> x >> y; --x, --y;
		x = f[x], y = f[y];

		if (cnt[x] >= MAGIC) cout << prec[x][y] << endl;
		else if (cnt[y] >= MAGIC) cout << prec[y][x] << endl;
		else {
			// sobe
		}
	}

}
