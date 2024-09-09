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
	vector<int> dp(n+1, 1e16), ndp = dp;
	vector digit = vector<vector<int>>(n, vector<int>(9));
	vector lists(9, vector<int>(n));
	vector pt(10, 1);
	for (int i = 1; i <= 9; ++i) pt[i] = 10 * pt[i-1];
	for (int i = 0; i < n; ++i) {
		int cur = v[i];
		for (int j = 0; j < 9; ++j) digit[i][j] = cur % 10, lists[j][i] = (j == 0 ? digit[i][j] : lists[j-1][i] + pt[j] * digit[i][j]), cur /= 10;
	}
	for (int j = 0; j < 9; ++j) sort(all(lists[j])), reverse(all(lists[j]));
	dp[0] = 0;
	for (int pot = 0; pot < 9; ++pot) {
		// vou calcular a dp pro pot
		ndp = vector<int>(n+1, 1e16);
		for (int i = 0; i <= n; ++i) {
			for (int use = 0; use <= 9; ++use) {
				if (i == 0) {
					int l = 0, r = n-1, ans = 0;
					while (l <= r) {
						int md = l + (r-l+1)/2;
						if (lists[pot][md] + pt[pot]*use >= pt[pot+1]) ans = l = md+1;
						else r = md - 1;
					}
					ckmin(ndp[ans], dp[i] + use*n - 9 * ans);
					continue;
				}
				int val = (pot?lists[pot-1][i-1]:0);

				int l = 0, r = n-1, ans = 0;

				while (l <= r) {
					int md = l + (r-l+1)/2, val_md = lists[pot][md];
					if (val_md + pt[pot] * use >= pt[pot+1] || (val_md + pt[pot] * (use+1) >= pt[pot+1] && (val_md % pt[pot] >= val))) l = ans = md+1;
					else r = md - 1;
				}
				ckmin(ndp[ans], dp[i] + use*n - 9 * ans);
			}
		}
		swap(dp, ndp);
	}
	int ans = 1e18;
	for (int i = 0; i <= n; ++i) ckmin(ans, dp[i]);
	for (int i = 0; i < n; ++i) for (int j = 0; j < 9; ++j) ans += digit[i][j];
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
