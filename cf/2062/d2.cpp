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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

void solve(){
	int n; cin >> n;
	vector<ii> intr(n);
	vector<vector<int>> g(n);
	int start = 0;
	for (auto& [x, y] : intr) cin >> x >> y, ckmax(start, x);
	for (int i = 0; i < n-1; ++i) {
		int u, v; cin >> u >> v;
		--u, --v;
		g[u].pb(v), g[v].pb(u);
	}
	int l = start, r = 1e15, ans = 1e15;
	vector<ii> bounds(n);
	vector<vector<int>> dp(n, vector<int>(2));
	auto dfs = [&] (auto&& self, int u, int p) {
		if (max(dp[u][0], dp[u][1]) < 0) return 0ll;
		auto [lx, rx] = bounds[u];
		int ok = 1;
		for (auto v : g[u]) {
			if (v == p) continue;
			auto [lx2, rx2] = bounds[v];
			if (dp[u][0] >= 0) {
				ckmax(dp[v][0], dp[u][0] + lx2-lx);
				ckmax(dp[v][1], dp[u][0] + rx2-lx);
			}
			if (dp[u][1] >= 0) {
				ckmax(dp[v][0], dp[u][1] + lx2-rx);
				ckmax(dp[v][1], dp[u][1] + rx2-rx);
			}
			ok &= self(self, v, u);
		}
		return ok;
	};
	auto possible = [&] (int x) {
		for (int i = 0; i < n; ++i) bounds[i] = {max(0ll, x-intr[i].second), x-intr[i].first}, dp[i][0] = dp[i][1] = -1e18;	
		dp[0][0] = dp[0][1] = 0;
		int z = dfs(dfs, 0, 0);
		cout << bounds[0].first << ' ' << bounds[0].second << endl;
		cout << "dp: " << endl;
		for (int i = 0; i < n; ++i) cout << dp[i][0] << ' ' << dp[i][1] << endl;;
		return z;
	};
	possible(6);
	cout << "A" << endl;
	return;
	while (l <= r) {
		int md = l + (r-l+1)/2;
		if (possible(md)) ans = md, r = md-1;
		else l = md+1;
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
