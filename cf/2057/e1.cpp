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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

void solve(){
	int n, m, q; cin >> n >> m >> q;
	vector<vector<ii>> g(n);
	vector<iii> edg(m);
	for (auto& [w, u, v] : edg) {
		cin >> u >> v >> w;
		--u, --v;
		g[u].pb({v, w});
		g[v].pb({u, w});
	}
	while (q--) {
		int u, v, k; cin >> u >> v >> k;
		--u, --v;
		int l = 0, r = 1e9, ans = 1e9;
		auto possible = [&] (int md) {
			deque<int> qq;
			qq.pb(u);
			vector<int> dist(n+1, inf), vis(n+1);
			dist[u] = 0;
			while (!qq.empty()) {
				auto w = qq.front(); qq.pop_front();
				if (vis[w]) continue;
				vis[w] = 1;
				for (auto [z, x] : g[w]) {
					if (x > md && ckmin(dist[z], dist[w]+1)) qq.pb(z);
					if (x <= md && ckmin(dist[z], dist[w])) qq.push_front(z);
				}
			}
			return (dist[v] < k);
		};
		while (l <= r) {
			int md = l + (r-l+1)/2;
			if (possible(md)) ans = md, r = md-1;
			else l = md+1;
		}
		cout << ans << ' ';
	}
	cout << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
