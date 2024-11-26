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
	int ans; cin >> ans;
	return ans;
}	

void solve(){
	int n; cin >> n;
	int x = query(1, n);
	if (x == 0) {
		cout << "! IMPOSSIBLE" << endl;
		return;
	}
	string s; 
	for (int i = 2; i <= n; ++i) {
		x = query(1, i);
		if (x != 0) {
			for (int j = 1; j <= i-x-1; ++j) s += '1';
			for (int j = 1; j <= x; ++j) s += '0';
			s += '1';
			break;
		}
	}
	assert(!s.empty());
	for (int i = sz(s)+1; i <= n; ++i) {
		int y = query(1, i);
		if (y > x) s += '1';
		else s += '0';
		x = y;
	}
	cout << "! " << s << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
