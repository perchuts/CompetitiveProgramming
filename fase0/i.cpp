#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
 
using namespace std;
	
#define int long long
#define PI pair<int,int>
#define f first
#define s second
#define pb push_back
#define szo(x) ((int)x.size())

const int maxn = 5e3+10, maxt = 102;
int dp[maxt][maxn];
int mat[maxn][maxt];

int32_t main(){

	int n, t; cin >> n >> t;
	for (int i = 0; i < n; ++i)
		for (int j = 1; j <= t; ++j) cin >> mat[i][j];

	for (int i = 0; i< n; ++i)
		for (int j = 1; j <= t; ++j) mat[i][j] += mat[i][j-1];

	int l, u; cin >> l >> u;

	for (int i = 0; i < n; ++i)
		for (int j = 1; j <= t; ++j) dp[j][i] = -1e18;

	for (int i = 1; i <= t; ++i){
		for (int s = i-l; s >= max(i-u, 0ll); s--){
			for (int a = 0; a < n; ++a){
				if (dp[s][a] == -1e18) continue;
				int cur = mat[a][i] - mat[a][s] + dp[s][a];
				dp[i][a] = max(dp[i][a], cur);
			}
		}

		vector<PI> tds;
		tds.pb({-1e18, -1});
		
		for (int a = 0; a < n; ++a) tds.pb({dp[i][a], a});
		sort(tds.begin(), tds.end());

		if (i == t) ;
		else{
			for (int a = 0; a < n; ++a) dp[i][a] = (tds.back().s == a) ? tds[n-1].f : tds[n].f;
		}
	}

	int best = -1e18;
	for (int a = 0; a < n; ++a) best = max(best, dp[t][a]);

	if (best == -1e18){
		cout << -1 << '\n';
		return 0;
	}

	cout << best << '\n';


	return 0;
}
