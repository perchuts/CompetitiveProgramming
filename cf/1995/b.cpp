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
 	int n, m; cin >> n >> m;
	vector<int> v(n), c(n);
	for (auto& x : v) cin >> x;
	for (auto& x : c) cin >> x;
	vector<int> ord(n); iota(all(ord), 0);
	sort(all(ord), [&] (int a, int b) {
		return v[a] < v[b];
	});
	// sei que gcd(x, x-1) = 1.
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		ckmax(ans, min(c[i], m / v[i]) * v[i]);	
	}
	for (int i = 1; i < n; ++i) {
		int x = v[ord[i]];
		if (v[ord[i-1]] != x-1) continue;
		int c1 = c[ord[i]], c2 = c[ord[i-1]];
		int v1 = x, v2 = x-1;
		int l = m/x, r = c1+c2;
		while (l <= r) {
			int need = l + (r-l+1)/2;
			assert(need - min(need, c1) <= c2);
			assert(need - min(need, c2) <= c1);
			int mn = min(need, c1)*v1 + (need - min(need, c1)) * v2;
			int mx = min(need, c2) * v2 + (need - min(need, c2)) * v1;
			if (mn > mx) swap(mn, mx);
			if (mn > m) r = need - 1;
			else {
				if (mn <= m && m <= mx) ans = m;
				if (mn <= m) ckmax(ans, mn);
				if (mx <= m) ckmax(ans, mx);
				l = need + 1;
			}
		}
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
