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
	vector<int> v(n), freq(n+1);
	for (auto& x : v) cin >> x, freq[x]++;
	sort(all(v));
	vector<vector<int>> dp(n+1, vector<int>(n+1));
	int distinct = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
			if (freq[i] && freq[i] <= j && distinct - dp[i-1][j-freq[i]] >= j) ckmax(dp[i][j], dp[i-1][j-freq[i]]+1);
		}
		distinct += (freq[i] != 0);
	}
	cout << distinct - dp[n][n] << endl;
}

int32_t main(){_
  int t; cin >> t;
  while(t--) solve();
}
