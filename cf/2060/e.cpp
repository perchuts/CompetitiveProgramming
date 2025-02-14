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
	int n, m1, m2; cin >> n >> m1 >> m2;	
	vector<int> par(n), lvl(n), par2(n), lvl2(n);
	auto findp = [&] (auto&& self, int u) -> int {
		return par[u] = (par[u] == u ? u : self(self, par[u]));
	};
	auto unite = [&] (int u, int v) {
		u = findp(findp, u), v = findp(findp, v);
		if (u == v) return 0;
		if (lvl[u] < lvl[v]) swap(u, v);
		par[v] = u;
		if (lvl[u] == lvl[v]) lvl[u]++;
		return 1;
	};

	auto findp2 = [&] (auto&& self, int u) -> int{
		return par2[u] = (par2[u] == u ? u : self(self, par2[u]));
	};
	auto unite2 = [&] (int u, int v) {
		u = findp2(findp2, u), v = findp2(findp2, v);
		if (u == v) return 0;
		if (lvl2[u] < lvl2[v]) swap(u, v);
		par2[v] = u;
		if (lvl2[u] == lvl2[v]) lvl2[u]++;
		return 1;
	};
	vector<vector<int>> comps(n);
	vector<ii> edg(m1);
	for (auto& [x, y] : edg) cin >> x >> y, --x, --y;
	iota(all(par), 0);
	iota(all(par2), 0);
	for (int i = 0; i < m2; ++i) {
		int x, y; cin >> x >> y;
		--x, --y;
		unite(x, y);
	}
	int ans = 0;
	for (auto& [x, y] : edg) {
		if (findp(findp, x) == findp(findp, y)) unite2(x, y);
		else ans++;
	}
	for (int i = 0; i < n; ++i) comps[findp(findp, i)].pb(i);	
	for (int i = 0; i < n; ++i) for (auto x : comps[i]) ans += unite2(x, i);
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
