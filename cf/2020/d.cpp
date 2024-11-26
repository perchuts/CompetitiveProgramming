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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

void solve(){
	int n, m; cin >> n >> m;
	// vou ter 1, 2, 3, ... 10 caras
	vector<vector<iii>> upd(11);
	for (int i = 0; i < m; ++i) {
		int a, d, k; cin >> a >> d >> k;
		--a;
		int version = a % d, l = a / d, r = l + k;
		upd[d].pb({version, l, r});
	}
	vector<int> p(n), lvl(n);
	for (int i = 0; i < n; ++i) p[i] = i;
	auto findp = [&] (auto&& self, int u) -> int {
		return p[u] = (p[u] == u ? u : self(self, p[u]));
	};
	auto merge = [&] (int u, int v) {
		u = findp(findp, u), v = findp(findp, v);
		if (u == v) return;
		if (lvl[u] < lvl[v]) swap(u, v);
		p[v] = u;
		if (lvl[u] == lvl[v]) lvl[u]++;
	};
	vector<vector<ii>> versions(10);
	for (int d = 1; d <= 10; ++d) {
		for (int i = 0; i < d; ++i) versions[i].clear();
		for (auto [a, b, c] : upd[d]) versions[a].pb({c, b});
		for (int i = 0; i < d; ++i) {
			vector<ii> segments;
			sort(all(versions[i]));
			for (auto [r, l] : versions[i]) {
				int mn = l;
				while (!segments.empty() and l <= segments.back().second) ckmin(mn, segments.back().first), segments.pop_back();
				segments.pb({mn, r});
			}
			for (auto [l, r] : segments) {
				for (int j = l; j < r; ++j) {
					merge(i + j * d, i + (j+1) * d);
				}
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < n; ++i) if (findp(findp, i) == i) ans++;
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
