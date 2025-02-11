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
const int mod = (119<<23)+1;
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
	vector<int> a(n), fat(n+1, 1), ifat(n+1), dp(n+1);
	for (auto& x : a) cin >> x;
	for (int i = 1; i <= n; ++i) fat[i] = fat[i-1] * i % mod;
	auto fexp = [&] (int b, int e) {
		int ans = 1;
		while (e) {
			if (e&1) ans = ans * b % mod;
			b = b * b % mod, e /= 2;
		}
		return ans;
	};
	ifat[n] = fexp(fat[n], mod-2);
	for (int i = n-1; ~i; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
	dp[0] = 1;
	for (int i = 0; i < n; ++i) {
		vector<int> ndp(n+1);
		for (int j = 0; j <= n; ++j) ndp[j] = (a[i] * dp[j] + (j == 0 ? 0 : dp[j-1])) % mod;
		swap(dp, ndp);
	}
	auto choose = [&] (int A, int b) {
		int ans = ifat[b];
		for (int i = A; i > A-b; --i) ans = ans * i % mod; 
		return ans;
	};	
	int ans = 0;
	for (int i = 0; i <= min(n, k); ++i) {
		int resto = choose(k, i) * fat[i] % mod;	
		resto = resto * dp[i] % mod;
		resto = resto * fexp(n, k-i) % mod; 
		ans = (ans + resto) % mod;
	}
	cout << (ans * fexp(fexp(n, k), mod-2)) % mod << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
