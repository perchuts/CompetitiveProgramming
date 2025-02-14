#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;
	map<int,set<pair<int,int>>> linhas, colunas;
	int n; cin >> n;
	vector<pair<int,int>> pts(n);
	vector<int> marc(n, -1);
	for(int i=0;i<n;i++){
		int x, y; cin >> x >> y;
		pts[i] = {x, y};
		linhas[x].insert({y, i});
		colunas[y].insert({x, i});
	}

	int ini, W;
	auto dfs = [&] (auto&& self, int i, int x, int y, int qual, int cor) -> void{
		marc[i] = cor;
		if(qual == 0){
			// quero andar na mesma linha
			if(linhas[x].size() == 0 ||( i == ini && linhas[x].size() == 1) ) return; // morreu, mas tudo bem
			for(auto [z, j] : linhas[x]){
				if(j == ini) continue;
				//cout << "achei o " << j << endl;

				linhas[x].erase({z, j});
				colunas[z].erase({x, j});
				if(j == ini){
					// fez o W! (fechou o ciclo)
					W = 1;
					return;
				}
				self(self, j, x, z, qual^1, cor^1);
				return;
			}
		}
		else{
			if(colunas[y].empty() ||( i == ini && colunas[y].size() == 1)) return;
			for(auto [z, j] : colunas[y]){
				if(j == ini) continue;

				//cout << "achei o " << j << endl;
				linhas[z].erase({y, j});
				colunas[y].erase({z, j});
				if(j == ini){
					// fez o W! (fechou o ciclo)
					W = 1;
					return;
				}
				self(self, j, z, y, qual^1, cor^1);
				return;
			}
		}
	};
	for(int i=0;i<n;i++){
		if(marc[i] == -1){
			// ainda nao assinalei esse bicho.
			auto [x, y] = pts[i];
			ini = i, W = 0;
			//cout << "entrei pelo " << i << endl;
			dfs(dfs, i, x, y, 0, 0);
			if(W) continue;
			//cout << "entrei pelo " << i << endl;
			dfs(dfs, i, x, y, 1, 0);
			if(W) continue;
			linhas[x].erase({y, i});
			colunas[y].erase({x, i});

		}
	}

	for(int i=0;i<n;i++){
		if(marc[i]==1) cout << 'L';
		else cout << 'F';
	}
	cout << endl;
			



}
