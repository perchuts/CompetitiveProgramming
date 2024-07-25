#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

void solve(){
	int n; cin >> n;
	vector<vector<int>> dp(n + 1, vector<int>(n + 1));
	string s; cin >> s;
	dp[1][1] = 1;
	for (int i = 2; i <= n; ++i) {
		for (int j = 1; j <= i; ++j) {
			if (s[i-2] == '<') dp[i][j] = dp[i-1][j-1];
			else dp[i][j] = (dp[i-1][i-1] - dp[i-1][j-1] + mod) % mod;
			dp[i][j] = (dp[i][j] + dp[i][j-1]) % mod;
		}
	}
	cout << dp[n][n] << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
