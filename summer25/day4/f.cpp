#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

const int MAX = 1e6 + 105;

int N;

int32_t main() {
	fast_io
	int n, m; cin >> n >> m;
	vector<vector<int>> grid(n, vector<int>(m));
	for (auto& x : grid) for (auto& y : x) cin >> y;
	auto get = [&] (int i, int j) {
		return m * i + j;
	};
	int a[8] = {1, -1, 0, 0, 0, 0, 1, -1};
	vector<pair<int, int>> ord;
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) ord.emplace_back(i, j);
	sort(begin(ord), end(ord), [&] (pair<int, int> x, pair<int, int> y) {
				return abs(grid[x.first][x.second]) < abs(grid[y.first][y.second]);
			});
	vector<int> par(n*m), lvl(n*m), atv(n*m);
	iota(begin(par), end(par), 0);
	auto findp = [&] (auto&& self, int u) -> int {
		return par[u] = (par[u] == u ? u : self(self, par[u])); 
	};
	auto unite = [&] (int u, int v) {
		u = findp(findp, u), v = findp(findp, v);
		if (u == v) return;
		if (lvl[u] < lvl[v]) swap(u, v);
		par[v] = u;
		if (lvl[u] == lvl[v]) lvl[u]++;
		atv[u] = max(atv[u], atv[v]);
	};
	int ans = 0;
	for (int l = 0, r = 0; l < n*m; l = r) {
		vector<pair<int, int>> caras;
		while (r < n*m and abs(grid[ord[r].first][ord[r].second]) == abs(grid[ord[l].first][ord[l].second])) caras.push_back(ord[r++]);
		for (auto [x, y] : caras) {
			for (int k = 0; k < 4; ++k) {
				int x2 = x + a[k], y2 = y + a[k+4];
				if (min(x2, y2) >= 0 and x2 != n and y2 != m and abs(grid[x2][y2]) <= abs(grid[x][y])) {
					unite(get(x, y), get(x2, y2));
				}
			}
		}
		for (auto [x, y] : caras) {
			if (grid[x][y] > 0 and atv[findp(findp,get(x, y))] == 0) {
				ans++;
				atv[findp(findp, get(x, y))] = 1;
			}
		}
	}
	cout << ans << endl;
}
