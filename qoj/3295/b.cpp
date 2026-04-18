#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;

const int maxn = 52;
int dp[maxn][maxn][maxn][2];
const int mod = 998244353;

int32_t main() {_
	int n; cin >> n;	
	string st; cin >> st;
	reverse(st.begin(), st.end());

	dp[0][0][0][0] = 1;

	for (int i = 0; i < 4*n; ++i){

		for (int a = 0; a <= n; ++a)
			for (int b = 0; b <= n; ++b)
				for (int c = 0; c <= n; ++c){
					if (st[i] == '?' or st[i] == 'u'){
						if (a) dp[a-1][b+1][c][1] = (dp[a-1][b+1][c][1] + dp[a][b][c][0]) % mod;
						else if (c) dp[a][b][c-1][1] = (dp[a][b][c-1][1] + dp[a][b][c][0]) % mod;
					}
					if (st[i] == '?' or st[i] == 'c'){
						if (b) dp[a][b-1][c+1][1] = (dp[a][b-1][c+1][1] + dp[a][b][c][0]) % mod;
					}
					if (st[i] == '?' or st[i] == 'p'){
						dp[a+1][b][c][1] = (dp[a+1][b][c][1] + dp[a][b][c][0]) % mod;
					}
				}

		for (int a = 0; a <= n; ++a)
			for (int b = 0; b <= n; ++b)
				for (int c = 0; c <= n; ++c){
					dp[a][b][c][0] = dp[a][b][c][1];
					dp[a][b][c][1] = 0;
				}
	}

	cout << dp[0][0][0][0] << endl;

}
