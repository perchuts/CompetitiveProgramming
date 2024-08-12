#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
using namespace std;

using ll = long long;

const int mod = 998244353;
const int inf = 2e9 + 100;


#define pii pair<int, int>

set<int> quem[110000];
vector<int> grafo[110000];
int deg[110000];
int morto[110000];
int existe[110000];

int32_t main() {_
	
	int n, k;
	cin >> n >> k;
	set<pii> arestas;
	for(int i=0;i<n;i++){
		int u, v; cin >> u >> v;
		u--; v--;
		if(arestas.find({u, v})!= arestas.end()) continue;
		existe[u] = 1;
		existe[v] = 1;

		quem[u].insert(i);
		quem[v].insert(i);

		if(u==v) continue;
		deg[u]++, deg[v]++;
		grafo[u].push_back(v);
		grafo[v].push_back(u);
		arestas.insert({u, v});
		arestas.insert({v, u});
	}

	for(int u=0;u<k;u++){
		if(grafo[u].size()==1){
			int v = grafo[u][0];
			if(grafo[v].size()==1) continue;
			int ok = 0;
			for(auto p : quem[u]){
				if(quem[v].find(p) == quem[v].end()){
					ok = 1;
					break;
				}
			}
			if(ok == 0){
				deg[v]--;
				morto[u] = 1;
			}
		}
	}

	for(int i=0; i<k;i++){
		if(deg[i] >= 3){
			cout << "impossible" << endl;
			return 0;
		}
	}


//	for(int i=0;i<k;i++){
//		if(morto[i]) continue;
//		cout << i+1 << ":" << endl;
//		for(auto v : grafo[i]){
//			cout << v+1 << " ";
//		}
//		cout << endl;
//	}
	
	vector<int> marc(k+2);
	int ciclos = 0;
	function<void(int)> dfs = [&] (int u){
		marc[u] = 1;
		for(auto v : grafo[u]) if(!marc[v] && !morto[v]){
			dfs(v);
		}
	};
	int caminhos =  0;
	for(int i=0;i<k;i++){
		if(!existe[i] || morto[i] || marc[i]) continue;
		if(deg[i] == 2) continue;
		caminhos++;
		dfs(i);
	}
	for(int i=0;i<k;i++){
		if(morto[i] || marc[i]) continue;
		if(deg[i]==0) continue;
		ciclos++;
		dfs(i);
	}
//	cout << ciclos << " " << caminhos << "\n";

	if(ciclos == 0 || (ciclos == 1 && caminhos == 0)){
		cout << "possible" << endl;
	}
	else
		cout << "impossible" << endl;



	


}
