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
 	int n, q; cin >> n >> q;
	vector<int> pai(n+1), p(n+1);
	vector<ii> euler(n+1);
	vector<vector<int>> g(n+1);
	for (int i = 2; i <= n; ++i) cin >> pai[i], g[pai[i]].pb(i);
	int t = 0;
	auto dfs = [&] (auto&& self, int u) -> void {
		euler[u].first = ++t;
		for (auto v : g[u]) self(self, v);
		euler[u].second = t;
	};
	dfs(dfs, 1);
	for (int i = 1; i <= n; ++i) cin >> p[i];
	int score2 = 0;
	auto is_ancestor = [&] (int u, int v) {
		return (euler[v].first <= euler[u].first && euler[u].first <= euler[v].second);
	};
	auto recompute = [&] (int i, int flag) {
		if (i == 0) return;
		if (i != n) score2 += flag * is_ancestor(p[i], pai[p[i+1]]);
	};
	for (int i = 1; i <= n; ++i) recompute(i, 1);
	while (q--) {
		int x, y; cin >> x >> y;
		if (x > y) swap(x, y);
		recompute(x, -1), recompute(y, -1), recompute(x-1, -1);
		if (x != y-1) recompute(y-1, -1);
		swap(p[x], p[y]);
		recompute(x, 1), recompute(y, 1), recompute(x-1, 1);
		if (x != y-1) recompute(y-1, 1);
		cout << (score2 == n-1 ? "Yes" : "No") << endl;
	}
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
