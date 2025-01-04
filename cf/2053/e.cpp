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
	vector<vector<int>> g(n);
	for (int i = 0; i < n-1; ++i) {
		int u, v; cin >> u >> v;
		--u, --v;
		g[u].pb(v), g[v].pb(u);
	}
	int ans = 0, fl = 0;
	for (int i = 0; i < n; ++i) if (sz(g[i]) == 1) ans++, fl++;
	ans = (n-ans) * ans;
	vector<int> no_leaf(n), par(n);
	auto dfs1 = [&] (auto&& self, int u, int p) -> void {
		no_leaf[u] = (sz(g[u]) > 1);
		par[u] = p;
		for (auto v : g[u]) {
			if (v == p) continue;
			no_leaf[u] &= (sz(g[v]) > 1);
			self(self, v, u);
		}
	};
	vector<int> subt(n), gajos(n);
	auto dfs2 = [&] (auto&& self, int u, int p) -> int {
		int tot = 0;
		gajos[u] = (sz(g[u]) > 1);
		for (auto v : g[u]) {
			if (v == p) continue;
			tot += self(self, v, u);
			gajos[u] += gajos[v];
			if (no_leaf[u] and sz(g[v]) != 1) tot++, subt[v]++;
		}
		subt[u] = tot;
		// N ancestral de A
		if (no_leaf[u]) ans += (gajos[u]-1-tot);
		return tot;
	};
	auto dfs3 = [&] (auto&& self, int u, int p, int total, int total2) -> void {
		if (no_leaf[u]) {
			ans += total2 - total;
		}
		for (auto v : g[u]) {
			if (v == p) continue;
			total += subt[v];
			total2 += gajos[v];
		}
		for (auto v : g[u]) {
			if (v == p) continue;
			self(self, v, u, total - subt[v], total2 - gajos[v]);
		}
	};
	auto dfs4 = [&] (auto&& self, int u, int p, int total) -> void {
		if (no_leaf[u]) ans += total;
		for (auto v : g[u]) {
			if (v == p) continue;
			self(self, v, u, total + (no_leaf[v] == 0));
		}
	};
	int root = 0;
	if (n == 2) {
		cout << 0 << endl;
		return;
	}
	for (int i = 0; i < n; ++i) if (sz(g[i]) != 1) root = i;
//	int real_ans = 0;
//	for (int i = 0; i < n; ++i) {
//		for (int j = 0; j < n; ++j) {
//			if (i == j) continue;
//			if (sz(g[i]) == 1 and sz(g[j]) > 1) real_ans++;
//		}
//	}
	dfs1(dfs1, root, root);
//	cout << "root: " << root << endl;
//	cout << "1: " << ans << ' ' << real_ans << endl;
	dfs2(dfs2, root, root);
//	for (int i = 0; i < n; ++i) {
//		for (int j = 0; j < n; ++j) {
//			if (i == j) continue;
//			int temp = i;
//			while (temp != root and temp != j) temp = par[temp];
//			if (temp == root) continue;
//			if (no_leaf[j] and no_leaf[par[i]] == 0 and sz(g[i]) > 1) real_ans++;
//		}
//	}
//	cout << "2: " << ans << ' ' << real_ans << endl;
	//cout << n << endl;
	//for (int i = 0; i < n; ++i) cout << no_leaf[i] << ' ' << subt[i] << endl;
	dfs3(dfs3, root, root, 0, 0);
	//for (int i = 0; i < n; ++i) {
	//	for (int j = 0; j < n; ++j) {
	//		if (i == j) continue;
	//		int temp = i;
	//		while (temp != root and temp != j) temp = par[temp];
	//		if (temp == j) continue;
	//		temp = j;
	//		while (temp != root and temp != i) temp = par[temp];
	//		if (temp == i) continue;
	//		if (no_leaf[j] and no_leaf[par[i]] == 0 and sz(g[i]) > 1) real_ans++;
	//	}
	//}
	//cout << "3: " << ans << ' ' << real_ans << endl;
	dfs4(dfs4, root, root, 0);
//	for (int i = 0; i < n; ++i) {
//		for (int j = 0; j < n; ++j) {
//			if (i == j) continue;
//			int temp = j, lst = j;
//			while (temp != root and temp != i) lst = temp, temp = par[temp];
//			if (temp != i) continue;
//			assert(par[lst] == i);
//			if (no_leaf[j] and no_leaf[temp] == 0 and sz(g[i]) > 1) real_ans++;
//		}
//	}
//	cout << "4: " <<  ans << ' ' << real_ans << endl;

	cout << ans << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
