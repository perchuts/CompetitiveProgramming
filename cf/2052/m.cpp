#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

const int inf = 1e8;

void solve() {
	int n; cin >> n;
	vector<vector<int>> g(2*n);
	vector<int> a(2*n);
	for (auto& x : a) cin >> x, --x;
	for (int i = 1; i < 2*n; ++i) {
		int u, v; cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	vector<vector<int>> dp(2*n, vector<int>(2));
	vector<int> arg_max(2*n, -1);
	auto dfs = [&] (auto&& self, int u, int p) -> void {
		// dp[u][0] = disponivel pra usar
		// dp[u][1] = pareei com o pai
		int sum_0 = 0, best = -inf;
		for (auto v : g[u]) {
			if (v == p) continue;
			self(self, v, u);
			sum_0 += max(dp[v][0], dp[v][1]);
			if (best < dp[v][0] + 1 - max(dp[v][0], dp[v][1])) {
				best = dp[v][0] + 1 - max(dp[v][0], dp[v][1]);
				arg_max[u] = v;
			}
		}
		dp[u][0] = sum_0;
		dp[u][1] = sum_0 + best;
	};
	dfs(dfs, 0, 0);
	vector<pair<int, int>> matching;
	auto rec = [&] (auto&& self, int u, int p, int type) -> void {
		if (type == 0) {
			for (auto v : g[u]) {
				if (v == p) continue;
				if (dp[v][1] >= dp[v][0]) self(self, v, u, 1);
				else self(self, v, u, 0);
			}
			return;
		}
		matching.push_back({u, arg_max[u]});
		self(self, arg_max[u], u, 0);
		for (auto v : g[u]) {
			if (v == p or v == arg_max[u]) continue;
			if (dp[v][1] >= dp[v][0]) self(self, v, u, 1);
			else self(self, v, u, 0);
		}
	};
	if (dp[0][1] >= dp[0][0]) rec(rec, 0, 0, 1);
	else rec(rec, 0, 0, 0);
	vector<vector<int>> appear(n);
	for (int i = 0; i < 2*n; ++i) appear[a[i]].push_back(i);
	vector<int> cnt(n), vis(2*n), pos(2*n, -1), parzinho(2*n), parzinho2(2*n);
	for (int i = 0; i < n; ++i) {
		parzinho2[appear[i][0]] = appear[i][1];
		parzinho2[appear[i][1]] = appear[i][0];
	}
	vector<pair<int, int>> ans;
	int m = matching.size();
	for (int i = 0; i < m; ++i) {
		auto [x, y] = matching[i];
		pos[x] = pos[y] = i;
		cnt[a[x]]++, cnt[a[y]]++;
		parzinho[x] = y, parzinho[y] = x;
	}
	//cout << matching.size() << endl;
	//for (auto [x, y] : matching) cout << x + 1 << ' ' << y + 1 << endl;
	for (int i = 0; i < 2*n; ++i) {
		if (vis[i] or cnt[a[i]] != 1 or pos[i] == -1) continue;
		int cur = i;
		vector<pair<int, int>> edges;
		while (true) {
			int outro = parzinho[cur];
			vis[cur] = vis[outro] = 1;
			edges.push_back({cur, outro});
			if (cnt[a[outro]] == 1) break;
			cur = parzinho2[outro];
		}
		int l = 0, r = (int)edges.size()-1, step = 0;
		//cout << "conjunto: " << endl;
		//for (auto [x, y] : edges) cout << x + 1 << ' ' << y + 1 << endl;
		while (l != r) {
			if (step & 1) {
				ans.emplace_back(edges[l].first, edges[r].first);
				r--;
			} else {
				ans.emplace_back(edges[l].second, edges[r].second);
				l++;
			}
			step ^= 1;
		}
		ans.emplace_back(edges[0].first, parzinho2[edges.back().second]);
	}
	for (int i = 0; i < 2*n; ++i) {
		if (pos[i] == -1 or vis[i]) continue;
		if (a[parzinho[i]] == a[i]) continue;
		int cur = i;
		assert(cnt[a[cur]] == 2);
		vector<pair<int, int>> edges;
		while (!vis[cur]) {
			int outro = parzinho[cur];
			vis[cur] = vis[outro] = 1;
			edges.push_back({cur, outro});
			cur = parzinho2[outro];
		}
		int l = 0, r = (int)edges.size()-1, step = 0;
		//cout << "conjunto: " << endl;
		//for (auto [x, y] : edges) cout << x + 1 << ' ' << y + 1 << endl;
		while (l != r) {
			if (step & 1) {
				ans.emplace_back(edges[l].first, edges[r].first);
				r--;
			} else {
				ans.emplace_back(edges[l].second, edges[r].second);
				l++;
			}
			step ^= 1;
		}
	}
	cout << ans.size() << endl;
	for (auto [x, y] : ans) cout << x + 1 << ' ' << y + 1 << endl;
}
int32_t main() {
	fast_io;
	int t; cin >> t;
	while (t--) {
		solve();
	}
}
