#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
//#define endl '\n'
#define pb push_back

using namespace std;
using ll = long long;
const int INF = 1e18;

const int M = 10;
int32_t main() {_

	int n; cin >> n;
	vector<int> a(n), b(n);
	for(auto& x : a) cin >> x;
	for(auto& x : b) cin >> x;

	int cn = 0;
	for(auto x : b) cn += x;
	vector<int> d;

	int ul = 0;
	for(int i=0;i<n;i++){
		if(b[i]){
			d.push_back(i - ul);
			ul = i;
		}
	}



	vector<int> dp(2*M);
	for(int k=0;k<d.size();k++){
		vector<int> ndp(2*M);
		for(int l = 0; l < 2*M; l++){

			if(l>0){
				ndp[l] = ndp[l-1];
			}
			if(l+2*k-M+2>=d[k] && l+2*k-M >= 0 && l+2*k - M < n){
				ndp[l] = max(ndp[l], a[l+2*k-M] + dp[l+2*k-M+2 - d[k]]);
			}
		}
		swap(ndp, dp);
	}


	for(int i=0;i<2*M;i++) cout << dp[i] << endl;
}


