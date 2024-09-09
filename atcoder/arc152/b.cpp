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
	int n, l; cin >> n >> l;
	vector<int> a(n+2); 
	a[0] = 0, a[n+1] = l;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	int ans = 1e18;
	for (int i = 1; i <= n; ++i) {
		int encontro = l - a[i];
		auto x = lower_bound(all(a), encontro) - begin(a);
		ckmin(ans, 2*(l+min((x == 1 ? 1e18 : encontro-a[x-1]), (x == n+1 ? 1e18 : a[x]-encontro))));
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
