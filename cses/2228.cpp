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

int fexp(int b, int e) {
	int ans = 1;
	while (e) {
		if (e&1) ans = ans * b % mod;
		b = b * b % mod, e /= 2;
	}
	return ans;
}

void solve(){
	int n, k; cin >> n >> k;
 	vector<int> fat(n+1, 1), ifat(n+1);
	for (int i = 1; i <= n; ++i) fat[i] = fat[i-1] * i % mod;
	ifat[n] = fexp(fat[n], mod - 2);
	for (int i = n - 1; i >= 0; --i) ifat[i] = (i + 1) * ifat[i+1] % mod;
	auto c = [&] (int a, int b) {
		return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
	};
	int ans = 0;
	for (int i = 1; i <= k; ++i) {
		int q = c(k, i) * fexp(i, n) % mod;
		if (i % 2 == k % 2) ans = (ans + q) % mod;
		else ans = (ans + mod - q) % mod;
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}