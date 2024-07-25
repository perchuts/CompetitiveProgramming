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
const int maxn = 1e6+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

vector<int> g[maxn], gr[maxn];
void solve(){
	int n, m; cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int u, v; cin >> u >> v; --u, --v;
		g[u].pb(v);
		gr[v].pb(u);
	}
	function<vector<int>(int)> bfs = [&] (int src) {
		vector<int> vis(n);
		vis[src] = 1;
		queue<int> q;
		q.push(src);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			if (src) {
				for (auto v : gr[u]) {
					if (!vis[v]) vis[v] = 1, q.push(v);
				}
			} else {
				for (auto v : g[u]) {
					if (!vis[v]) vis[v] = 1, q.push(v);
				}
			}
		}
		return vis;
	};
	auto v1 = bfs(0);
	auto vn = bfs(n-1);
	vector<int> exist(n);
	int nn = 0, mm = 0;
	for (int u = 0; u < n; ++u) {
		for (auto v : g[u]) {
			if (v1[u] && vn[v]) {
				exist[u] = exist[v] = 1;
				mm++;
			}
		}
	}
	for (int i = 0; i < n; ++i) nn += exist[i];
	if (nn == 0) cout << 0 << endl;
	else cout << mm - nn + 2 << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
