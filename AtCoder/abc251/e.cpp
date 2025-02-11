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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

void solve(){
	int n; cin >> n;
	vector<int> cost(n);
	for (auto& x : cost) cin >> x;
	vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(2)));
	dp[0][1][1] = cost.back() + cost[0], dp[0][1][0] = cost[0];
	dp[0][0][0] = 1e18, dp[0][0][1] = cost.back();
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < 2; ++j) {
			dp[i][0][j] = dp[i-1][1][j];
			dp[i][1][j] = min(dp[i-1][1][j], dp[i-1][0][j]) + cost[i];
		}
	}
	cout << min({dp[n-1][1][0], dp[n-1][0][0], dp[n-2][0][1], dp[n-2][1][1]}) << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
