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
vector<ii> g[maxn];
void solve() {
	int n, m; cin >> n >> m;
	vector<int> val(n);
	for (auto& x : val) cin >> x;
	for (int i = 0; i < m; ++i) {
		int u, v, w; cin >> u >> v >> w;
		--u, --v;
		g[u].pb({v, val[v] + w});
		g[v].pb({u, val[u] + w});
	}
	vector<int> dist(n, 1e18);
	priority_queue<ii, vector<ii>, greater<ii>> pq;
	dist[0] = val[0];
	pq.push({val[0], 0});
	while (!pq.empty()) {
		auto [d, u] = pq.top(); pq.pop();
		if (d != dist[u]) continue;
		for (auto [v, w] : g[u]) {
			if (ckmin(dist[v], dist[u] + w)) {
				pq.push({dist[v], v});
			}
		}
	}
	for (int i = 1; i < n; ++i) cout << dist[i] << ' ';
}

int32_t main() {_
	int t = 1; //cin >> t;
	while(t--) solve();
}
