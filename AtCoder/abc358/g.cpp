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
	int n, m, k; cin >> n >> m >> k;
	vector<vector<int>> grid(n, vector<int>(m));
	int si, sj; cin >> si >> sj;
	for (auto& x : grid) for (auto& y : x) cin >> y;
	--si, --sj;
	vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(n * m + 1, -1e18)));
	dp[si][sj][0] = 0;
	int ans = grid[si][sj] * k;
	for (int i = 1; i <= min(n * m, k); ++i) {
		for (int a = 0; a < n; ++a) {
			for (int b = 0; b < m; ++b) {
				if (a) ckmax(dp[a][b][i], dp[a-1][b][i-1] + grid[a][b]);
				if (b) ckmax(dp[a][b][i], dp[a][b-1][i-1] + grid[a][b]);
				if (a != n-1) ckmax(dp[a][b][i], dp[a+1][b][i-1] + grid[a][b]);
				if (b != m-1) ckmax(dp[a][b][i], dp[a][b+1][i-1] + grid[a][b]);
				ckmax(ans, dp[a][b][i] + (k - i) * grid[a][b]);
			}
		}
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
