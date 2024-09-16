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
	vector<vector<int>> weights(n);
	vector<int> a(n), w(n);
	for (auto& x : a) cin >> x, --x;
	for (int i = 0; i < n; ++i) {
		int x; cin >> x;
		weights[a[i]].pb(x);
	}
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		sort(all(weights[i]));
		for (int j = 0; j < sz(weights[i]) - 1; ++j) ans += weights[i][j];
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
