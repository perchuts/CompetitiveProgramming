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

void solve(){
 	int n; cin >> n;
	vector<vector<int>> g(n);
	for (int i = 0; i < n - 1; ++i) {
		int u, v; cin >> u >> v; --u, --v;
		g[u].pb(v), g[v].pb(u);
	}
	vector<int> subt(n);
	auto pre = [&] (auto&& self, int u, int p) -> void {
		subt[u] = 1;
		for (auto v : g[u]) {
			if (v == p) continue;
			self(self, v, u);
			subt[u] += subt[v];
		}
	};
	pre(pre, 0, 0);
	auto find_centroid = [&] (auto&& self, int u, int p) -> int {
		for (auto v : g[u]) {
			if (v != p && 2 * subt[v] > n) return self(self, v, u);
		}	
		return u;
	};
	int c = find_centroid(find_centroid, 0, 0);
	vector<vector<int>> orders;
	vector<int> vis(n);
	vis[c] = 1;
	auto bfs = [&] (int u) {
		queue<int> q;
		q.push(u);
		vis[u] = 1;
		vector<int> order;
		while (!q.empty()) {
			int w = q.front(); q.pop();
			order.pb(w);
			for (auto v : g[w]) {
				if (!vis[v]) {
					vis[v] = 1;
					q.push(v);
				}
			}
		}
		orders.pb(order);
	};
	vector<int> p(n);
	for (auto v : g[c]) bfs(v);
	p[c] = c;
	int m = sz(orders), big = 0;
	vector<int> ptr(m);
	priority_queue<ii> pq;
	for (int i = 0; i < m; ++i) {
		if (sz(orders[i]) > sz(orders[big])) big = i; 
	}
	for (int i = 0; i < m; ++i) {
		if (n&1) pq.push({sz(orders[i]), i});
		else {
			if (i == big) {
				if (sz(orders[i]) > 1) pq.push({sz(orders[i])-1, i});
				ptr[i] = 1, p[orders[i][0]] = c, p[c] = orders[i][0];
			}
			else pq.push({sz(orders[i]), i});
		}
	}
	while (!pq.empty()) {
		auto [s1, x1] = pq.top(); pq.pop();
		assert(!pq.empty());
		auto [s2, x2] = pq.top(); pq.pop();
		int u = orders[x1][ptr[x1]++], v = orders[x2][ptr[x2]++];
		p[u] = v, p[v] = u;
		s1--, s2--;
		if (s1) pq.push({s1, x1});
		if (s2) pq.push({s2, x2});
	}
	for (auto x : p) cout << x + 1 << ' ';
	cout << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
