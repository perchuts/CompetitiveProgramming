#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

const int LINF = 1e18;

int32_t main() {
	fast_io;
	int n, k; cin >> n >> k;
	vector<int> a(n);
	for(auto& x : a) cin >> x;
	vector<pair<int,int>> coisos(n);
	for(int i=0;i<n;i++) coisos[i] = {a[i], i};
	sort(a.rbegin(), a.rend());
	sort(coisos.rbegin(), coisos.rend());

	vector dp(n, vector<int>(k+1, LINF));
	vector agmin(n, vector<int>(k+1, LINF));

	for(int l=1;l<=k;l++) dp[0][l] = 0;


	for(int i=1;i<n;i++){
		for(int j=0;j<=i;j++){
			
			for(int l=0;l<=k;l++){
				if(l<k){
					if(dp[j][l] < dp[i][l+1]){
						agmin[i][l+1] = j;
						dp[i][l+1] = dp[j][l];
					}
				}
				dp[j][l] += (a[j]-a[i])*(a[j]-a[i]);
			}
		}
	}

	//for(int i=0;i<n;i++){
	//	for(int l=0;l<=k;l++){
	//		if(dp[i][l] > LINF/2) cout << "    * ";
	//		else cout << setw(5) << dp[i][l] << " ";
	//	}
	//	cout << endl;
	//}
	//for(int i=0;i<n;i++){
	//	for(int l=0;l<=k;l++){
	//		if(agmin[i][l] > LINF/2) cout << "    * ";
	//		else cout << setw(5) << agmin[i][l] << " ";
	//	}
	//	cout << endl;
	//}

	int ans = LINF, ians = -1;
	for(int i=0;i<n;i++){
		if(dp[i][k] < ans){
			ans = dp[i][k];
			ians = i;
		}
	}

	//cout << ans << endl;
	vector<int> recup(n);
	for(int j=n-1;j>=ians;j--) recup[j] = ians;
	int c = ians;
	//cout << c << " ";
	for(int l=k;l>1;l--){
		int nc = agmin[c][l];
		
		if(nc == LINF) nc = 0;
		//cout << nc << " ";
		for(int j=c-1;j>=nc;j--){
			recup[j] = nc;
		}
		c = nc;
	}
	//cout << endl;
	vector<int> resp(n);
	for(int i=0;i<n;i++){
		auto [x, y] = coisos[i];
		resp[y] = a[recup[i]];
	}

	for(auto x : resp) cout << x << " ";
	cout << endl;
}
