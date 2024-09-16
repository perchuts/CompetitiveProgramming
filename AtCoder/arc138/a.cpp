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
	int n, k; cin >> n >> k;
	vector<int> a(n);
	int mn = inf, mx = 0;
	for (int i = 0; i < n; ++i) cin >> a[i], ckmax(mx, a[i]);
	for (int i = 0; i < k; ++i) ckmin(mn, a[i]);
	vector<int> out;
	for (int i = k; i < n; ++i) out.pb(a[i]);
	for (int i = 1; i < sz(out); ++i) ckmax(out[i], out[i-1]);
	int ans = 1e18;
	for (int i = 0; i < k; ++i) {
		int good = upper_bound(all(out), a[i]) - begin(out);
		if (good != sz(out)) ckmin(ans, k - i + good);
	}
	cout << (ans==1e18?-1:ans) << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
