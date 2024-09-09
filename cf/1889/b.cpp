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
 	int n, c; cin >> n >> c;
	vector<int> v(n);
	for (auto& x : v) cin >> x;
	vector<ii> cost;
	for (int i = 2; i <= n; ++i) cost.pb({i * c - v[i-1], v[i-1]});
	sort(all(cost));
	int S = v[0];
	for (auto [x, y] : cost) {
		if (S < x) {
			cout << "NO" << endl;
			return;
		}
		S += y;
	}
	cout << "YES" << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
