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
int fexp(int b, int e) {
	int ans = 1, p = b;
	while (e) {
		if (e&1) ans = ans * p % mod;
		p = p * p % mod, e /= 2;
	}
	return ans;
}
int fat[maxn], ifat[maxn];
void solve(){
	int n; cin >> n;  
	vector<int> c(26);
	for (auto& x : c) cin >> x;
	fat[0] = 1;
	for (int i = 1; i <= n; ++i) fat[i] = fat[i-1] * i % mod;
	ifat[n] = fexp(fat[n], mod - 2);
	for (int i = n - 1; i >= 0; --i) ifat[i] = ifat[i+1] * (i+1) % mod;
	vector<vector<int>> dp(2, vector<int>(n + 1));
	dp[1][n] = 1;
	auto comb = [&] (int a, int b) {
		return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
	};
	for (int i = 0; i < 26; ++i) {
		for (int j = 0; j <= n; ++j) {
			dp[i&1][j] = 0;
			for (int k = 0; k <= min(c[i], n-j); ++k) {
				dp[i&1][j] = (dp[i&1][j] + dp[(i&1)^1][j+k] * comb(j+k, k)) % mod;
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		int cx = comb(n, i);
		ans = (ans + dp[1][i] * fexp(cx, mod - 2)) % mod;
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
