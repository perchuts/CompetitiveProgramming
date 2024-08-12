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

void solve(){
	int n, m, k; cin >> n >> m >> k;
	for (int i = 0; i < m; ++i) {
		int u, v; cin >> u >> v;
		--u, --v;
		g[u].pb(v), g[v].pb(u);
	}
	vector<int> a(n), b(k);
	for (auto& x : a) cin >> x, --x;
	for (auto& x : b) cin >> x, --x;
	vector<int> dist(n, inf), foi(n, 0);
	deque<int> dq;
	dq.pb(0);
	dist[0] = (b[0] == a[0]);
	while (!dq.empty()) {
		int u = dq.front(); dq.pop_front();
		if (foi[u] || dist[u] == k) continue;	
		foi[u] = 1;
		for (auto v : g[u]) {
			int ndist = dist[u] + (a[v] == b[dist[u]]);
			if (ckmin(dist[v], ndist)) {
				if (ndist == dist[u] + 1) dq.push_back(v);
				else dq.push_front(v);
			}
		}
	}
	cout << (dist.back() < k ? "No" : "Yes") << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
