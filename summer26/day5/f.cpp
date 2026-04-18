#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back
using namespace std;

using ll = long long;

void solve(){
	int k, p, n;
	cin >> k >> p >> n;
	int cnt = 0;
	for(int x = max(1LL,n/k-p);k*x<=n;x++){
		if(k*x + (x%k)*(x%p) == n) cnt++;
	}
	cout << cnt << endl;
}

int32_t main() {_
	int t; cin >> t;
	while(t--) solve();
}
