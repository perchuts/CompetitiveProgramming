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

int fexp(int b, int e) {
	int ans = 1;
	while (e) {
		if (e&1) ans = ans * b % mod;
		e /= 2, b = b * b % mod;
	}
	return ans;
}

void solve(){
	int n, m; cin >> n >> m;
	vector grid(n, vector(m, 0));
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
		char x; cin >> x;
		grid[i][j] = (x == 'Y');
	}
	vector<int> fat(n+m+1), ifat(n+m+1);
	fat[0] = 1;
	for (int i = 1; i <= n+m; ++i) fat[i] = fat[i-1] * i % mod;
	ifat[n+m] = fexp(fat[n+m], mod-2);
	for (int i = n+m-1; i >= 0; --i) ifat[i] = ifat[i+1] * (i+1) % mod;
	auto c = [&] (int a, int b) {
		return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
	};
	vector dp(n+1, vector(m+1, 0));
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % mod;
			if (j != 1) {
				if (grid[i-1][j-1] && grid[i-1][j-2]) {
					dp[i][j] = (dp[i][j] + c(i+j-3, i-1)) % mod;
					int tot = c(i+j-3, i-1) * c(n-i+m-j, n-i) % mod;
					int tot2 = 2 * dp[i][j-1] * c(n-i+m-j, n-i) % mod;
					ans = (ans + tot + tot2) % mod;
				}
			}
			if (i != 1) {
				if (grid[i-1][j-1] && grid[i-2][j-1]) {
					dp[i][j] = (dp[i][j] + c(i+j-3, j-1)) % mod;
					int tot = c(i+j-3, j-1) * c(n-i+m-j, n-i) % mod;
					int tot2 = 2 * dp[i-1][j] * c(n-i+m-j, n-i) % mod;
					ans = (ans + tot + tot2) % mod;
				}
			}
		}
	}
	cout << ans << endl;

}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
