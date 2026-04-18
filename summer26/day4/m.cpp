#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define endl '\n'
#define pb push_back

using namespace std;

using ll = long long;

vector<int> p;

void solve(){

	int n; cin >> n;
	vector<int> prim;

		for(auto i : p){
			while(n % i == 0){
				n /= i;
				prim.push_back(i);
			}
		}

	if(n > 1) cout << 0 << endl;
	else if(prim.size() == 1) cout << 1 << endl;
	else if(prim[0] * prim[1] >= 4000) cout << 1 << endl;
	else cout <<0 << endl;

}

int32_t main() {_
	int t; cin >> t;

	for(int i=2;i<4000;i++){
		int ok = 1;
		for(int j=2;j*j<=i;j++) if(i % j == 0) ok = 0;
		if(ok) p.push_back(i);
	}

	while(t--) solve();
}
