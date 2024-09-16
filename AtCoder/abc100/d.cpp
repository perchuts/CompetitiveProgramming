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
	int n, m; cin >> n >> m;
	vector<array<int, 3>> v(n);
	for (auto& x : v) cin >> x[0] >> x[1] >> x[2];
	if (m == 0) {
		cout << 0 << endl;
		return ;
	}
	int best = -1e18;
	for (int a = 0; a < 8; ++a) {
		vector<vector<int>> dp(n+1, vector<int>(m+1, -1e18));
		dp[0][0] = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= min(i, m); ++j) {
				dp[i][j] = dp[i-1][j];
				int score = 0;
				for (int w = 0; w < 3; ++w) {
					score += (((a>>w)&1) ? v[i-1][w] : -v[i-1][w]);
				}
				if (j) ckmax(dp[i][j], dp[i-1][j-1] + score);
			}
		}
		best = max(best, dp[n][m]);
	}
	cout << best << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
