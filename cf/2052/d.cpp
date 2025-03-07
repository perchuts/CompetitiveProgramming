#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;

	int n; cin >> n;
	vector<pair<int, int>> a(n);
	for (auto &[x, y] : a) {
		string s, t;
		cin >> s >> t;
		
		x = s == "set";
		y = t == "true";
	}
	
	int m; cin >> m;
	vector<vector<int>> g(n);
	vector<int> indeg(n, 0);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v; --u, --v;

		g[u].push_back(v);
		++indeg[v];
	}

	queue<int> q;
	for (int i = 0; i < n; i++) {
		if (indeg[i] == 0) {
			q.push(i);
		}
	}

	int val = 0;

	array<int, 2> seen = {-1, -1};
	array<queue<int>, 2> st;

	vector<int> ord;	
	while (true) {
		while (q.size()) {
			int u = q.front(); q.pop();

			auto [op, w] = a[u];
			if (w) {
				if (seen[op] != -1) {
					cout << -1 << endl;
					return 0;
				}
				seen[op] = u;
			} else {
				st[op].push(u);
			}
		}

		while (st[val].size()) {
			int u = st[val].front(); st[val].pop();
			ord.push_back(u);
			for (int v : g[u]) {
				--indeg[v];
				if (indeg[v] == 0) q.push(v);
			}
		}

		if (q.empty()) {
			if (seen[!val] != -1) {
				int u = seen[!val];
				ord.push_back(u);
				seen[!val] = -1;
				for (int v : g[u]) {
					--indeg[v];
					if (indeg[v] == 0) q.push(v);
				}
				val = 1 - val;
			} else break;
		}
	}

	if (ord.size() != n) {
		cout << -1 << endl;
		return 0;
	}

	for (auto i : ord) cout << i+1 << " ";
	cout << endl;
}
