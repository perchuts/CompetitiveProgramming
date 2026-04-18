#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;

void solve(){

	int n; cin >> n;
	vector<vector<int>> g(n);
	for(int i=0;i<n-1;i++) {
		int u, v; cin >> u >> v;
		u--, v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	vector<tuple<int, int, int>> ans;
	auto dfs = [&] (auto&& self, int u, int p, int h=0) -> int {
		vector<int> bichos;
		for (auto v : g[u]) {
			if (v == p) continue;
			int k = self(self, v, u, h+1);
			if (k != -1) bichos.pb(k);
		}
		for (int i = 1; i < bichos.size(); i += 2) {
			ans.push_back({h, bichos[i]+1, bichos[i-1]+1});
		}
		if (bichos.size() & 1) return bichos.back();
		if (bichos.empty()) return u;
		return -1;
	};
	int k = dfs(dfs, 0, 0);
	if (k != -1) ans.pb({0, 1, k+1});
	sort(begin(ans), end(ans));
	cout << ans.size() << endl;
	for (auto [h, u, v] : ans) cout << u << " " << v << endl;
}

int32_t main() {_
	
	int t; cin >> t;
	while(t--) solve();

}
