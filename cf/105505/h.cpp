#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
	int n; cin >> n;
	vector<int> b(n), deg(n), answer(n), flag(n);
	vector<vector<int>> c(n, vector<int>(n)), g(n), gr(n);
	queue<int> q;
	for (auto& x : b) cin >> x;
	int m; cin >> m;
	for (int i = 0; i < m; ++i) {
		int u, v; cin >> u >> v;
		--u, --v;
		g[u].pb(v), gr[v].pb(u);
		deg[u]++;
	}
	int Q; cin >> Q;
	vector<ii> queries(Q);
	// quero fazer as queries em porcoes de tamanho 1000
	const int block = sqrt(n+m);
	for (auto& [x, y] : queries) {
		char op; cin >> op;
		if (op == 'U') cin >> x >> y;
		else cin >> x, y = -1;
		--x;
	}
	ll tot = 0, id = 0;
	for (int i = 0; i < n; ++i) if (deg[i] == 0) q.push(i);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		c[u][u] = 1;
		for (auto v : gr[u]) {
			deg[v]--;
			for (int j = 0; j < n; ++j) {
				c[v][j] += c[u][j];
				if (c[v][j] >= mod) c[v][j] -= mod;
			}
			if (deg[v] == 0) q.push(v);
		}
	}
	for (int i = 0; i * block < Q; ++i) {
		vector<int> active;
		for (int j = 0; j < n; ++j) {
			deg[j] = sz(g[j]), answer[j] = flag[j] = 0;
			if (deg[j] == 0) q.push(j);
		}
		while (!q.empty()) {
			int u = q.front(); q.pop();
			answer[u] += b[u];
			if (answer[u] >= mod) answer[u] -= mod;
			for (auto v : gr[u]) {
				deg[v]--;
				if (deg[v] == 0) q.push(v);
				answer[v] += answer[u];
				if (answer[v] >= mod) answer[v] -= mod;
			}
		}
		for (int j = i * block; j < min(Q, (i+1)*block); ++j) {
			auto [u, val] = queries[j];
			if (flag[u] == 0 and val == -1) flag[u] = 1, active.pb(u);
		}
		for (int j = i * block; j < min(Q, (i+1)*block); ++j) {
			auto [u, val] = queries[j];
			if (val == -1) {
				tot = (tot + ll(answer[u]) * (++id)) % mod;
				continue;
			}
			for (auto x : active) {
				ll K = ll(c[x][u]) * ll(val-b[u]+mod) % mod; 
				answer[x] += K;
				if (answer[x] >= mod) answer[x] -= mod;
			}
			b[u] = val;
		}
	}
	cout << tot << endl;
}
int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
