#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back
using namespace std;

using ll = long long;

int32_t main() {_

	string s; cin >> s;
	int t; cin >> t;
	if(s[0] == 'e'){
		while(t--){
			int n, r, c;
			cin >> n >> r >> c; r--, c--;
			vector<int> grid(n*n);
			vector<int> ngrid(n*n);
			for(auto& l : grid) cin >> l;
			if(r == n-1 && c == n-1){
				if(n&1){
					for(int i=0;i<n*n-1;i++) ngrid[i] = grid[(i+1)%(n*n-1)];
				}
				else{
					for(int i=0;i<n*n-3;i++) ngrid[i] = grid[(i+1)%(n*n-3)];
					ngrid[n*n-3] = grid[n*n-2];
					ngrid[n*n-2] = grid[n*n-3];
				}
			}
			else{
				if(((r+c+n)&1) == 0){
					int p = n*r+c;
					for(int i=0;i<n*n;i++){
						if(i == p) ngrid[i] = grid[n*n-1];
						else if(i == n*n-1) ngrid[i] = grid[(p+1)%(n*n-1)];
						else ngrid[i] = grid[(i+1)%(n*n-1)];
					}
				}
				else{
					int p = n*r+c;
					auto ruim = [&](int i){
						return (i == p) | (i == (n*n-1));
					};
					for(int i=0;i<n*n;i++){
						if(ruim(i)) continue;
						int j = (i + 1) % (n*n);
						while(ruim(j)) j = (j + 1) % (n*n);
						ngrid[i] = grid[j];
					}
					ngrid[p] = grid[n*n-1];
					ngrid[n*n-1] = grid[p];
				}
			}
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++) cout << ngrid[i*n+j] << " ";
				cout << endl;
			}
		}
	}
	else{
		while(t--){
			int n; cin >> n;
			vector<int> grid(n*n);
			vector<int> ngrid(n*n);
			for(auto& l : grid) cin >> l;
			int r, c;
			for(int i=0;i<n;i++) for(int j=0;j<n;j++) if(grid[n*i+j] == 0) r=i,c=j;
			if(r == n-1 && c == n-1){
				if(n&1){
					for(int i=0;i<n*n-1;i++) ngrid[i] = grid[(i+n*n-1-1)%(n*n-1)];
				}
				else{
					for(int i=0;i<n*n-3;i++) ngrid[i] = grid[(i+n*n-3-1)%(n*n-3)];
					ngrid[n*n-3] = grid[n*n-2];
					ngrid[n*n-2] = grid[n*n-3];

				}
			}
			else{

				if(((r+c+n)&1) == 0){
					int p = n*r+c;
					for(int i=0;i<n*n;i++){
						if(i == (p+1)%(n*n-1)) ngrid[i] = grid[n*n-1];
						else if(i == n*n-1) ngrid[i] = grid[p];
						else ngrid[i] = grid[(i+n*n-1-1)%(n*n-1)];
					}
				}
				else{
					int p = n*r+c;
					auto ruim = [&](int i){
						return (i == p )|( i == (n*n-1));
					};
					for(int i=0;i<n*n;i++){
						if(ruim(i)) continue;
						int j = (n*n + i - 1) % (n*n);
						while(ruim(j)) j = (n*n + j - 1) % (n*n);
						ngrid[i] = grid[j];
					}
					ngrid[p] = grid[n*n-1];
					ngrid[n*n-1] = grid[p];
				}

			}
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++) cout << ngrid[i*n+j] << " ";
				cout << endl;
			}
		}
	}
}
