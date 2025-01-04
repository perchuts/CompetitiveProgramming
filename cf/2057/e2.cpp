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
	int n, m, q; cin >> n >> m >> q;

	vector<vector<ii>> g(n);
	vector<iii> edg(m);
	vector<int> par(n), lvl(n, 1);
	vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n+1, 1e9)));
	vector<vector<int>> tempdp(n, vector<int>(n, n));
	iota(all(par), 0);

	for (int i = 0; i < n; ++i) tempdp[i][i] = 0;
	for (auto& [w, u, v] : edg) {
		cin >> u >> v >> w;
		--u, --v;
		tempdp[u][v] = tempdp[v][u] = 1;
		g[u].pb({v, w});
		g[v].pb({u, w});
	}

	sort(all(edg)); 

	for (int k = 0; k < n; ++k) for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) ckmin(tempdp[i][j], tempdp[i][k] + tempdp[k][j]);

	auto findp = [&] (auto&& self, int u) -> int { return par[u] = (u == par[u] ? u : self(self, par[u])); };

	auto redo = [&] (int u, int w) {
		deque<int> dq;
		vector<int> dist(n, n+1);
		dq.pb(u);
		dist[u] = 0;
		while (!dq.empty()) {
			auto x = dq.front(); dq.pop_front();
			for (auto [y, ww] : g[x]) {
				if (ww <= w and ckmin(dist[y], dist[x])) dq.push_front(y);
				if (ww > w and ckmin(dist[y], dist[x]+1)) dq.pb(y);
			}
		}
		for (int i = 0; i < n; ++i) tempdp[u][i] = dist[i];
		for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) ckmin(tempdp[i][j], tempdp[u][i] + tempdp[u][j]); 
		for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
			ckmin(dp[i][j][tempdp[i][j]], w);
		}
	};

	auto unite = [&] (int u, int v, int w) {
		int pu = findp(findp, u), pv = findp(findp, v);
		if (pu == pv) return;
		redo(pu, w); 
		if (lvl[pu] < lvl[pv]) swap(pu, pv);
		par[pv] = pu, lvl[pu] += lvl[pv];
	};

	for (auto [w, u, v] : edg) unite(u, v, w);

	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) for (int k = 1; k < n; ++k) ckmin(dp[i][j][k], dp[i][j][k-1]);

	while (q--) {
		int u, v, k; cin >> u >> v >> k;
		--u, --v;
		cout << dp[u][v][k-1] << ' ';
	}
	cout << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
