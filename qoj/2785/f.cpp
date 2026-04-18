#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back

using namespace std;

using ll = long long;

void solve(){
	
	int n; cin >> n;
	int q = 0;
	for(int i=0;i<n;i++){
		int x; cin >> x; q += x == 1;
	}
	q += (q == n);
	if(q&1) cout << "Bob" << endl;
	else cout << "Alice" << endl;

}

int32_t main() {_

	int t; cin >> t;
	while(t--) solve();
}
