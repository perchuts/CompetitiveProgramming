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

void solve(){
 	int n, k; cin >> n >> k;
	string s; cin >> s;
	vector<vector<int>> dp(n + 1, vector<int>((1<<k)));
	for (auto& x : s) {
		if (x == 'A') x = '0';
		if (x == 'B') x = '1';
	}
	for (int i = 0; i < (1 << k); ++i) {
		bool ok = 1;
		for (int j = 0; j < k; ++j) {
			if (s[k-1-j] == '?') continue;
			ok &= ((s[k-1-j]-'0') == ((i>>j)&1));
		}
		bool pal = 1;
		for (int j = 0; j < k; ++j) pal &= (((i>>j)&1) == ((i>>(k-1-j))&1));
		if (pal) continue;
		dp[k-1][i] = ok;
	}
	int fix = (1 << k) - 1;
	for (int i = k; i < n; ++i) {
		for (int j = 0; j < (1 << k); ++j) {
			for (int bit = 0; bit < 2; ++bit) {
				if (s[i] == char('0'+bit) || s[i] == '?') {
					int nova = 2 * j + bit, pal = 1;
					for (int w = 0; w < k; ++w) pal &= (((nova>>w)&1) == ((nova>>(k-1-w))&1));
					if (!pal) dp[i][nova&fix] = (dp[i][nova&fix] + dp[i-1][j]) % mod;
				}
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < (1 << k); ++i) ans = (ans + dp[n-1][i]) % mod;
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
