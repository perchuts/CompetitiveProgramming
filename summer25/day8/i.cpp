#include <bits/stdc++.h>
using namespace std;

#define BRUTE

using T = __int128_t;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

struct dsu {
	int n;
	vector<int> p, sz;
	dsu(int _n) : n(_n), p(n), sz(n, 1) {
		iota(p.begin(), p.end(), 0);
	}
	void clear() {
		iota(p.begin(), p.end(), 0);
		sz.assign(n, 1);
	}
	int find(int x) {
		if (x == p[x]) return x;
		return p[x] = find(p[x]);
	}
	bool unite(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (sz[a] < sz[b]) swap(a, b);
		p[b] = a;
		sz[a] += sz[b];
		return true;
	}
};

int aliens(int n, int m, int k, vector<tuple<int, int, int>>& edg) {
	vector<tuple<int, int, int, int>> edges;
	for (auto &[w, a, b] : edg) {
		bool sp = (a == 0 || b == 0);
		edges.emplace_back(w, sp, a, b);
	}

	vector<vector<int>> g(n);
	for (auto [_, a, b] : edg) {
		g[a].emplace_back(b);
		g[b].emplace_back(a);
	}
	
	int cc = 0;
	vector<int> vis(n, false);
	auto dfs = [&] (auto&& self, int u) -> void {
		if (u == 0) return;
		vis[u] = true;
		for (int v : g[u]) {
			if (!vis[v]) self(self, v);
		}
	};
	for (int i = 1; i < n; i++) {
		if (!vis[i]) cc++, dfs(dfs, i);
	}

	if (k < cc) {
		return -1;
	}

	dsu d(n);
	auto check = [&] (int val) -> pair<T, int> {
		auto st = edges;
		for (auto &[w, sp, a, b] : st) {
			if (sp) w += val;
		}

		d.clear();
		sort(st.begin(), st.end());
		T ans = 0;
		int used = 0;
		for (auto &[w, sp, a, b] : st) {
			if (d.unite(a, b)) {
				used += sp;
				ans += w;
			}
		}

		return pair(ans, used);
	};

	int lo = -2e15, hi = 2e15;
	while (lo < hi) {
		int mid = lo + (hi - lo) / 2;

		//cout << lo << " " << hi << " ";
		//cout << check(lo).second << " " << check(hi).second << endl; cout.flush();

		auto [cost, used] = check(mid);
		if (used <= k)
			hi = mid;
		else
			lo = mid + 1;
	}

	auto [cost, used] = check(lo);
	//cout << "lo=" << (long long)lo << " ";
	//cout << (int)cost << " " << used << endl;

	return cost - k * lo;
}

vector<int> brute(int n, int m, vector<tuple<int, int, int>>& edg) {
	vector<vector<pair<int, int>>> g(n);
	for (auto [w, a, b] : edg) {
		g[a].emplace_back(b, w);
		g[b].emplace_back(a, w);
	}
	int sz = g[0].size();
	sort(edg.begin(), edg.end());
	vector<int> ans(sz + 1, 1e18);
	for (int mask = 0; mask < (1 << sz); mask++) {
		dsu d(n);
		int cost = 0;
		int pc = 0;

		int comps = n;
		for (int j = 0; j < sz; j++) {
			if (mask >> j & 1) {
				pc++;
				auto [to, w] = g[0][j];
				if (d.unite(0, to)) {
					comps--;
					cost += w;
				}
			}
		}
		for (auto [w, a, b] : edg) {
			if (a == 0 || b == 0) continue;
			if (d.unite(a, b)) {
				cost += w;
				comps--;
			}
		}
		if (comps == 1)
			ans[pc] = min(ans[pc], cost);
	}

	bool ok = true;
	for (int i = 2; i < ans.size(); i++) {
		ok &= ans[i - 1] == 1e18 || ans[i] - ans[i - 1] >= ans[i - 1] - ans[i - 2];
	}
	return ans;
}

int32_t main() {

#ifdef BRUTE
	for (int seed = 1; ; seed++) {
		srand(seed);

		int n = 400, m = 2000;
		set<pair<int, int>> st;
		vector<tuple<int, int, int>> edg;
		int deg0 = 0;

		dsu d(n);
		int comps = n;
		do {
			comps = n;
			d = dsu(n);
			do {
				int a = rand() % n;
				int b = rand() % n;
				if (a == b) continue;
				if (st.count({a, b}) || st.count({b, a})) continue;

				int c = rand() % 10;
				edg.emplace_back(c, a, b);
				st.emplace(a, b);
				deg0 += a == 0 || b == 0;
				if (d.unite(a, b)) {
					comps--;
				}
			} while (st.size() < m);
		} while (comps != 1);

		if (deg0 > 10) continue;

		cout << n << " " << m << endl;
		for (auto [w, a, b] : edg) {
			cout << a + 1 << " " << b + 1 << " " << w << endl;
		}

		auto ans = brute(n, m, edg);
		//for (int k = 1; k <= deg0; k++) {
		//	cout << k << endl; cout.flush();
		//	assert(ans[k] == aliens(n, m, k, edg));
		//}
		bool ok = true;
		for (int i = 2; i < ans.size(); i++) {
			ok &= ans[i - 1] == 1e18 || ans[i] - ans[i - 1] >= ans[i - 1] - ans[i - 2];
		}
		assert(ok);
		cout << seed << endl; cout.flush();
	}
#else
	fast_io;

	int n, m, k;
	cin >> n >> m >> k;
	vector<tuple<int, int, int>> edges(m);
	for (auto &[w, a, b] : edges) {
		cin >> a >> b >> w;
		--a, --b;
	}
	cout << aliens(n, m, k, edges) << endl;

	auto ans = brute(n, m, edges);
	for (int i = 1; i < ans.size(); i++)
		cout << ans[i] << " ";
	cout << endl;

#endif
}
