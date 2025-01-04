#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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

int query(int l, int r) {
	cout << "? " << l << ' ' << r << endl;
	int x; cin >> x;
	return x;
}

void solve(){
	int n; cin >> n;
	int a = query(1, n/2), b = query(1, n/4), c = query(n/4+1, n/2);
	int lie = 0;
	if (a == 0 && (b != 0 or c != 0)) lie = 1;
	if (a == 1 && (b == c)) lie = 1;
	int l = n/2+1, r = n-1, ans;
	if (lie == 1) l = 2, r = n/2;
	while (l <= r) {
		int md = l + (r-l+1)/2;
		if (a == 0) {
			if (query(n-md+1, n) ^ lie) l = md+1;
			else r = md-1, ans = md;
		} else {
			if (query(1, md) ^ lie) l = md+1;
			else r = md-1, ans = md;
		}
	}
	cout << "! " << ans << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
