#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;
	int n, k, q; cin >> n >> k >> q;
	vector<int> p(n), h(n), coeff(n);
	vector<vector<int>> g(n);
	for (int i = 1; i < n; ++i) cin >> p[i], --p[i], g[p[i]].push_back(i);
	auto dfs = [&] (auto&& self, int u) -> void {
		int x = h[u]+k-1, y = k-1;
		if ((x|y) != x) coeff[u] = 0;
		else coeff[u] = 1;
		for (auto v : g[u]) {
			h[v] = h[u]+1;
			self(self, v);
		}
	};
	dfs(dfs, 0);
	while (q--) {
		int ans = 0;
		for (int i = 0; i < n; ++i) {
			int x; cin >> x;
			ans = (ans + x * coeff[i]) % 2;
		}
		cout << ans << endl;
	}
}
