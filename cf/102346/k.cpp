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

void solve(){
	int n; cin >> n;
	if (n == 1) {
		cout << 2 << endl;
		exit(0);
	}
	if (n == 2) {
		cout << 24 << endl;
		exit(0);
	}
	vector<int> t(n+100);
	t[0] = 1;
	t[1] = 2, t[2] = 12;
	vector<int> pot(n + 1000);
	pot[0] = 1;
	for (int i = 1; i <= n; ++i) pot[i] = 2 * pot[i-1] % mod;
	for (int i = 3; i <= n; ++i) {
		t[i] = (2 * (t[i-1] + 2*t[i-2]) + pot[i]) % mod;
		if (i <= 10) cout << t[i] << endl;
	}
	int ans = 2*t[n] % mod;
	for (int i = 2; i < n; ++i) {
		ans += (pot[i+1]*t[n-i]) % mod;
		ans %= mod;
	}
	cout << ans << endl;
}
int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
