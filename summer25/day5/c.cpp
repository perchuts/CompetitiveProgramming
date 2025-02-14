#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

#define INF 1e18

int32_t main() {
	fast_io;
	int n, W; cin >> n >> W;
	vector<int> d(n+1), w(n+1), val(n+1);
	vector<vector<int>> g(n+1);
	for(int i=1;i<=n;i++){
		cin >> d[i];
		g[d[i]].push_back(i);
	}

	for(int i=1;i<=n;i++){
		cin >> w[i];
	}

	for(int i=1;i<=n;i++){
		cin >> val[i];
	}

	vector dpcom(n+1, vector<int>(W+1));
	vector dpsem(n+1, vector<int>(W+1));

	auto dfs = [&] (auto&& self, int u) -> void {

		for(auto v : g[u]){
			
			for(int i=0;i<=W;i++){
				if(i >= w[v]) dpcom[v][i] = dpcom[u][i-w[v]] + val[v];
				else dpcom[v][i] = -INF;
			}
			for(int i=0;i<=W;i++){
				dpsem[v][i] = max(dpcom[u][i], dpsem[u][i]);
			}

			self(self, v);

			for(int i=0;i<=W;i++){
				dpcom[u][i] = max(dpcom[u][i], dpcom[v][i]);
			}
		}
	};

	dfs(dfs, 0);
	cout << dpcom[0][W] << endl;
	
}
