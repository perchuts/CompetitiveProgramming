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
	auto fexp = [&] (int b, int e) {
		int ans = 1;
		b %= mod;
		while (e) {
			if (e&1) ans = ans * b % mod;
			b = b * b % mod, e /= 2;
		}
		return ans;
	};
	int n, k; cin >> n >> k;
	vector<int> dp(k+1);
	int invn = fexp(n, mod-2);
	if (k <= n) {
		int frac = (n-k+1) % mod * invn % mod;
		frac = (mod + 1 - frac) % mod;
		dp[k] = fexp(frac, mod-2);
		for (int i = k-1; i >= 0; --i) {
			dp[i] = (n-i) % mod * invn % mod * dp[i+1] % mod;
			dp[i] = (dp[i] + 1) % mod;
		}
	} else {
		// k > n
		dp[n] = 1;
		for (int i = n-1; i >= 0; --i) {
			dp[i] = (n-i) % mod * invn % mod * dp[i+1] % mod;
			dp[i] = (dp[i] + 1) % mod;
		}
	}
	cout << dp[0] << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
