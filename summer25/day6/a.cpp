#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;

	int n; cin >> n;
	vector<vector<int>> g(n);
	for (int i = 0; i < n; i++) {
		int m; cin >> m;
		g[i].resize(m);
		for (int &j : g[i]) cin >> j;
	}

	vector<int> dp(n);
	auto dfs = [&] (auto&& self, int u, int p) -> void {
		dp[u] = 0;
		vector<int> ch;
		for (int v : g[u]) if (v != p) {
			self(self, v, u);
			ch.push_back(dp[v]);
		}
		sort(ch.rbegin(), ch.rend());
		for (int i = 0; i < ch.size(); i++)
			dp[u] = max(dp[u], ch[i] + i + 1);
	};

	int ans = 1e18;
	auto reroot = [&] (auto&& self, int u, int par) -> void {
		vector<int> ch;
		for (int v : g[u]) ch.push_back(dp[v]);

		sort(ch.rbegin(), ch.rend());
		for (int i = 0; i < ch.size(); i++)
			dp[u] = max(dp[u], ch[i] + i + 1);
		ans = min(ans, dp[u]);

		vector<int> ord = g[u];
		int m = ord.size();
		sort(ord.begin(), ord.end(), [&] (int i, int j) {
			return dp[i] > dp[j];
		});
		
		vector<int> pref(m, 0), suff(m, 0);
		for (int i = 0; i < m; i++) {
			pref[i] = dp[ord[i]] + i + 1;
			if (i - 1 >= 0)
				pref[i] = max(pref[i], pref[i - 1]);
		}
		for (int i = m - 1; i >= 0; --i) {
			suff[i] = dp[ord[i]] + i;
			if (i + 1 < m)
				suff[i] = max(suff[i], suff[i + 1]);
		}

		for (int i = 0; i < m; i++) {
			int v = ord[i];
			if (v == par) continue;
			
			dp[u] = max((i ? pref[i - 1] : 0), (i + 1 < m ? suff[i + 1] : 0));
			// update dp[u]
			self(self, v, u);
			// rollback dp[u]
		}
	};
	
	dfs(dfs, 0, 0);
	reroot(reroot, 0, 0);

	//for (int i = 0; i < n; i++) {
	//	dfs(dfs, i, i);
	//	ans = min(ans, dp[i]);
	//}
	cout << ans << endl;

}
