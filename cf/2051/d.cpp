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
	int n, x, y; cin >> n >> x >> y;
	vector<int> a(n);
	for (auto& z : a) cin >> z;
	sort(all(a));
	int ans = 0, ss = 0;
	for (auto z : a) ss += z;
	for (int i = 1; i < n; ++i) {
		int l = 0, r = i-1, mn = -1;
		while (l <= r) {
			int md = l + (r-l+1)/2;
			if (ss - a[i] - a[md] <= y) mn = md, r = md-1;
			else l = md+1;
		}
		l = 0, r = i-1;
		int mx = -1;
		while (l <= r) {
			int md = l + (r-l+1)/2;
			if (ss - a[i] - a[md] >= x) mx = md, l = md+1;
			else r = md-1;
		}
		if (mn == -1 or mx == -1) continue;
		ans += max(0ll, mx-mn+1);
	}
	cout << ans << endl;


}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
