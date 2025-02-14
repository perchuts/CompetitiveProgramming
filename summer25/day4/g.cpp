#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;
	
	int n, q;
	cin >> n >> q;

	vector<int> a(n), b(n);
	for (int i = 1; i < n; i++) {
		char x; cin >> x;
		a[i] = x - '0';
	}
	for (int i = 1; i < n; i++) {
		char x; cin >> x;
		b[i] = x - '0';
	}
	vector<int> nine(4*n + 10), carry(4*n + 10);

	auto merge = [&] (int x) {
		int l = 2*x, r = 2*x + 1;

		nine[x] = nine[l] && nine[r];
		carry[x] = carry[l] || (nine[l] && carry[r]);
	};

	auto build = [&] (auto&& self, int x, int lx, int rx) {
		if (lx + 1 == rx) {
			nine[x] = (a[lx] + b[lx] == 9);
			carry[x] = (a[lx] + b[lx] > 9);
			return;
		}

		int m = (lx + rx) / 2;
		self(self, 2*x, lx, m);
		self(self, 2*x + 1, m, rx);
		merge(x);
	};
	build(build, 1, 0, n);

	auto upd = [&] (auto&& self, int i, int w, int v, int x, int lx, int rx) {
		if (lx + 1 == rx) {
			if (!w) a[lx] = v;
			else b[lx] = v;

			nine[x] = (a[lx] + b[lx] == 9);
			carry[x] = (a[lx] + b[lx] > 9);
			return;
		}

		int m = (lx + rx) / 2;
		if (i < m)
			self(self, i, w, v, 2*x, lx, m);
		else self(self, i, w, v, 2*x + 1, m, rx);

		merge(x);
	};
	build(build, 1, 0, n);

	auto query = [&] (auto&& self, int i, int c, int x, int lx, int rx) {
		if (lx + 1 == rx) {
			return (a[i] + b[i] + c) % 10;
		}

		int m = (lx + rx) / 2;
		if (i < m) {
			int nc = carry[2*x + 1] || (c && nine[2*x + 1]);
			return self(self, i, nc, 2*x, lx, m);
		} else {
			return self(self, i, c, 2*x + 1, m, rx);
		}
	};

	while (q--) {
		char t; cin >> t;
		if (t == 'S') {
			int i; cin >> i;
			i = n-i;

			cout << query(query, i, 0, 1, 0, n) << endl;
		} else {
			int i, x;
			cin >> i >> x;
			i = n-i;

			if (t == 'W') upd(upd, i, 0, x, 1, 0, n);
			else upd(upd, i, 1, x, 1, 0, n);
		}
	}

	



}
