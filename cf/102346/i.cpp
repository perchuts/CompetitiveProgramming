#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
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

const int inf = 2e8+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

vector<pair<int, int>> g[maxn];

int dist[401][401];

int min_edg[401][401];

vector<iii> queries[405][2];

void solve(){
	int n, r; cin >> n >> r;
	vector<int> temp(n), ord(n);
	for (auto& x : temp) cin >> x;
	iota(all(ord), 0);
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) min_edg[i][j] = inf;
	sort(all(ord), [&] (int u, int v) { return temp[u] < temp[v]; });
	vector<int> tt = temp;
	sort(all(tt)); tt.erase(unique(all(tt)), end(tt));
	for (int i = 1; i <= r; ++i) {
		int u, v, d; cin >> u >> v >> d;
		--u, --v;
		ckmin(min_edg[u][v], d), min_edg[v][u] = min_edg[u][v];
		g[u].pb({v, d});
		g[v].pb({u, d});
	}
	int q; cin >> q;
	vector<int> ans(q);
	for (int i = 0; i < q; ++i) {
		int a, b, k, t; cin >> a >> b >> k >> t;
		--a, --b;
		queries[k][t].pb({a, b, i});
	}
	for (int w = 0; w < 2; ++w) {
		for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) dist[i][j] = (i == j ? 0 : min_edg[i][j]);	
		int ptr = 0;
		vector<int> exist(n);
		for (int k = 1; k <= n; ++k) {
			// update guys
			while (ptr != n && (k > sz(tt) || tt[k-1] >= temp[ord[ptr]])) {
				int u = ord[ptr];
				exist[u] = 1, ptr++;
				for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) ckmin(dist[i][j], dist[i][u] + dist[u][j]);
			}
			for (auto [a, b, id] : queries[k][w]) ans[id] = (dist[a][b] == inf ? -1 : dist[a][b]);
		}
		reverse(all(ord));
		reverse(all(tt));
		for (auto& x : tt) x *= -1;
		for (auto& x : temp) x *= -1;
	}
	for (auto x : ans) cout << x << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
