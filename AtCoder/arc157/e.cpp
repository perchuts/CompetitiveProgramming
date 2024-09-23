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

const int inf = 100000+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

void solve(){
 	int n, a, b, c; cin >> n >> a >> b >> c;
	if (n == 1) {
		cout << "Yes" << endl;
		return;
	}
	vector<vector<int>> g(n);
	vector<vector<vector<int>>> dp(n);
	vector<int> subt(n);
	for (int i = 1; i < n; ++i) {
		int v; cin >> v;
		v--;
		g[v].pb(i), g[i].pb(v);
	}
	if (c % 2 == 1) {
		cout << "No" << endl;
		return;
	}
	c /= 2;
	auto dfs = [&] (auto&& self, int u, int p) -> void {
		if (sz(g[u]) == 1) {
			dp[u] = vector<vector<int>>(2, vector<int>(2));
			dp[u][0][1] = dp[u][1][0] = -inf;
			subt[u] = 1;
			return;
		}
		int l = -1, r = -1;
		for (auto v : g[u]) {
			if (v == p) continue;
			if (l == -1) l = v;
			else r = v;
			self(self, v, u);
			subt[u] += subt[v];
		}
		dp[u] = vector<vector<int>>(2, vector<int>(subt[u]+1, -inf));
		for (int i = 0; i <= subt[l]; ++i) {
			for (int j = 0; j <= subt[r]; ++j) {
				ckmax(dp[u][0][i+j], max(dp[l][0][i], dp[l][1][i]) + max(dp[r][0][j], dp[r][1][j]));
				ckmax(dp[u][1][i+j], dp[l][0][i] + dp[r][0][j] + 1);
			}
		}
	};
	dfs(dfs, 0, 0);
	int need = b - c;
	if (need >= 0 and subt[0] >= need and dp[0][0][need] >= c) {
		cout << "Yes" << endl;
		return;
	}
	if (c >= 1) {
		need = b - (c-1);
		if (need >= 0 and subt[0] >= need and dp[0][1][need] >= c) {
			cout << "Yes" << endl;
			return;
		}
	}
	cout << "No" << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
