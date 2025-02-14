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
	int n, k; cin >> n >> k;
	vector<int> fat(n+1, 1), ifat(n+1), dp(n+1);
	for (int i = 1; i <= n; ++i) fat[i] = i * fat[i-1] % mod;
	auto fexp = [&] (int b, int e) {
		int ans = 1;
		while (e) {
			if (e&1) ans = ans * b % mod;
			b = b * b % mod, e /= 2;
		}
		return ans;
	};
	ifat[n] = fexp(fat[n], mod-2);
	for (int i = n-1; ~i; --i) ifat[i] = (i + 1) * ifat[i+1] % mod;
	dp[n] = 1;
	int ans = (k == n);
	for (int i = n-1; i >= 1; --i) {
		int cur = fat[n-i-1] * (dp[i+1]-(i+k>=n ? 0 : dp[i+1+k]) + mod) % mod;
		cur = (cur * ifat[n-i]) % mod;
		if (i <= k) ans = (ans + cur) % mod;
		dp[i] = (cur + dp[i+1]) % mod;
	}
	ans = ans * fat[n-1] % mod;
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
