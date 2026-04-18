#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;

void solve(){

	int n; cin >> n;

	vector<int> a(n), b(n), c(n);
	for(int i=0;i<n;i++){
		cin >> c[i];
		for(int j=0;j<c[i];j++){
			int x; cin >> x;
			a[i] += x*x;
			b[i] += x;
		}
	}
	int imin = 0, imax = 0;
	for(int i=1;i<n;i++){
		if(b[i] * c[imin] < b[imin] * c[i]) imin = i;
		else if(b[i] * c[imin] == b[imin] * c[i]){
			if(a[i] * c[imin] * c[imin] > a[imin] * c[i] * c[i]) imin = i;
		}
		if(b[i] * b[imax] > b[i] * 
	}

}

int32_t main() {_
	int t; cin >> t;
	while(t--) solve();

}
