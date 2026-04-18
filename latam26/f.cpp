#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define endl '\n'
#define pb push_back

using namespace std;

using ll = long long;


int32_t main() {_
	int n; cin >> n;
	vector<int> a(n);
	for (auto& x : a) cin >> x;
	vector<vector<int>> v;
	int tot = 0;
	for (int i = 1; i <= 50; ++i) {
		v.pb({});
		for (int j = 0; j < i; ++j) {
			if (tot == n) break;
			v.back().pb(tot++);
		}
		if (tot == n) break;
	}
	int layers = v.size(), ans = 1;
	for (int i = 0; i < (1 << layers); ++i) {
		vector<int> par(n), lvl(n, 1);
		auto findp = [&] (auto&& self, int x) -> int {
			return par[x] = (par[x] == x ? x : self(self, par[x]));
		};
		auto merge = [&] (int u, int v) {
			u = findp(findp, u), v = findp(findp, v);
			if (u == v) return;
			if (lvl[u] < lvl[v]) swap(u, v);
			par[v] = u;
			lvl[u] += lvl[v];
			ans = max(ans, lvl[u]);
		};
		vector<vector<int>> dir(2, {0});
		iota(begin(par), end(par), 0);
		for (int j = 1; j < layers; ++j) {
			int z = (i >> j & 1);
			for (int k = 0; k < v[j].size(); ++k) {
				if (k != 0 and a[dir[z][k-1]] == a[v[j][k]]) merge(dir[z][k-1], v[j][k]);
				if (k != 0 and a[v[j][k]] == a[v[j][k-1]]) merge(v[j][k], v[j][k-1]);
				if (k < dir[z].size() and a[dir[z][k]] == a[v[j][k]]) merge(dir[z][k], v[j][k]);
			}
			dir[z] = v[j];
			dir[z^1].push_back(v[j].back());
		}
	}
	cout << ans << endl;
}
