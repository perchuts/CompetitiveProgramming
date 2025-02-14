#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;

	int n, m;
	cin >> n >> m;

	int cnt = 0;

	vector<int> din(n);
	for (auto &x : din) {
		cin >> x;
		cnt += x;
	}

	if (cnt <= m) {
		cout << 0 << endl;
		return 0;
	}

	vector<vector<int>> g(n);
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		--a, --b;
		g[a].emplace_back(b);
		g[b].emplace_back(a);
	}

	int lo = 0, hi = n;
	while (lo < hi) {
		int mid = (lo + hi) / 2;

		//cout << "mid = " << mid << endl;
		int qt = 0;
		auto dfs = [&] (auto&& self, int u, int p) -> pair<int, int> {
			int bad = 0, good = n;

			for (int v : g[u]) if (v != p) {
				auto [a, b] = self(self, v, u);

				good = min(good, b);
			}

			for (auto a : g[u]) if (a != p) {
				if (good + a <= mid) continue; // coberto
				if (a != 0) bad = max(bad, a);
			}

			if (bad == mid) {
				qt++;
				//cout << "u = " << u+1 << endl;
				bad = 0;
				good = 1;
				return make_pair(bad, good);
			}

			if (bad) bad++;

			//cout << u+1 << " " << bad << " " << good << endl;

			if (din[u] && good > mid) bad = max(bad, 1ll);
			good = min(n, good + 1);

			return {bad, good};
		};
		auto [bad, good] = dfs(dfs, 0, 0);

		if (bad) qt++;

		if (qt <= m)
			hi = mid;
		else
			lo = mid + 1;
	}

	cout << lo << endl;

}

