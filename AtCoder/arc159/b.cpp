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
	int a, b; cin >> a >> b;
	int ans = 0;
	while (min(a, b)) {
		int g = gcd(a, b), tries = min(a/g, b/g), k = abs(a-b);
		for (int j = 1; j*j <= k; ++j) {
			if (k % j) continue;
			if (j>1 and (a/g) % j == (b/g) % j) ckmin(tries, (a/g)%j);
			int j2 = k/j;
			if (j2>1 and (a/g) % j2 == (b/g) % j2) ckmin(tries, (a/g)%j2);
		}
		a -= tries*g, b -= tries*g, ans += tries;
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
