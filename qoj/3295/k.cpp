#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back

using namespace std;

using ll = long long;

void prep(){
	int n; cin >> n;
	vector<vector<int>> g(n);
	for (int i = 0; i < n-1; ++i){
		int u, v; cin >> u >> v;
		u--; v--;
		g[u].pb(v);
		g[v].pb(u);
	}

	vector<int> par(n);
	vector<int> dep(n);
	function<void(int,int,int)> dfs = [&](int x, int p, int d){
		dep[x] = d;
		par[x] = p;
		for (auto y : g[x]) if (y != p){
			dfs(y,x,d+1);
		}
	};
	dfs(0,-1,1);

	vector<int> vec(n);
	iota(vec.begin(), vec.end(), 0);
	sort(vec.begin(), vec.end(), [&](int a, int b){
			if (dep[a] != dep[b]) return dep[a] > dep[b];
			return a < b;
		});

	vector<int> m(n,-1);
	for (auto v : vec){
		if (m[v] != -1) continue;
		if (par[v] == -1 or m[par[v]] != -1) continue;
		m[v] = par[v];
		m[par[v]] = v;
	}

	vector<int> vals(n);
	function<void(int,int,int)> build = [&](int x, int p, int v){
		vals[x] = v;
		for (auto y : g[x]) if (y != p){
			if (y == m[x]) build(y,x,!v);
			else build(y,x,v);
		}
	};
	build(0,-1,0);

	for (int i = 1; i < n; ++i) cout << vals[i];
	cout << endl;
}

void play(){
	int n; cin >> n;
	string st; cin >> st;
	vector<int> vals(n);
	for (int i = 1; i < n; ++i) vals[i] = (st[i-1] == '1');

	for (int i = 0; i < n-1; ++i){
		int u, v; cin >> u >> v;
		u--; v--;
		if (vals[u] == vals[v]) cout << "ignore" << endl;
		else cout << "take" << endl;
	}
}

int32_t main() {_
	string act; cin >> act;
	if (act == "prepare") prep();
	else play();
}
