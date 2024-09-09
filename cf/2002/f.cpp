#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

const int maxn = 2e7 + 696969;

vector<int> primes;

bool p[maxn];

void solve(){
	int n, m; ll l, f; cin >> n >> m >> l >> f;
	if (l < f) swap(l, f);
	if (n > m) swap(n, m);
	int P = primes[upper_bound(all(primes), n) - begin(primes) - 1], st = max(0, P-100);
	vector dp(n-P+1, vector(n-st+1, 0));
	ll ans = 0;
	for (int i = P; i <= n; ++i) {
		for (int j = st; j <= n; ++j) {
			if (gcd(i, j) != 1) continue;
			if (max(i, j) == P) dp[i-P][j-st] = 1;
			if (i != P) dp[i-P][j-st] |= dp[i-1-P][j-st];
			if (j != st) dp[i-P][j-st] |= dp[i-P][j-1-st];
			if (dp[i-P][j-st]) ckmax(ans, l * i + j * f);
		}
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  primes.pb(0);
  int lst = 0, mxgap = 0;
  for (int i = 2; i < maxn; ++i) {
	  if (p[i]) continue;
	  primes.pb(i);
	  ckmax(mxgap, i - lst);
	  lst = i;
	  if (i > sqrt(maxn)) continue;
	  for (int j = i * i; j < maxn; j += i) p[j] = 1;
  }
  int tot = 0;
  vector<int> qq(mxgap+1);
  for (int i = 2; i <= mxgap; ++i) {
	 for (int j = 2; j <= i; ++j) {
			if (i % j == 0) {
				qq[j]++;
				break;
			}
	 }
  }
  cout << mxgap << endl;
  for (int i = 1; i <= mxgap; ++i) {
	  if (i <= 13) tot += (i-2) * qq[i];
	  if (p[i]) continue;
	  cout << i << ": " << qq[i] << endl;
  }
  cout << tot << endl;
  return 0;
  while(t--) solve();
}
