#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

struct Dsu{

	vector<int> pai, sz, mn;
	Dsu(int n) : pai(n), sz(n, 1), mn(n) {
		for(int i=0;i<n;i++) pai[i] = i, mn[i] = i;
	}

	int find(int i){
		if(i == pai[i]) return i;
		return pai[i] = find(pai[i]);
	}

	void une(int i, int j){
		i = find(i);
		j = find(j);
		if(i == j) return;
		if(sz[i] < sz[j]) swap(i, j);
		pai[j] = i;
		sz[i] += sz[j];
		mn[i] = min(mn[i], mn[j]);
	}

};

void solve(){

	int n; cin >> n;
	vector<int> p(n);
	for(auto& x : p) cin >> x, x--;
	vector<int> rev(n); for(int i=0;i<n;i++) rev[p[i]] = i;
	vector<vector<int>> g(n);
	for(int i=0;i<n-1;i++){
		int u, v; cin >> u >> v;
		u--, v--;
		g[v].push_back(u);
		g[u].push_back(v);
	}
	Dsu dsu(n);
	vector<int> pai(n, -1);
	for(int i=n-1;i>=0;i--){
		for(auto j : g[p[i]]) if(rev[j] > i) {
			pai[p[dsu.mn[dsu.find(rev[j])]]] = p[i];
		}
		for(auto j : g[p[i]])if(rev[j] > i) {
			dsu.une(i, rev[j]);
		}
	}
	for(auto x : pai) cout << x+1 << " ";
	cout << endl;
}

int32_t main() {
	fast_io;
	int t; cin >> t;
	while(t--) solve();
}
