#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;



void solve(){
	using pt = array<int,2>;
	vector<pt> tr(3);
	for(auto& [x, y] : tr) cin >> x >> y;
	int nx, dx, ny, dy;
	
	cin >> nx >> dx >> ny >> dy;

	auto d2 = [&] (pt a, pt b){
		int dx = a[0] - b[0];
		int dy = a[1] - b[1];
		return dx*dx + dy*dy;
	};

	int special = 0;
	for(int k=0;k<2;k++){
		int t = 0;
		for(int j=0;j<3;j++){
			t += d2(tr[(j+1)%3], tr[(j+2)%3]) * (2 * (j == k) - 1);
		}
		if(t == 0){
			special = 1;
			if(k == 1){
				swap(tr[0], tr[1]);
			}
			break;
		}
	}

	if(special){
		// triangulo eh retangulo no A.
		
	}



}

int32_t main() {_
	int t; cin >> t;
	while(t--) solve();
	
}
