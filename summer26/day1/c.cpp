#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back

using ll = long long;
using namespace std;

int32_t main() {_
	int n, m, k; cin >> n >> m >> k;
	vector<int> par(n), comp(n), lvl(n);
	iota(begin(par), end(par), 0);
	for (int i = 0; i < k; ++i) {
		int x; cin >> x; --x;
		comp[x] = 1;
	}
	auto findp = [&] (auto&& self, int u) -> int {
		return par[u] = (par[u] == u ? u : self(self, par[u]));
	};
	int ans = 0;
	auto unite = [&] (int u, int v) {
		u = findp(findp, u), v = findp(findp, v);
		if (u == v) return;
		if (lvl[u] < lvl[v]) swap(u, v);
		if (lvl[u] == lvl[v]) lvl[u]++;
		par[v] = u;
		ans += comp[u] * comp[v];
		comp[u] += comp[v];
	};
	vector<tuple<int, int, int>> edg(m);
	for (auto& [w, u, v] : edg) cin >> u >> v >> w, --u, --v;
	int q; cin >> q;
	for (int i = 0; i < q; ++i) {
		int x; cin >> x;
		edg.push_back({x, -1, i});
	}
	vector<int> resp(q);
	sort(rbegin(edg), rend(edg));
	for (auto [w, u, v] : edg) {
		if (u < 0) {
			resp[v] = ans;
		} else {
			unite(u, v);
		}
	}
	for (auto x : resp) cout << x << " ";
	cout << endl;
}
