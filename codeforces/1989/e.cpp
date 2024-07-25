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
const int mod = 998244353;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

void solve(){
	int n, k; cin >> n >> k;
	vector<int> f(n + 1);
	f[0] = 1;
	int s = 1, tot = n-1;
	for (int i = 1; i <= n-2; ++i) {
		f[i] = s;
		if (i >= 2) f[i] = (f[i] - f[i-2] + mod) % mod;
		s = (s + f[i]) % mod;
		tot = (tot + f[i] * (n-1-i)) % mod;
	}
	vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(k, vector<int>(2)));
	vector<vector<int>> ps(n+1, vector<int>(k));
	ps[0][0] = dp[0][0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < k; ++j) {
			if (j) dp[i][j][0] = (dp[i-1][j-1][0] + dp[i-1][j-1][1]) % mod;
			if (i >= 3 && j) dp[i][j][1] = ps[i-3][j-1];
			ps[i][j] = (ps[i-1][j] + dp[i][j][0] + dp[i][j][1]) % mod;
		}
	}
	for (int i = n - 2; i >= 0; --i) {
		for (int j = 0; j + 2 < k; ++j) {
			tot = (tot - (dp[i][j][0] + dp[i][j][1]) * (n-1-i)) % mod;
			tot = (tot + mod) % mod;
		}
	}
	cout << tot << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
