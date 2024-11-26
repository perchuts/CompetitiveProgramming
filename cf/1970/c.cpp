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
	int n, t; cin >> n >> t;
	vector<vector<int>> g(n);
	for (int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		--u, --v;
		g[u].pb(v), g[v].pb(u);
	}
	vector<int> dp(n), ans(n);
	vector<ii> ganha(n, make_pair(-1, -1));
	auto dfs = [&] (auto&& dfs, int u, int p) -> void {
		for (auto v : g[u]) {
			if (v == p) continue;
			dfs(dfs, v, u);
			dp[u] |= (dp[v] ^ 1);
			if (dp[v] == 0) {
				if (ganha[u].first == -1) ganha[u].first = v;
				else ganha[u].second = v;
			}
		}
	};
	dfs(dfs, 0, 0);
	auto dfs2 = [&] (auto&& dfs2, int u, int p) -> void {
		// atualizar a dp do meu pai
		if (u != p) {
			int ndp_p = ((ganha[p].first != -1 and ganha[p].first != u) or (ganha[p].second != -1 and ganha[p].second != u));
			ans[u] = ((dp[u]==1) | (ndp_p == 0));
			if (ndp_p == 0) ganha[u].second = p;
		} else ans[u] = dp[u];
		for (auto v : g[u]) {
			if (v == p) continue;
			dfs2(dfs2, v, u);
		}
	};
	dfs2(dfs2, 0, 0);
	for (int i = 0; i < t; ++i) {
		int x; cin >> x;
		--x;
		cout << (ans[x] ? "Ron" : "Hermione") << endl;
	}
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
