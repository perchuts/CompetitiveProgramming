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
	vector<int> v(n);
	for (auto& x : v) cin >> x;
	sort(all(v), [] (int a, int b) {
		int t1 = 1, t2 = 1, cura = a, curb = b;
		while (cura) t1 *= 10, cura /= 10;
		while (curb) t2 *= 10, curb /= 10;
		return t2 * a + b > t1 * b + a;
	});
	vector<vector<int>> dp(n+1, vector<int>(4, -1));
	dp[0][0] = 0;
	for (int i = 1; i <= n; ++i) { 
		dp[i][0] = 0;
		int tam = 1, tmp = v[i-1];
		while (tmp) tam *= 10, tmp /= 10;
		for (int j = 1; j <= 3; ++j) {
			dp[i][j] = dp[i-1][j];
			// usar
			ckmax(dp[i][j], dp[i-1][j-1] * tam + v[i-1]);
		}
	}
	cout << dp[n][3] << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
