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
 	int a, b, c; cin >> a >> b >> c;
	int mx = max({a, b, c});
	int x1 = mx - a, x2 = mx - b, x3 = mx - c;
	a -= x2 + x3, b -= x1 + x3, c -= x1 + x2;
	if (a != b || a != c || a < 0) cout << -1 << endl;
	else cout << x1 + x2 + x3 + a << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
