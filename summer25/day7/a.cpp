#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

void solve(){

	int n, m; cin >> n >> m;
	vector<int>  pai(m+1), qt(m+1), edg(n, -1);
	vector<vector<int>> arv(m+1), g(n);
	vector<vector<pair<int,int>>> vbons(m+1);
	vector<int> soz(m+1);
	for(int i=0;i<m;i++){
		int u, v; cin >> u >> v;
		edg[u] = v;
		edg[v] = u;
	}

	//for(int i=0;i<n;i++){
	//	int j = (i+1) % n;
	//	g[i].push_back(j);
	//	g[j].push_back(i);
	//}

	soz[0] = n-1; // aresta n-1 <-> 0
	vector<pair<int,int>> st;
	st.push_back({n-1, 0});
	int idc = 1;
	for(int i=0;i<n;i++){
		auto[x, y] = st.back();
		// To no vtc y da arvore (cuja subarvore acaba quando eu chegar no x)
		qt[y]++;
		if(x == i){
			if(y>0) qt[pai[y]]++;
			st.pop_back();
			continue;
		}
		if(edg[i] == -1){
			continue;
		}

		int u = edg[i];
		// vtc novo na arvore
		arv[y].push_back(idc);
		vbons[y].push_back({i, u});

		arv[idc].push_back(y);
		vbons[idc].push_back({i, u});

		pai[idc] = y;
		soz[idc] = i; // aresta i <-> i+1
		qt[idc]++;
		st.push_back({u, idc++});
	}


	//for(int i=0;i<=m;i++){
	//	cout << "filhos do " << i << " (qt = " << qt[i] << ")" << endl;
	//	for(auto j : arv[i]) cout << j << " ";
	//	cout << endl;
	//}
	
	vector<int> vis(m+1), dp0(m+1), dp1(m+1), agm(m+1, -1);
	// dp0 nao me pega, dp1 fodase
	auto dfs = [&] (auto&& self, int u, int p) -> void{
		vis[u] = 1;
		for(auto v : arv[u]) if((qt[v]&1) && v != p){
			self(self, v, u);
		}
		for(auto v : arv[u]) if((qt[v]&1) && v != p){
			dp0[u] += dp1[v];
		}
		dp1[u] = dp0[u];
		for(auto v : arv[u]) if((qt[v]&1) && v != p){
			if(ckmax(dp1[u], 1 + dp0[u] - (dp1[v] - dp0[v]))) agm[u] = v;
		}
	};

	vector<int> recup(n), uso(m+1);
	auto dfs2 = [&] (auto&& self, int ocup, int u, int p) -> void{
		for(int i=0;i<arv[u].size();i++){
			auto [a, b] = vbons[u][i];
			int v = arv[u][i];
			if(!(qt[v] & 1)) continue;
			if(v == p) continue;
			if(agm[u] == v){
				// uso a aresta u-v:
				recup[a] = 1;
				recup[b] = 1;
				uso[u] = 1;
				uso[v] = 1;
				self(self, 1, v, u);
				continue;
			}
			self(self, 0, v, u);
		}
	};



	int ruins = 0;
	for(auto x : qt) ruins += (x&1);
	int bons = 0;
	for(int i=0;i<=m;i++){
		if((qt[i] & 1) && !vis[i]) dfs(dfs, i, -1), bons += dp1[i], dfs2(dfs2, 0, i, -1);

	}
		
	cout << ruins - bons << endl;



	vector<int> cons(n);
	for(int i=0;i<=m;i++){
		if((qt[i]&1) && !uso[i]) cons[soz[i]] = -1;
	}

	for(int i=0;i<n;i++){
		int j = (i+1) % n;
		if(cons[i] != -1) g[i].push_back(j), g[j].push_back(i);
	}
	for(int i=0;i<n;i++){
		if(edg[i] != -1 && !recup[i]) g[i].push_back(edg[i]);
	}

	vector<int> cor(n), marc2(n);
	auto dfs3 = [&] (auto&& self, int u) -> void{
		marc2[u] = 1;
		for(auto v : g[u]) if(!marc2[v]){
			cor[v] = cor[u] ^ 1;
			self(self, v);
		}
	};

	//for(int i=0;i<n;i++){
	//	cout << "viz do " << i << endl;
	//	for(auto j : g[i]) cout << j << " ";
	//	cout << endl;
	//}

	dfs3(dfs3, 0);
	for(int i=0;i<n;i++) cout << cor[i] << " ";
	cout << endl;
		






}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
