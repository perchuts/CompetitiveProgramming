#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
using ord_set = tree<T, null_type, less<T>, rb_tree_tag,
	  tree_order_statistics_node_update>;

#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);


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
	vector<int> vals(n);
	for (int i = 0; i < n; ++i) {
		int x; cin >> x;
		if (i == 0) continue;
		--x;
		g[x].push_back(i);
	}
	for (auto& x : vals) cin >> x;
	vector<int> ans(n), subt(n);
	vector<ord_set<int>> sexo(n);
	auto dfs = [&] (auto&& self, int u, int p) -> void {
		subt[u] = 1;
		int big = -1, tam = 0;
		for (auto v : g[u]) {
			if (v == p) continue;
			self(self, v, u);
			subt[u] += subt[v];
			if (ckmax(tam, subt[v])) big = v;
		}
		
		if (big != -1) sexo[u].swap(sexo[big]);
		sexo[u].insert(vals[u]);
		for (auto v : g[u]) {
			if (v == p or v == big) continue;
			for (auto x : sexo[v]) sexo[u].insert(x);
		}
		int l = 1, r = n+1;
		while (l <= r) {
			int md = l + (r-l+1)/2;
			if (sexo[u].order_of_key(md) == md-1) l = md+1, ans[u] = md;
			else r = md-1;
		}
	};
	dfs(dfs, 0, 0);
	for (auto x : ans) cout << x << ' ';
	cout << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
