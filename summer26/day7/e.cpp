#include <bits/stdc++.h>
#define int ll
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
using namespace std;

using ll = long long;

int32_t main() {_

	int n; cin >> n;
	vector<int> v(n);
	for(auto& x : v) cin >> x;
	if(n == 1){
		cout << v[0] << endl;
		return 0;
	}

	vector<int> w(n-2);
	vector<int> ans(n);

	for(int i=0;i<n-2;i++){
		w[i] = min(v[i+1], max(v[i], v[i+2]));
	}


	int mx = 0;
	for(auto x : v) mx = max(mx, x);
	ans[n-1] = ans[n-2] = mx;

	if(n == 2){

		cout << ans[0] << " " << ans[1] << endl;
		return 0;
	}
	for(int i=0;i<n-2;i++){
		if((i+n) % 2 == 0){
			if(n&1) ans[i] = v[n/2];
			int j = i/2+1;
			ans[i] = max({ans[i], v[n/2-j], v[(n-1)/2+j]});
			if(i>=2) ans[i] = max(ans[i], ans[i-2]);
		}
		else{
			int j = (i+1)/2;
			ans[i] = max(w[n/2-1-j], w[(n-1)/2-1+j]);
			if(i>=2) ans[i] = max(ans[i], ans[i-2]);
		}
		cout << ans[i] << " ";
	}
	cout << ans[n-2] << " " << ans[n-1] << endl;
}
