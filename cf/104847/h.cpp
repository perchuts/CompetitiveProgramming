
#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

struct Seg {
	int n;
	vector<int> tree;

	Seg(int _n=0) : n(_n), tree(4*n + 10) {}

	void update(int i, int v, int x, int lx, int rx) {
		if (lx + 1 == rx) {
			tree[x] = v;
			return;
		}
		int mid = (lx + rx) / 2;
		if (i < mid)
			update(i, v, 2*x, lx, mid);
		else
			update(i, v, 2*x + 1, mid, rx);
		tree[x] = tree[2*x] + tree[2*x + 1];
	}

	int query(int l, int r, int x, int lx, int rx) {
		if (lx >= l && rx <= r) {
			return tree[x];
		}
		if (lx >= r || rx <= l) {
			return 0;
		}
		int mid = (lx + rx) / 2;
		int ql = query(l, r, 2*x, lx, mid);
		int qr = query(l, r, 2*x+1, mid, rx);
		return ql + qr;
	}

	int first(int x, int lx, int rx, int qt) {
		if (lx + 1 >= rx) return lx;
		int mid = (lx + rx) / 2;
		if (tree[2*x] >= qt) return first(2*x, lx, mid, qt);
		else return first(2*x + 1, mid, rx, qt - tree[2*x]);
	}
};

int32_t main() {
	fast_io;

	int n, k; cin >> n >> k;

	string s;
	cin >> s;

	Seg st(n);
	set<int> ind;
	for (int i = 0; i < n; i++) {
		if (s[i] == ')') {
			st.update(i, 1, 1, 0, n);
			ind.insert(i);
		}
	}

	while (k--) {
		int l, r; cin >> l >> r; --l, --r;

		if (s[l] == ')') ind.erase(l);
		if (s[r] == ')') ind.erase(r);
		swap(s[l], s[r]);
		st.update(l, s[l] == ')', 1, 0, n);
		st.update(r, s[r] == ')', 1, 0, n);
		if (s[l] == ')') ind.insert(l);
		if (s[r] == ')') ind.insert(r);

		int qt = *ind.begin();

		if (qt * 2 == n) {
			cout << "No" << endl;
			continue;
		}

		int pos = st.first(1, 0, n, qt + 2);

		if (st.query(0, pos + 1, 1, 0, n) < qt + 2) {
			cout << "No" << endl;
			continue;
		}

		if (pos != n - 1 && st.query(pos + 1, n, 1, 0, n) != (n - pos - 1))
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}

}

