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

int fat[maxn], ifat[maxn];

int fexp(int b, int e) {
	int ans = 1, p = b;
	while (e) {
		if (e&1) ans = ans * p % mod;
		p = p * p % mod, e /= 2;
	}
	return ans;
}

int comb(int a, int b) {
	if (b > a) return 0;
	return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
}

void solve(){
 	 int n; cin >> n;
	 int ans = 1;
	 for (int i = 1; i <= n; ++i) { 
		for (int j = i + 1; j <= min(n, 2 * i + 1); ++j) {
			int kk = (j * comb(j-1, i) % mod * comb(n - j, 2*i-j+1)) % mod;
			ans = (ans + kk) % mod;
		}
		if (2 * i + 1 > n) {
			ans = (ans + (1+2*i) * comb(n, i)) % mod;
		}
	 }
	 cout << ans << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  fat[0] = 1;
  for (int i = 1; i < maxn; ++i) fat[i] = fat[i-1] * i % mod;
  ifat[maxn-1] = fexp(fat[maxn-1], mod - 2);
  for (int i = maxn - 2; i >= 0; --i) ifat[i] = (i + 1) * ifat[i+1] % mod;
  while(t--) solve();
}
