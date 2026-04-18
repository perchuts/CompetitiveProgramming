#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define endl '\n'
#define pb push_back
#define PI pair<int,int>
#define f first
#define s second
using namespace std;

using ll = long long;

string solve(){
	int n; cin >> n;
	vector<vector<PI>> g(n);

	for (int i = 0; i < n-1; ++i){
		int u, v, w; cin >> u >> v >> w;
		g[u].pb({v,w});
		g[v].pb({u,w});
	}

	function<int(int,int)> dfs = [&](int x, int p){
		int nim = 0;
		for (auto e : g[x]) if (e.f != p){
			int y = e.f, w = e.s;
			int val = dfs(y,x);
			if (w == 1) val = val+1;
			else if ((w&1) == 0) val = val;
			else val = val^1;
			nim ^= val;
		}
		return nim;
	};

	int val = dfs(0,-1);
	if (val) return "Emily";
	return "Jolly";
}

int32_t main() {_
	int t; cin >> t;
	for (int i = 1; i <= t; ++i){
		cout << "Case " << i << ": " << solve() << endl;
	}

}
