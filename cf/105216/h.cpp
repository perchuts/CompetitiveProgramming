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
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

void solve(){
	int n, r, c; cin >> n >> r >> c;
	--r, --c;
	vector<int> hired, v(n);
	iota(all(v), 1);
	int pt1 = 0, pt2 = n-1;
	while (sz(v) > 2) {
		pt1 = (pt1 + r) % sz(v);
		pt2 = (pt2 - c) % sz(v);
		if (pt2 < 0) pt2 += sz(v);
		if (pt1 == pt2) {
			hired.pb(v[pt1]);
			v.erase(begin(v)+pt1);
			pt1 %= sz(v);
			pt2 = (pt2 + sz(v) - 1) % sz(v); 
		} else {
			v.erase(begin(v)+max(pt1, pt2));
			v.erase(begin(v)+min(pt1, pt2));
			if (pt2 < pt1) pt1 = (pt1 + sz(v) - 1) % sz(v); 
			else pt2 = (pt2 + sz(v) - 1) % sz(v); 
			pt2 = (pt2 + sz(v) - 1) % sz(v); 
			pt1 %= sz(v);
		}
	}
	for (auto x : v) hired.pb(x);
	sort(all(hired));
	for (auto x : hired) cout << x << ' ';
	cout << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
