#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;

int32_t main() {_
	int n, m, c; cin >> n >> m >> c;
	vector<int> score(n+m), alive(n+m, 1);
	vector<vector<int>> g(n+m);
	for (int i = 0; i < m; ++i) {
		int x; cin >> x;
		g[i].resize(x);
		for (auto& j : g[i]) cin >> j, --j, j += m, g[j].pb(i), score[i]++, score[j]++;
	}
	queue<int> q;
	for (int i = m; i < n+m; ++i) if (score[i] < c) q.push(i), alive[i] = 0;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (auto v : g[u]) {
			if (!alive[v]) continue;
			score[v]--;
			if (v < m and score[v] * 2 < (int)g[v].size()) alive[v] = 0, q.push(v);
			if (v >= m and score[v] < c) alive[v] = 0, q.push(v);
		}
	}
	vector<int> ans;
	for (int i = m; i < n+m; ++i) if (alive[i]) ans.push_back(i-m+1);
	if (ans.empty()) {
		cout << "impossible" << endl;
		return 0;
	}
	cout << "possible" << endl;
	cout << ans.size() << endl;
	for (auto x : ans) cout << x << " ";
	cout << endl;
}
