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

bitset<1000000005> foi;
void solve(){
	int n; cin >> n;
	// gcd of v_p's must be greater than 1
	// iterate over gcd, do some inclusion exclusion??
	// know that p <= sqrt(n)
	int ans = 1;
	vector<int> big;
	int sq = sqrt(n);
	assert(sq * sq + 2 * sq + 1 > n);
	for (int i = 2; i <= 1000000; ++i) {
		int cur = i * i, pot = 2;
		while (cur <= n) {
			pot++;
			if (cur > 1000000 && cur <= sq && foi[cur] == 0) ans--;
			if (cur <= sq) {
				if (foi[cur] == 0)ans++, foi[cur] = 1;
			} else big.pb(cur);
			if (cur >= (2*n)/i) break;
			cur *= i;
		}
	}
	sort(all(big));
	big.erase(unique(all(big)), end(big));
	ans += big.size() + max(0ll, sq - 1000000);
	cout << ans << endl;
	// agora vamos pegar quadrados de numeros grandes o bastante
	// 1e6 < a < 1e9
	// a^2 nao eh representavel como numero antes
	
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
