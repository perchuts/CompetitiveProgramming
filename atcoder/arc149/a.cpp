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
	int n, m; cin >> n >> m;
	ii best = {-1, -1};
	for (int i = 1; i <= 9; ++i) {
		string ans;
		int cur = 0;
		for (int j = 1; j <= n; ++j) {
			ans += char('0' + i);
			cur = 10 * cur + i;
			cur %= m;
			if (cur == 0) {
				ckmax(best, make_pair(j, i));
			}
		}
	}
	if (best.first == -1) cout << -1 << endl;
	else {
		for (int j = 0; j < best.first; ++j) cout << best.second;
	}
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}