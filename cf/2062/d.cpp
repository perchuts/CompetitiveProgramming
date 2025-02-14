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
	vector<array<int, 2>> intr(n);
	vector<vector<int>> g(n);
	for (auto& x : intr) cin >> x[0] >> x[1];
	for (int i = 0; i < n-1; ++i) {
		int u, v; cin >> u >> v;
		--u, --v;
		g[u].pb(v), g[v].pb(u);
	}
	vector<int> need(n, 1e18);
	int ans = 0, root = 0;
	auto dfs = [&] (auto&& self, int u, int p) -> void {
		for (auto v : g[u]) {
			if (v == p) continue;
			self(self, v, u);
			ckmin(need[u], need[v]);
		}
		ckmin(need[u], (intr[u][0] <= intr[root][0] ? 1e18 : intr[u][0] - intr[root][0]));
	};
	for (int i = 0; i < n; ++i) if (intr[root][0] > intr[i][0]) root = i; 
	dfs(dfs, root, root);
	auto dfs2 = [&] (auto&& self, int u, int p, int foi) -> void {
		if (need[u] > 1e10) return;
		if (need[u] and u != p) ans += need[u], foi += need[u];
		for (auto v : g[u]) {
			if (v == p) continue;
			need[v] -= foi;
			self(self, v, u, foi);
		}
	};
	dfs2(dfs2, root, root, 0);
	cout << root << ' ';
	cout << ans + intr[root][0] << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
