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
	int n, t; cin >> n >> t;
	vector<int> a(n), b(n);
	vector<int> ord(n); iota(all(ord), 0);
	for (int i = 0; i < n; ++i) cin >> a[i] >> b[i];
	sort(all(ord), [&] (int x, int y) { return a[x] < a[y]; });
	vector<vector<int>> dp(n+1, vector<int>(t));
	for (int i = 1; i <= n; ++i) {
		int pos = ord[i-1];
		for (int j = 0; j < t; ++j) {
			dp[i][j] = dp[i-1][j];
			if (j >= a[pos]) ckmax(dp[i][j], dp[i-1][j-a[pos]]+b[pos]);
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) for (int j = 0; j < t; ++j) {
		ckmax(ans, dp[i-1][j] + b[ord[i-1]]);
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
