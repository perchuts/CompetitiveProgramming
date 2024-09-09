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
const int mod = 1e9;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }


void solve(){
 	int N, m, k; cin >> N >> m >> k; 
	N--;
	N = 21;
	vector<ii> v(m);
	for (auto& [x, y] : v) cin >> x >> y;
	auto brute = [&] (auto&& self, int n) -> vector<vector<int>> {
		n += 5;
		vector dp(n+1, vector<int>(k+1));
		vector freq(11, vector<int>(k+1));
		for (auto [x, y] : v) freq[x][y]++;	
		dp[0][0] = 1;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= k; ++j) {
				for (int a = 1; a <= min(10ll, i); ++a) for (int b = 0; b <= j; ++b) dp[i][j] = (dp[i][j] + freq[a][b] * dp[i-a][j-b]) % mod;
			}
		}
		return dp;
	};
	auto solve_small = [&] () {
		auto dp = brute(brute, N);
		int ans = 0;
		for (int i = 0; i <= k; ++i) ans = (ans + dp[N][i]) % mod;
		cout << ans << endl;
	};
	if (N <= 20) {
		solve_small();
		return;
	}
	auto solve = [&] (auto&& self, int n) -> vector<vector<int>> {
		if (n <= 20) {
			auto dp = brute(brute, n);
			vector<vector<int>> ans;
			for (int i = n - 5; i <= n + 5; ++i) ans.pb(dp[i]);
			return ans;
		}
		auto dp = self(self, n/2);
		vector<vector<int>> ndp(11, vector<int>(k+1));
		for (int a = 0; a <= 10; ++a) {
			for (int c = 0; c <= a; ++c) {
				int id_real = 2*(n/2 - 5) + a + c;
				if (id_real < n - 5 || n + 5 < id_real) continue;
				id_real -= n - 5;
				for (int b = 0; b <= k; ++b) {
					for (int d = 0; d <= k - b; ++d) {
						ndp[id_real][b+d] = (ndp[id_real][b+d] + dp[a][b] * dp[c][d]) % mod;
					}
				}
			}
		}
		return ndp;
	};
	auto dp = solve(solve, N);
	int ans = 0;
	for (int i = 0; i <= k; ++i) ans = (ans + dp[5][i]) % mod;
	cout << ans << endl;
	solve_small();
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
