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
	int n, x; cin >> n >> x;
	vector<int> ans;
	ans.pb(x);
	if (n&1) {	
		int pl = n / 2 + (x <= n/2), pr = pl+1;
		int type = 0;
		for (int i = 0; i < n - 1; ++i) {
			if (type^(i&1)) {
				if (pr == x) pr++;
				ans.pb(pr++);
			} else {
				if (pl == x) pl--;
				ans.pb(pl--);
			}
		}
	} else {
		int pl = n / 2, pr = pl+1;
		int type = (x <= n/2);
		for (int i = 0; i < n - 1; ++i) {
			if (type^(i&1)) {
				if (pr == x) pr++;
				ans.pb(pr++);
			} else {
				if (pl == x) pl--;
				ans.pb(pl--);
			}
		}
	}
//	int cur = 0;
//	int corner = ((n % 2 == 1 && x == (n+1)/2) || (n%2 == 0 && (x == n/2 || x == n/2+1)));
//	for (int i = 2-corner; i < n; ++i) {
//	int novo = abs(ans[i] - ans[i-1]);
//	if (novo <= cur) {
//		cout << n << ' ' << x << endl;
//		exit(0);
//	}
//	cur = novo;
	
//}
	for (auto y : ans) cout << y << ' ';
}

int32_t main(){_
//int n; cin >> n;
//for (int i = 1; i <= n; ++i) {
//	for (int j = 1; j <= i; ++j) {
//		solve(i, j);
//	}
//}
	solve();
}
