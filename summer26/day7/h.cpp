#include <bits/stdc++.h>
#define int ll
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
using namespace std;

using ll = long long;

const int INF = 1e18;

int solve(){
	int n, l; cin >> l >> n;
	vector<int> b(n);
	for (int i = 0; i < n; ++i) cin >> b[i];
	if (n == 1) {
		if (l % b[0]) return -1;
		return l/b[0];
	}
	sort(b.begin(), b.end());
	b.erase(unique(b.begin(),b.end()), b.end());

	int sz = b.size();
	int m = b.back();
	vector<vector<pair<int,int>>> g(m);
	for (int j = 0; j < sz-1; ++j){
		for (int a = 0; a < m; ++a){
			if (b[j] + a >= m) g[a].pb({b[j] + a - m, 0});
			else g[a].pb({b[j] + a, 1});
		}	
	}

	int ans = l/m;

	deque<int> dq;
	dq.push_back(0);
	const int inf = 1e18;
	vector<int> dist(m, inf), vis(m);
	dist[0] = 0;
	while (!dq.empty()) {
		int u = dq.front(); dq.pop_front();
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto [v, w] : g[u]) {
			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				if (w == 1) dq.push_back(v);
				else dq.push_front(v);
			}
		}
	}
	if (dist[l%m] == inf) return -1;
	ans += dist[l%m];
	return ans;
}

int32_t main() {_
	int t; cin >> t;
	for (int i = 0; i < t; ++i){
		cout << "Case #" << i+1 << ": ";
		int v = solve();
		if (v == -1) cout << "IMPOSSIBLE" << endl;
		else cout << v << endl;
	}

}
