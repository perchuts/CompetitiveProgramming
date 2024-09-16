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
		e /= 2, p = p * p % mod;
	}
	return ans;
}
void solve(){
	int n, k; cin >> n >> k;  
	if (n == 1) {
		cout << 1 << endl;
		return;
	}
	int p1 = 1, p2 = 0, div = fexp(n*n%mod, mod-2);
	int sobra = (n*n%mod-2*n+2)%mod;
	sobra = (sobra + mod) % mod;
	int pp = (sobra*div)%mod;
	int qq = (div*2)%mod;
	for (int i = 1; i <= k; ++i) {
		p1 = (pp*p1+(1-p1)*qq%mod)%mod;
		p1 = (p1 + mod) % mod;
		p2 = (pp*p2+(1-p2)*qq%mod)%mod;
		p2 = (p2 + mod) % mod;
	}
	int tot = (((n+1)*n)/2-1+mod) % mod;
	int ans = (p1 + (tot*p2)%mod)%mod;
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
