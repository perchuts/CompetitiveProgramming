#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

int32_t main() {
	fast_io;
	int n; cin >> n;
	vector<int> w(n);
	for(int i=1;i<n;i++) cin >> w[i];

	vector<vector<int>> g(n);
	for(int i=0;i<n-1;i++){
		int u, v; cin >> u >> v;
		u--, v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	array<int,2> ans = {0, 0};
	vector<map<int,int>> dp(n);
	vector<int> mx(n), d(n);
	auto dfs = [&] (auto&& self, int u, int pai) -> void {
		for(auto v : g[u]) if(v != pai) {
			d[v] = d[u] + 1;
			self(self, v, u);
		}

		if(u == 0) return;
		for(auto v : g[u]) if(v != pai){
			//cout << "faz" << v << endl;
			
			if(dp[u].size() < dp[v].size()){
				swap(dp[u], dp[v]);
			}

			for(auto [pr, qt] : dp[v]) {
				dp[u][pr] += qt;
				//cout << "dist " << pr-d[u] << " " << qt << " virou " << dp[u][pr] << endl;
				qt = dp[u][pr];
				if(ans[0] < qt){
					//cout << "vira " << qt << endl;
					//cout << "dist " << pr-d[u] << " " << qt << endl;
					ans = {qt, pr-d[u]+1};
				}
				else if(ans[0] == qt){
					//cout << "subst " << qt << endl;
					if(pr-d[u]+1 < ans[1]) ans[1] =  pr - d[u]+1;
				}
			}
		}
		dp[u][d[u]] += w[u];
		//cout << "dist do " <<  u << " " << d[u] << endl;
		//cout << "no " << d[u] << " pus " << w[u] << endl;
		if(ans[0] <= w[u]){
			//cout << "base " << w[u] << endl;
			ans = {w[u], 1};
		}
	};
	dfs(dfs, 0, -1);
	cout << ans[0] << " "<< ans[1] << endl;
}
