#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

#define INF 1e18

int dp[201][201][61];
int dp2[201][61];

int32_t main() {
	fast_io;
	int n, m; cin >> n >> m;
	vector<int> a(n);
	for(auto& x : a) cin >> x;
	vector<int> pref(n+1);
	for(int i=1;i<=n;i++){
		pref[i] = pref[i-1] + a[i-1];
	}

	m++;

	const int BITS = 60;
	for(int i=n-1;i>=0;i--){
		// calcular dp[i][i+1][l]:
		for(int l=0;l<=BITS;l++){
			if(a[i] > 0) dp[i][i+1][l] = l*a[i];
		}
		for(int j=i+2;j<=n;j++){
			dp[i][j][0] = -INF;
			for(int l=1;l<=BITS;l++){
				dp[i][j][l] = -INF;
				for(int x=i+1;x<j;x++){
					dp[i][j][l] = max(dp[i][j][l], dp[i][x][l-1] + dp[x][j][l-1] + pref[j] - pref[x]);
				}
				//cout << i << " " << j << " " << l << " " << dp[i][j][l] << endl;
			}
		}
	}

	// Agora quero usar os digitos do m!
	// dp2[i][l] = melhor que da para fazer jogando todos a partir do i no sufixo do m
	
	// dp2[i][1]
	
	for(int i=0;i<n;i++) dp2[i][0] = -INF;

	//for(int i=0;i<n;i++) dp2[i][1] = -INF;
	//if((m) & 1){
	//	for(int i=0;i<n;i++) dp2[i][1] = a[i];
	//}
	//for(int i=0;i<=n;i++) cout << i << " " << 1 << "  " << dp2[i][1] << endl;

	for(int l=1;l<=BITS;l++){
		if(((m >> (l-1)) & 1) == 0){
			for(int i=0;i<=n;i++){
				dp2[i][l] = dp2[i][l-1];
				//cout << i << " " << l << " " << dp2[i][l] << endl;
			}
			continue;
		}
		for(int i=0;i<=n;i++){
			dp2[i][l] = -INF;
			for(int x = i;x<=n;x++){
				//cout << "para " << i << " " << l << " considerei x=" << x << " " << dp[i][x][l-1] << " + " << dp2[x][l-1] + pref[n] - pref[x] << endl;
				dp2[i][l] = max(dp2[i][l], dp[i][x][l-1] + dp2[x][l-1] + pref[n] - pref[x]);
			}
			//cout << i << " " << l << " " << dp2[i][l] << endl;
		}
	}
	cout << dp2[0][BITS] << endl;


		
		

	//cout << dp[0][n][2] << endl;
	//cout << dp[0][n][3] << endl;

}
