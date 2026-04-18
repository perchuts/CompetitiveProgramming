#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll
using namespace std;

using ll = long long;

int32_t main() {_ 
	while (true) {
		int n, k, m; cin >> n >> k >> m;
		if (n == -1) break;
		vector<int> chave(n, -1), porta(n, -1);
		for (int i = 0; i < k; ++i) {
			int u, v; cin >> u >> v; --u, --v;
			chave[u] = v;
			porta[v] = u;
		}
		vector<vector<int>> g(n);
		for (int i = 0; i < m; ++i) {
			int u, v; cin >> u >> v; --u, --v;
			g[u].pb(v), g[v].pb(u);
		}
		queue<int> q;
		vector<int> waiting(n), vis(n);
		q.push(0);
		// vis[i] = 1 se i ja ta na queue
		vis[0] = 1;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (auto v : g[u]) {
				if (vis[v]) continue;
				if (porta[v] != -1) {
					if (vis[porta[v]]) {
						vis[v] = 1;
						q.push(v);
					} else {
						waiting[v] = 1;
					}
				} else {
					q.push(v);
					vis[v] = 1;
					if (chave[v] != -1 and waiting[chave[v]]) {
						vis[chave[v]] = 1;
						q.push(chave[v]);
					}
				}
			}
		}
		cout << "NY"[vis[n-1]] << endl;
	}
}
