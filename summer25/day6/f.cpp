#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;
	int n; cin >> n;
	vector<int> a(n), b(n), h(n);
	vector<int> par(n), lvl(n), repr(n);
	iota(begin(par), end(par), 0);
	iota(begin(repr), end(repr), 0);
	auto findp = [&] (auto&& self, int u) -> int {
		return par[u] = (par[u] == u ? u : self(self, par[u]));
	};
	auto unite = [&] (int u, int v) {
		u = findp(findp, u), v = findp(findp, v);
		if (u == v) return;
		if (lvl[u] < lvl[v]) swap(u, v);
		par[v] = u;
		if (lvl[u] == lvl[v]) lvl[u]++;
		repr[u] = min(repr[u], repr[v]);
	};
	for (auto& x : a) cin >> x;
	for (auto& x : b) cin >> x;
	set<pair<int, int>> s;
	int ans = 0, sum = 0, L = 0;
	for (int i = 0; i < n; ++i) {
		sum += a[i];
		if (a[i] > 0) s.insert({-a[i], i});
		if (a[i] < 0) L++;
		if (i and a[i] == 0) unite(i, b[i]);
		if (i) h[i] = h[b[i]] + 1;
	}
	if (sum < 0) {
		cout << -1 << endl;
		exit(0);
	}	
	auto operate = [&] (int i, int j) {
		s.erase({-a[i], i});
		if (a[j] < 0) {
			a[j] += a[i];	
			a[i] = 0;
			if (a[j] >= 0) {
				if (a[j] > 0) s.insert({-a[j], j});
				L--;
			}
			return;
		}
		if (a[j]) s.erase({-a[j], j});
		a[j] += a[i];
		s.insert({-a[j], j});
		a[i] = 0;
	};
	for (int __ = 0; __ < 3*n; ++__) {
		if (L == 0) { cout << ans << endl; return 0; }
		auto [x, y] = *begin(s);
		s.erase({x, y}), x *= -1;
		if (y == 0) { ans++, operate(0, b[0]); continue; }
		unite(y, b[y]);
		int ponta = repr[findp(findp, y)];
		ans += h[y] - h[ponta];
		operate(y, ponta);
	}
	cout << -1 << endl;
}
