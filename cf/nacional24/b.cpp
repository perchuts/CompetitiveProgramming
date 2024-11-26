#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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

}

int32_t main(){_
	while (true) {
		int n = rnd(5, 10), m = 0;
		vector<vector<int>> adj(n, vector<int>(n));
		vector<vector<int>> g(n);
		vector<int> deg(n);
		for (int i = 0; i < m ; ++i) {
			while (true) {
				int x = rnd(0, n-1), y = rnd(0, n-1);
				if (x == y or adj[x][y]) continue;
				adj[x][y] = adj[y][x] = 1;
				g[x].pb(y), g[y].pb(x);
				deg[x]++, deg[y]++;
				break;
			}
		}
		while (true) {
			bool ok = false;
			for (int i = 0; i < n; ++i) {
				if (deg[i] < 3) {
					ok = true;
					while (true) {
						int j = rnd(0, n-1);
						if (i == j or adj[i][j]) continue;
						adj[i][j] = adj[j][i] = 1;
						cout << i << ' ' << j << endl;
						m++;
						g[i].pb(j), g[j].pb(i);
						deg[i]++, deg[j]++;
						break;
					}
				}
			}
			if (ok == false) break;
		}
		int w = 0;
		vector<int> vis(n);
		auto dfs = [&] (auto&& self, int u, int p) -> void {
			vis[u] = 1;
			w++;
			for (auto v : g[u]) {
				if (vis[v]) continue;
				self(self, v, u);
				adj[u][v] = adj[v][u] = 0;
			}
		};
		dfs(dfs, 0, 0);
		if (w != n) {
			cout << "Test discarded because graph is not connected" << endl;
			continue;
		}
		for (int i = 0; i < n; ++i) g[i].clear(), vis[i] = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) if (adj[i][j]) g[i].pb(j);
		}
		bool ok = 0;
		auto find_cycle = [&] (auto&& self, int u, int p) -> void {
			vis[u] = 1;
			for (auto v : g[u]) {
				if (v == p) continue;
				if (vis[v]) {
					ok = 1;
				} else {
					self(self, v, u);
				}
			}
		};
		for (int i = 0; i < n; ++i) {
			if (!vis[i]) find_cycle(find_cycle, i, i);
		}
		if (ok) {
			cout << "cycle found: n = " << n << "; m = " << m << endl; 
		} else {
			cout << "cant find cycle in residual graph :(";
			cout << "n = " << n << "; m = " << m << endl;
			exit(0);
		}
	}
}
