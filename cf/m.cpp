#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;
using ii = pair<int, int>;

const int mod = (119<<23)+1;

int32_t main() {
	fast_io;
	int n, m, k; cin >> n >> m >> k;
	vector<ii> edg(m);
	vector<int> par(n), lvl(n); iota(begin(par), end(par), 0);
	auto findp = [&] (auto&& self, int u) -> int {
		return par[u] = (par[u] == u ? u : self(self, par[u]));
	};
	auto unite = [&] (int u, int v) {
		u = findp(findp, u), v = findp(findp, v);
		if (u == v) return;
		if (lvl[u] > lvl[v]) swap(u, v);
		par[v] = u;
		lvl[u] += (lvl[u] == lvl[v]);
	};
	for (auto& [x, y] : edg) cin >> x >> y, --x, --y, unite(x, y);
	if (findp(findp, 0) != findp(findp, 1)) {
		cout << 0 << endl;
		exit(0);
	}
	vector<int> sdp(n, 0), dp(n), tem(n);
	sdp[0] = tem[0] = 1;
	auto add = [&] (int& x, int y) {
		x += y;
		if (x >= mod) x -= mod;
	};
	for (int step = 0; ; ++step) {
		dp = sdp;
		vector<int> nsdp(n, 0);
		for (int j = 1; j <= k; ++j) {
			vector<int> ndp(n, 0), ntem = tem;
			for (auto [u, v] : edg) {
				ntem[u] |= tem[v];
				ntem[v] |= tem[u];
				add(ndp[u], dp[v]);
				add(ndp[v], dp[u]);
			}
			for (int w = 0; w < n; ++w) add(nsdp[w], ndp[w]);
			swap(dp, ndp);
			swap(tem, ntem);
		}
		swap(nsdp, sdp);
		if (tem[1] == 1) {
			cout << sdp[1] << endl;
			exit(0);
		}
	}
}
