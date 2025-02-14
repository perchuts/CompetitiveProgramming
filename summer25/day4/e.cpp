#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io
	int m; cin >> m;
	int n; cin >> n;

	vector<int> a(n);
	for (auto &i : a) cin >> i, --i;

	vector<vector<int>> ids(m);
	for (int i = 0; i < n; i++) {
		ids[a[i]].push_back(i);
	}

	vector<int> b(m);
	for (auto &i : b) cin >> i;

	int q; cin >> q;
	vector<tuple<int, int, int>> upds(q);
	for (auto &[l, r, k] : upds) {
		cin >> l >> r >> k;
		--l, --r;
	}

	vector<int> bit(n+1, 0);
	auto insert = [&] (int x, int z) {
		if (x == -1) return;
		x++;
		while (x <= n) {
			bit[x] = bit[x] + z, x += x & (-x);
		}
	};
	auto query = [&] (int x) {
		x++;
		int ans = 0;
		while (x) {
			ans = ans + bit[x];
			x -= x & (-x);
		}
		return ans;
	};
	auto upd = [&] (int l, int r, int v) {
		insert(l, v);
		insert(r + 1, -v);
	};

	vector<int> l(m, 1), r(m, q + 1);
	while (true) {
		bool some = false;
		vector<vector<int>> who(q + 1);
		for (int i = 0; i < m; i++) {
			if (l[i] >= r[i]) continue;
			int mid = (l[i] + r[i]) / 2;
			if (mid == q + 1) r[i] = mid;
			else {
				some = true;
				who[mid].push_back(i);
			}
		}

		if (!some) break;

		fill(bit.begin(), bit.end(), 0);
		for (int i = 0; i < q; i++) {
			auto [l1, r1, k] = upds[i];
			if (l1 <= r1) upd(l1, r1, k);
			else {
				upd(0, r1, k);
				upd(l1, n - 1, k);
			}
			for (auto j : who[i + 1]) {
				int tot = 0;
				for (int pos : ids[j]) {
					tot += query(pos);
					if (tot >= b[j]) break;
				}

				if (tot >= b[j])
					r[j] = i + 1;
				else
					l[j] = i + 2;
			}
		}
	}

	for (int j = 0; j < m; j++) {
		if (l[j] <= q) cout << l[j] << endl;
		else cout << "NIE" << endl;
	}

}

