#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
#define pb push_back
typedef long long ll;

using ii = pair<int, int>;

namespace cover {
	const int MAX = 1001;
	vector<int> g[MAX];
	bitset<MAX> bs[MAX];
	int n, k;
	void limpa(int _n, int _k) {
		n = _n;
		for (int i = 0; i < n; ++i) g[i].clear(), bs[i] = 0;
		k = _k;
	}
	void add(int i, int j) {
		if (i == j) return;
		n = max({n, i+1, j+1});
		bs[i][j] = bs[j][i] = 1;
	}

	int rec(bitset<MAX> m, int max_pode) {
		if (max_pode < 0) return k+1;
		int ans = 0;
		for (int x = 0; x < n; x++) if (m[x]) {
			bitset<MAX> comp;
			function<void(int)> dfs = [&](int i) {
				comp[i] = 1, m[i] = 0;
				for (int j : g[i]) if (m[j]) dfs(j);
			};
			dfs(x);

			int ma, deg = -1, cyc = 1;
			for (int i = 0; i < n; i++) if (comp[i]) {
				int d = (bs[i]&comp).count();
				if (d <= 1) cyc = 0;
				if (d > deg) deg = d, ma = i;
			}
			if (deg <= 2) { // caminho ou ciclo
				ans += (comp.count() + cyc) / 2;
				continue;
			}
			comp[ma] = 0;

			// ou ta no cover, ou nao ta no cover
			ans += min(1 + rec(comp, max_pode-1-ans), deg + rec(comp & ~bs[ma], max_pode-deg-ans));
			if (ans > max_pode) return k+1;
		}
		return ans;
	}
	void init() {
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; j++)
				if (bs[i][j]) g[i].push_back(j);
	}
	int solve(int u) {
		bitset<MAX> m;
		for (int i = 0; i < n; i++) {
			m[i] = (i != u);
		}
		return rec(m, k-1) + 1;
	}
}
int32_t main() {
	fast_io;
	int t; cin >> t;
	while (t--) {
		int n, m, k; cin >> n >> m >> k;
		map<ii, int> used;
		vector<ii> edg;
		vector<vector<int>> g(n);
		cover::limpa(n, k);
		for (int i = 0; i < m; ++i) {
			int u, v; cin >> u >> v;
			--u, --v;
			if (used[{u, v}]) continue;
			cover::add(u, v);
		}
		int mn = k+1;
		vector<int> ans;
		cover::init();
		for (int i = 0; i < n; ++i) {
			if (cover::g[i].size() == 0) continue;
			int cur = cover::solve(i);
			if (cur < mn) {
				ans.clear();
				ans.push_back(i);
				mn = cur;
				cover::k = mn;
			} else if (cur == mn) {
				ans.push_back(i);
			}
		}
		if (mn <= k) {
			cout << mn << ' ' << ans.size() << endl;
			for (auto x : ans) cout << x + 1 << ' ';
			cout << endl;
		} else {
			cout << -1 << endl;
		}
	}
}



