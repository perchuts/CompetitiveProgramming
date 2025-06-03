#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
//#define endl '\n'
#define int long long
const int INF = 1e18;

int32_t main(){

	
	int n, m; cin >> n >> m;
	int dn = (1<<n);

	vector<array<int,3>> v;
	for(int i=0;i<m;i++){
		int t; cin >> t;
		if(t == 1){
			int x, y; cin >> x >> y;
			v.push_back({-1, x, y});
		}
		else{
			int x, y, z; cin >> x >> y >> z;
			v.push_back({x, y, z});
		}
	}
	vector<vector<int>> ans(dn, vector<int>(dn));
	for(int i=0;i<dn;i++){ // iesima coluna
		// simular a mascara de i no circuito
		int a = i;
		for(int j=m-1;j>=0;j--){
			int na = a;
			if(v[j][0] == -1){
				auto [__, y, z]=  v[j];
				// cnot
				if((a>>(y))&1) na ^= (1<<(z));
			}
			else{
				// ccnot
				auto [x, y, z] = v[j];
				if((a>>(x))&1){
					if((a>>(y))&1) na ^= (1<<(z));
				}
			}
			a = na;
		}

		ans[a][i] = 1;
	}
	for(auto l : ans){
		for(auto c : l) cout << c;
		cout << endl;
	}

}
