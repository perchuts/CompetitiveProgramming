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
	vector<string> grid(n);
	for (auto& x : grid) cin >> x;
	vector<int> dp(1<<m, n + 1000);
	dp[0] = 0;
	for (int i = 0; i < n; ++i) {
		int mee = 0;
		for (int j = 0; j < m; ++j) if (grid[i][j] == 'o') mee += (1 << j);
		for (int j = 0; j < (1 << m); ++j) {
			dp[j|mee] = min(dp[j|mee], dp[j]+1);
		}
	}
	cout << dp.back() << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
