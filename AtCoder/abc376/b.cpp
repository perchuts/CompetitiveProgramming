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
	int n, q; cin >> n >> q;
	int l = 0, r = 1, tot = 0;
	while (q--) {
		char c; int pos; cin >> c >> pos;
		--pos;
		if (c == 'L') {
			// ir de um sentido, ir no outro
			int ans = 0, ok = 1;
			for (int i = l; i != pos; i = (i+1)%n) {
				if (i == r) { ok = 0; break; }	
				ans++;
			}
			if (ok) tot += ans;
			else {
				ans = 0;
				for (int i = l; i != pos; i = (i+n-1)%n) {
					assert(i != r);
					ans++;
				}
				tot += ans;
			}
			l = pos;
		} else {
			int ans = 0, ok = 1;
			for (int i = r; i != pos; i = (i+1)%n) {
				if (i == l) { ok = 0; break; }	
				ans++;
			}
			if (ok) tot += ans;
			else {
				ans = 0;
				for (int i = r; i != pos; i = (i+n-1)%n) {
					assert(i != l);
					ans++;
				}
				tot += ans;
			}
			r = pos;
		}
	}
	cout << tot << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
