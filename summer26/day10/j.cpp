#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define endl '\n'
#define pb push_back
using namespace std;

using ll = long long;

int dx[] = {1, 1, 0, 0, -1, -1};
int dy[] = {-1, 0, 1, -1, 1, 0};

void solve(int r, int c, vector<vector<char>> grid){
	vector<array<int,2>> act;
	vector<vector<char>> ans(r, vector<char>(c, '.'));
	for(int i=0;i<r;i++) for(int j=0;j<c;j++){
		if(grid[i][j] != '.') ans[i][j] = 'F';
		if(grid[i][j] == 'I') act.push_back({i, j}), ans[i][j] = '(';
	}

	
	int l = 0;
	auto dfs = [&] (auto&& self, int x, int y) -> void {
		
		for(int k=0;k<6;k++){
			int nx = x + dx[k];
			int ny = y + dy[k];
			if(min(nx, ny) < 0 || nx >= r || ny >= c) continue;
			if(ans[nx][ny] == 'F'){
				if(ans[x][y] == ')') ans[nx][ny] = '(';
				else if(ans[x][y] == '(') ans[nx][ny] = ')';
				else{
					assert(0);
				}
				self(self, nx, ny);
			}
			if(ans[nx][ny] == ')' && ans[x][y] == ')') l = 1;
			if(ans[nx][ny] == '(' && ans[x][y] == '(') l = 1;
		}
	};


	auto dfsl = [&] (auto&& self, int x, int y) -> void {
		
		for(int k=0;k<6;k++){
			int nx = x + dx[k];
			int ny = y + dy[k];
			if(min(nx, ny) < 0 || nx >= r || ny >= c) continue;
			if(ans[nx][ny] == ')' || ans[nx][ny] == '(' || ans[nx][ny] == 'F'){
				ans[nx][ny] = 'B';
				self(self, nx, ny);
			}
		}
	};

	for(auto p : act){
		int i = p[0], j = p[1];
		if(ans[i][j] == 'B') continue;
		l = 0;
		dfs(dfs, i, j);
		if(l){
			ans[i][j] = 'B';
			dfsl(dfsl, i, j);
		}
	}

	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++) cout << ans[i][j];
		cout << endl;
	}
	cout << endl;



}

int32_t main() {_


	while(1){
		int r, c; cin >> r >> c;
		//r = rand() % 100 + 1, c = rand() % 100 + 1;
		if(r + c == 0) break;
		vector<vector<char>> grid(r, vector<char>(c));
		for(int i=0;i<r;i++) for(int j=0;j<c;j++){
			cin >> grid[i][j];
			//int x = rand() % 3;
			//if(x == 1) grid[i][j] = '.';
			//if(x == 0) grid[i][j] = 'I';
			//if(x == 2) grid[i][j] = '*';
		}
		solve(r, c, grid);
	}
}
