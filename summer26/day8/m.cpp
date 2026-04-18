#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll

using namespace std;

using ll = long long;

const int MAX = 2e5+10;
vector<int> g[MAX];
int vis[MAX], comp[MAX];
int id[MAX];

int dfs(int i, int &t){
	int lo = id[i] = t++;
	s.push(i);
	vis[i] = 2;

	for (int j : g[i]){
		if (!vis[j]) lo = min(lo, dfs(j,t));
		else if (vis[j] == 2) lo = min(lo, id[j]);
	}

	if (lo == id[i]) while (1){
		int u = s.top(); s.pop();
		vis[u] = 1, comp[u] = i;
		if (u == i) break;
	}
	
	return lo;
}


void tarjan(int n){
	int t = 0;
	for (int i = 0; i < n; ++i) vis[i] = 0;
	for (int i = 0; i < n; ++i) if (!vis[i]) dfs(i,t);
}

int32_t main() {_
	int n, m; cin >> n >> m;
	vector<pair<int,int>> edges;
	for (int i = 0; i < m; ++i){
		int a, b; cin >> a >> b;
		a--; b--;
		edges.pb({a,b});
		g[a].pb(b);
	}
	tarjan(n);

	set<int> cs;
	for (int i = 0; i < n; ++i) cs.insert(comp[i]);

	if (cs.size() == 1){
		cout << 0 << endl;
		return 0;
	}

	int sz = cs.size();
	vector<int> indeg(sz), outdeg(sz);

	vector<pair<int,int>> adj(n);
	for (auto [a,b] : edges){
		a = comp[a], b = comp[b];
		if (a == b) continue;
		adj[a].pb(b);
	}

}
