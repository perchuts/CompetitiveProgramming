#include <bits/stdc++.h>
#define int ll
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
using namespace std;

using ll = long long;

int32_t main() {_

	int n, m; cin >> n >> m;
	vector<string> grid(n);
	for(int i=0;i<n;i++) cin >> grid[i];

	int ans = 0;
	vector<int> antcima(n), antbaixo(n), antstreak(n); 
	for(int j=0;j<m;j++){


		vector<int> streak(n), cima(n), baixo(n), qtd(n);
		cima[0] = 0;
		for(int i=1;i<n;i++){
			if(grid[i][j] == grid[i-1][j]) cima[i] = cima[i-1], qtd[i] = qtd[i-1]+1;
			else cima[i] = i;
		}
		baixo[n-1] = n-1;
		for(int i=n-2;i>=0;i--){
			if(grid[i][j] == grid[i+1][j]) baixo[i] = baixo[i+1], qtd[i] = qtd[i+1];
			else baixo[i] = i;
		}

		for(int l=0, r=0;l<n;l=r){
			while(r < n && grid[r][j] == grid[l][j]) r++;
			if(l == 0 || r == n) continue;
			if(j > 0 && grid[l][j] == grid[l][j-1] && grid[l-1][j] == grid[l-1][j-1] && grid[r][j] == grid[r][j-1] && cima[l] == antcima[l] && baixo[l] == antbaixo[l] && qtd[l-1] >=qtd[l] && qtd[r] >= qtd[r-1]) streak[l] = antstreak[l] + 1;
			else if(qtd[l-1] >=qtd[l] && qtd[r] >= qtd[r-1]) streak[l] = 1;
			else streak[l] = 0;
			ans += streak[l];
		}
		swap(antcima, cima);
		swap(antbaixo, baixo);
		swap(streak, antstreak);
	}
	cout << ans << endl;
}
