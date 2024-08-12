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
int dp[85][85][85*85];
void solve() {
	int n; cin >> n;
	vector<int> v(n + 1);
	vector<int> dif;
	for (int i = 1; i <= n; ++i) cin >> v[i];
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			dif.pb(v[i] - v[j]);
		}
	}
	sort(all(dif));
	dif.erase(unique(all(dif)), end(dif));
	vector<vector<int>> pos(n+1, vector<int>(n+1));
	cout << endl;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			int d = v[i] - v[j];
			pos[i][j] = lower_bound(all(dif), d) - begin(dif);
		}
	}
	vector<int> ans(n+1);
	for (int i = 1; i <= n; ++i) {
		ans[1]++;
		ans[2] += i-1;
		for (int j = i - 1; j >= 1; --j) {
			dp[i][2][pos[i][j]] = (dp[i][2][pos[i][j]] + 1) % mod;
		}
		for (int j = 3; j <= i; ++j) {
			for (int last = i-1; last >= 1; --last) {
				dp[i][j][pos[i][last]] = (dp[i][j][pos[i][last]] + dp[last][j-1][pos[i][last]]) % mod;
			}
		}
	}
	for (int w = 1; w <= n; ++w) {
		for (int j = 3; j <= w; ++j) {
			for (int i = 0; i < sz(dif); ++i) ans[j] = (ans[j] + dp[w][j][i]) % mod;
		}
	}
	for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
}

int32_t main() {_
	int t = 1; //cin >> t;
	while(t--) solve();
}
