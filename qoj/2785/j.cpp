#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back

using namespace std;

using ll = long long;
using ld = long double;



int32_t main() {_
	int n, k; cin >> n >> k;
	vector<ld> p(n);
	for(auto& x : p) cin >> x, x /= 100;
	vector dp(n, vector(k+1, vector<ld>(k+1)));
	for(int i=0;i<n;i++){
		dp[i][0][0] = 1;
		for(int l=0;l<k;l++){
			for(int j=0;j<k;j++){
				dp[i][l+1][j] += dp[i][l][j] * p[i];
				dp[i][l][j+1] += dp[i][l][j] * (1 - p[i]);
			}
		}
	}

	// nunca sei o i, so sei o l,j
	
	vector suc(k+1, vector<ld>(k+1));
	for(int l=0;l<=k;l++){
		for(int j=0;j<=k;j++){
			if(l+j >= k) continue;
			ld bom = 0, tot = 0;
			for(int i=0;i<n;i++){
				bom += dp[i][l][j] * p[i];
				tot += dp[i][l][j];
			}
			suc[l][j] = bom/tot;
		}
	}

	vector ans(k+1, vector<ld>(k+1));
	for(int l=k;l>=0;l--){
		for(int j=k;j>=0;j--){
			if(l+j > k) continue;
			if(l+j == k) {
				ans[l][j] = 1;
				continue;
			}
			ld sucesso = suc[l][j];
			ld tudo = 2*sucesso*ans[l+1][j];
			ld nada = sucesso*ans[l+1][j] + (1-sucesso)*ans[l][j+1];
			ans[l][j] = max(tudo, nada);
		}
	}

	cout << fixed << setprecision(20);
	cout << ans[0][0] * 1000 - 1000 << endl;
	
}
