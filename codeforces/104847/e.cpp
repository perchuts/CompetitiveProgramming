
#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const int maxn = 3e5 + 100;

vector<int> g[maxn];
set<pair<int, int>> ss[maxn];
pair<int, int> resp[maxn];
int tam[maxn], n, ans;

void dfs(int u) {
	tam[u] = 1;
	for (auto v : g[u]) {
		dfs(v);
		tam[u] += tam[v];
	}
	int big = -1;
	for (auto v : g[u]) {
		if (big == -1 || tam[v] > tam[big]) big = v;
	}
	if (big == -1) {
		ss[u].insert({u, u});
		// contendo segmento, nao contendo segmento
		resp[u] = {1, (n-u) * (n-u+1) / 2};
		return;
	}
	resp[u] = resp[big];
	swap(ss[u], ss[big]);
	auto [lb, rb] = *begin(ss[u]);
	assert(lb == big);
	resp[u].second += (big-u) * (big-u-1) / 2;
	int mistico = 0;
	auto add = [&] (int i) {
		auto nxt = ss[u].lower_bound(make_pair(i, i));
		if (nxt == end(ss[u])) {
			assert(nxt != begin(ss[u]));
			auto prv = prev(nxt);
			auto [lx, rx] = *prv;
			if (rx+1 == i) {
				resp[u].first += rx-lx+2;
				resp[u].second -= n-i+1;
				ss[u].erase(make_pair(lx, rx));
				ss[u].insert(make_pair(lx, rx+1));
			} else {
				resp[u].first++;
				resp[u].second -= (i-rx)*(n-i+1);
				ss[u].insert(make_pair(i, i));
			}
		} else {
			if (nxt == begin(ss[u])) {
				auto [lx, rx] = *nxt;
				if (lx-1 == i) {
					resp[u].first += rx-lx+2;
					resp[u].second -= i-u;
					ss[u].erase(make_pair(lx, rx));
					ss[u].insert(make_pair(lx-1, rx));
				} else {
					resp[u].first++;
					resp[u].second -= (i-u)*(lx-i);
					ss[u].insert(make_pair(i, i));
				}
			} else {
				auto prv = prev(nxt);
				auto [lx, rx] = *nxt;
				auto [lx2, rx2] = *prv;
				if (rx2+1 == i && i + 1 == lx) {
					resp[u].first += (i-lx2+1) * (rx-i+1);
					resp[u].second--;
					ss[u].erase(make_pair(lx2, rx2));
					ss[u].erase(make_pair(lx, rx));
					ss[u].insert(make_pair(lx2, rx));
				} else if (rx2+1 == i) {
					resp[u].first += (rx2-lx2+2);
					resp[u].second -= (lx-i);
					ss[u].erase(make_pair(lx2, rx2));
					ss[u].insert(make_pair(lx2, rx2+1));
				} else if (i + 1 == lx) {
					resp[u].first += (rx-lx+2);
					resp[u].second -= (i-rx2);
					ss[u].erase(make_pair(lx, rx));
					ss[u].insert(make_pair(lx-1, rx));
				} else {
					resp[u].first++;
					resp[u].second -= (i-rx2)*(lx-i);
					ss[u].insert(make_pair(i, i));
				}
			}
		}
	};
	for (auto v : g[u]) {
		mistico -= resp[v].first;
		if (v == big) continue;
		for (auto [l, r] : ss[v]) {
			for (int i = l; i <= r; ++i) add(i);	
		}
	}
	mistico -= resp[u].second;
	ans += (n-u) * (n-u + 1) / 2 + mistico;
	add(u);
}

void solve() {
 	 cin >> n;
	 for (int i = 2; i <= n; ++i) {
		int x; cin >> x;
		g[x].push_back(i);
	 }
	 for (int i = 1; i <= n; ++i) ans += i * (n-i+1);
	 dfs(1);
	 cout << ans << endl;
}
int32_t main() {
  fast_io;
  int t = 1;// cin >> t;
  while (t--) solve();
}

