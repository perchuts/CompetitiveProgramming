#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

#define INF 1e18

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int32_t main() {
	fast_io;
	int n, m, k; cin >> n >> m >> k;
	vector grid(n, vector<char>(m));
	vector dist(n, vector<int>(m, INF));
	for(auto& l : grid){
		for(auto& c : l) cin >> c;
	}
	queue<pair<int,int>> fila;
	fila.push({0, 0});
	dist[0][0] = 0;
	while(fila.size()){
		auto [i, j] = fila.front(); fila.pop();
		//cout << i << " " << j << endl;
		//cout.flush();
		for(int kk=0;kk<4;kk++){
			int ni = i + dx[kk];
			int nj = j + dy[kk];
			if(min(ni, nj) < 0 || ni >= n || nj >= m) continue;
			if(dist[ni][nj] < INF || grid[ni][nj] != '.') continue;
			dist[ni][nj] = dist[i][j] + 1;
			fila.push({ni, nj});
		}
	}
	int tot = dist[n-1][m-1];
	int ex = tot - n - m + 2;

	int mn = INF, qt = 0;
	for(int i=0;i<k;i++){
		int a, b; cin >> a >> b;
		int cs = a * (n+m - 2) + (a+b) * (ex/2);
		if(cs == mn) qt++;
		if(cs < mn){
			qt = 1;
			mn = cs;
		}
	}
	cout << mn << " " << qt << endl;

}
