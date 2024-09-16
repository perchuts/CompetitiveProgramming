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

int c(int a, int b) {
	if (a < b) return 0;
	return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
}

void solve(){
 	int n; cin >> n; 
	fat[0] = 1;
	for (int i = 1; i <= n*n; ++i) fat[i] = fat[i-1] * i % mod;
	ifat[n*n] = fexp(fat[n*n], mod - 2);
	for (int i = n * n - 1; i >= 0; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
	int ans = fat[n*n];
	for (int i = 1; i <= n * n; ++i) {
		int escolhe = c(i-1, n-1) * c(n*n-i, n-1) % mod;
		escolhe = escolhe * n % mod * n % mod;
		escolhe = escolhe * fat[n-1] % mod * fat[n-1] % mod;
		escolhe = escolhe * fat[n*n-2*n+1] % mod;
		ans = (ans - escolhe + mod) % mod;
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
