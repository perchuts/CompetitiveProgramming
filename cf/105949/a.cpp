#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

int dist[303][303 * 202];

int32_t main() {
	fast_io;

	int t; cin >> t;
	while (t--) {
		int n, m; cin >> n >> m;

		vector<vector<tuple<int, int, int>>> g(n);
		for (int i = 0; i < m; i++) {
			int u, v, a, b; cin >> u >> v >> a >> b;
			--u, --v;
			g[u].push_back({v, a, b});
		}

		const int N = 202 * n;
		for (int i = 0; i < n; i++) for (int j = 0; j < N; j++) dist[i][j] = int(1e18);
		dist[0][0] = 0;
		using T = tuple<int, int, int>;
		priority_queue<T, vector<T>, greater<>> pq;
		pq.emplace(0, 0, 0);
		for (int a = 0; a < N; a++) {
			for (int u = 0; u < n; u++) {
				for (auto [v, na, nb] : g[u]) {
					if (a + na < N) {
						if (dist[v][a + na] > dist[u][a] + nb) {
							dist[v][a + na] = dist[u][a] + nb;
						}
					}
				}
			}
		}

		int ans = 1e18;
		int ans_a = -1, ans_b = -1;
		for (int a = 0; a < N; a++) {
			if (dist[n - 1][a] != int(1e18)) {
				int b = dist[n - 1][a];
				if (a * b < ans) {
					ans = a * b;
					ans_a = a;
					ans_b = b;
				}
			}
		}

		cout << ans_a << " " << ans_b << endl;
	}
}
