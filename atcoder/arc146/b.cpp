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
int bit(int a, int x) { return ((a >> x) & 1); }
void solve(){
 	int n, m, k; cin >> n >> m >> k;
	vector<int> a(n);
	for (auto& x : a) cin >> x;
	int ans = 0;
	for (int i = 30; i >= 0; --i) {
		ans += (1 << i);
		vector<int> cost;
		for (auto x : a) {
			if (ans >= x) {
				cost.pb(ans-x);
			} else {
				int need = ans;
				for (int j = 30; j >= 0; --j) {
					if (bit(ans, j) < bit(x, j)) need += (1 << j);
					if (bit(ans, j) > bit(x, j)) break;
				}
				cost.pb(need-x);
			}
		}
		int ss = 0;
		sort(all(cost));
		for (int j = 0; j < k; ++j) ss += cost[j];
		if (ss > m) ans -= (1 << i);
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
