#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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
	vector<ii> ev(q);
	for (auto& [x, y] : ev) {
		char lixo; cin >> x >> lixo;
		--x;
		if (lixo == '+') y = 1;
		else y = -1;
	}
	vector<vector<int>> cost(n, vector<int>(n, 1));
	vector<int> add(n);	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			int d = 0, tot = 0;
			for (auto [x, y] : ev) {
				if (x == i) {
					if (y == 1) d--, tot++;
				} else if (x == j) {
					if (y == -1) d++;
				}
				ckmax(cost[i][j], -d+1);
			}
			add[i] = tot;
		}
	}
	vector<vector<int>> dp((1<<n), vector<int>(n, 1e9+1));
	for (int i = 1; i < (1<<n); ++i) {
		for (int j = 0; j < n; ++j) {
			if (i >> j & 1) {
				if (i == (1 << j)) {
					dp[i][j] = 1;
					continue;
				}		
				for (int k = 0; k < n; ++k) {
					if (k == j) continue;
					if (i >> k & 1) ckmin(dp[i][j], dp[i-(1<<j)][k] + cost[k][j]);	
				}
			}
		}
	}
	int ans = 1e9;
	for (int i = 0; i < n; ++i) ckmin(ans, dp[(1<<n)-1][i] + add[i]);
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
