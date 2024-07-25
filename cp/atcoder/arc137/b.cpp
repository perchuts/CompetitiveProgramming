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
	vector<int> v(n);
	int tot = 0;
	for (auto& x : v) {
		cin >> x;
		tot += x;
		x = (x == 0 ? 1 : -1);
	}
	vector<int> pref(n + 1);
	for (int i = 1; i <= n; ++i) pref[i] = pref[i-1] + v[i-1];
	int mx = 0, mn = 0, mxplus = 0, mxminus = 0;
	for (int i = 1; i <= n; ++i) {
		ckmax(mxplus, pref[i] - mn);
		ckmax(mxminus, mx - pref[i]);
		ckmax(mx, pref[i]);
		ckmin(mn, pref[i]);
	}
	cout << mxplus + mxminus + 1 << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
