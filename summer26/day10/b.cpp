#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define endl '\n'
#define pb push_back
using namespace std;

using ll = long long;

const int maxn = 25;
const int maxm = 4000;

int g[maxn][maxm];

void solve(){
	int r, c, n;
	cin >> r >> c >> n;
	int nim =0 ;
	for(int i=0;i<n;i++){
		int x, y; cin >> x >> y;
		x--, y--;

		if(y < maxm) nim ^= g[x][y];
		else{
			int ny = 768 * 4 + y % 768;
			nim ^= (g[x][ny] + (y - ny));
		}
	}
	if(nim){
		cout << "YES" << endl;
	}
	else{
		cout << "NO" << endl;
	}

}

int32_t main() {
	for (int i = 0; i < maxn; ++i){
		for (int j = 0; j < maxm; ++j){
			vector<bool> v(2*i+j+10);

			for (int k = 1; i-k >= 0; ++k) v[g[i-k][j]] = true;
			for (int k = 1; j-k >= 0; ++k) v[g[i][j-k]] = true;
			for (int k = 1; j-k >= 0 and i-k >= 0; ++k) v[g[i-k][j-k]] = true;

			int mex = 0;
			while (v[mex]) mex++;
			g[i][j] = mex;
		}
	}

	int t; cin >> t;
	while(t--) solve();

}
