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

vector<int> solve(int n, vector<ii> edg){
	vector<vector<int>> g(n);
	for (auto [u, v] : edg) g[u].pb(v), g[v].pb(u);
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
	return p;
}

mt19937 rng(time(0));

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}
int32_t main(){_
	int tt = 0;
	while (true) {
		int n = rnd(2, 30);
		vector<ii> edg;
		vector<vector<int>> g(n);
		for (int i = 1; i < n; ++i) edg.pb({rnd(0, i-1), i});
		vector<int> rr(n); iota(all(rr), 0);
		shuffle(all(rr), rng);
		for (auto& [x, y] : edg) x = rr[x], y = rr[y], g[x].pb(y), g[y].pb(x);
		vector<vector<int>> paths;
		auto genpath = [&] (auto&& self, int u, vector<int> path) -> void {
			path.pb(u);
			paths.pb(path);
			for (auto v : g[u]) {
				if (sz(path) > 1 && end(path)[-2] == v) continue;
				self(self, v, path);
			}
		};
		auto p = solve(n, edg);
		for (int i = 0; i < n; ++i) genpath(genpath, i, vector<int>());
		for (auto path : paths) {
			vector<int> path_p;
			for (auto x : path) path_p.pb(p[x]);
			int m = sz(path);
			vector<int> occ(m, -1), ans(m);
			for (int i = 0; i < m; ++i) {
				for (int j = 0; j < m; ++j) {
					if (path_p[j] == path[i]) occ[i] = j;
				}
			}
			int best = 0;
			for (int i = 0; i < m; ++i) {
				if (occ[i] == -1) continue;
				ans[i] = 1;
				for (int j = 0; j < i; ++j) if (occ[j] < occ[i]) ckmax(ans[i], ans[j] + 1);
				ckmax(best, ans[i]);
			}
			cout << best << ' ';
			if (best > 1) {
				assert(m > 1);
				cout << "Wrong answer on test " << tt << endl;
				cout << n << endl;
				for (auto [x, y] : edg) cout << x + 1 << ' ' << y + 1 << endl;
				cout << "Your permutation: ";
				for (auto x : p) cout << x + 1 << ' ';
				cout << endl;
				cout << "Problematic pair: " << path[0] + 1 << ' ' << path.back() + 1 << endl;
				cout << "LCS found has size " << best << endl;
				exit(0);
			}
		}		
		cout << "Accepted on test " << ++tt << endl;
	}
}
