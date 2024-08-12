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
vector<int> g[maxn];
int subt[maxn];
int dfs(int u, int p = 1) {
	subt[u] = 1;
	for (auto v : g[u]) {
		if (v == p) continue;
		subt[u] += dfs(v, u);
	}
	return subt[u];
}
int find_centroid(int u, int p = 1) {
	for (auto v : g[u]) {
		if (v != p && 2 * subt[v] > subt[1]) return find_centroid(v, u);
	}
	return u;
}
vector<int> order;
void solve(int u, int p) {
	order.pb(u);
	for (auto v : g[u]) {
		if (v == p) continue;
		solve(v, u);
	}
}
void solve() {
	int n; cin >> n;
	for (int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	dfs(1);
	int c = find_centroid(1);
	solve(c, c);
	for (int i = (n%2==1); i < (n+1) / 2; ++i) {
		cout << order[i] << ' ' << order[i + n / 2] << endl;
	}
}

int32_t main() {_
	int t = 1; //cin >> t;
	while(t--) solve();
}
