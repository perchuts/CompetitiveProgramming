#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

const int INF = 1e9;

int32_t main() {
	fast_io;
	int n; cin >> n;
	vector<vector<int>> g(n);

	int lixo; cin >> lixo; // 0
	for(int i=1;i<n;i++){
		int x; cin >> x; x--;
		g[x].push_back(i);
	}
	vector<int> sp(n);
	for(auto& x : sp) cin >> x;


	vector<int> l(n), r(n), c(n, -1);
	
	int L = 0;
	auto dfs1 = [&] (auto&& self, int u) -> void {
		
		for(auto v : g[u]) {
			self(self, v);
		}
		if(sp[u] == -1){
			// posso ser bastante coisa!
			// (intersecao dos intervalos dos filhos)
			vector<int> blk(2);
			l[u] = 0, r[u]= INF;
			for(auto v : g[u]){
				l[u] = max(l[u], max(0LL, l[v] - 1));
				r[u] = min(r[u], r[v] + 1);
				if(c[v] >= 0) blk[c[v]] = 1;
			}

			if(!blk[0] && !blk[1]) c[u] = -1;
			else if(!blk[0]) c[u] = 0;
			else if(!blk[1]) c[u] = 1;
			else L = 1;

			if(c[u] >= 0 && ((l[u]+c[u])&1)) l[u]++;
			if(c[u] >= 0 && ((r[u]+c[u])&1)) r[u]--;
			if(l[u] > r[u]) L = 1;
			//cout << "L: " << L << endl;
			//cout << u << " c: " << c[u] << " l: " << l[u] << " r: " << r[u] << endl;
		}
		else{
			int s = sp[u];
			l[u] = s;
			r[u] = s;
			c[u] = s&1;
			for(auto v : g[u]){
				
				if(c[v] == c[u]) L = 1;
				if(l[v]-1 > s) L = 1;
				if(r[v]+1 < s) L = 1;
			}
			//cout << "L: " << L << endl;
			//cout << u << " l: " << l[u] << " r: " << r[u] << endl;
		}
	};

	dfs1(dfs1, 0);
	if(L){
		cout << "NEM" << endl;
		return 0;
	}

	cout << "IGEN" << endl;

	// reconstruir de cima para baixo
	auto dfs2 = [&] (auto&& self, int u, int npai) -> void {
		
		if(u == 0) sp[u] = l[u];
		else if(npai-1 >= l[u] && npai-1 <= r[u]) sp[u] = npai-1;
		else if(npai+1 >= l[u] && npai+1 <= r[u]) sp[u] = npai+1;
		else assert(0);

		for(auto v : g[u]){
			self(self, v, sp[u]);
		}
	};
	
	dfs2(dfs2, 0, -1);
	for(auto x : sp) cout << x << " ";
	cout << endl;
}
