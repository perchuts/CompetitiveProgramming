#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

template<typename T> struct minq {
	vector<T> v;
	int n; static const int b = 30;
	vector<int> mask, t;

	int op(int x, int y) { return v[x] <= v[y] ? x : y; }
	int msb(int x) { return __builtin_clz(1) - __builtin_clz(x); }
	int small(int r, int sz = b) { return r-msb(mask[r]&((1<<sz)-1)); }
	minq() {}
	minq(const vector<T>& v_) : v(v_), n(v.size()), mask(n), t(n) {
		for (int i = 0, at = 0; i < n; mask[i++] = at |= 1) {
			at = (at<<1)&((1<<b)-1);
			while (at and op(i-msb(at&-at), i) == i) at ^= at&-at;
		}
		for (int i = 0; i < n/b; i++) t[i] = small(b*i+b-1);
		for (int j = 1; (1<<j) <= n/b; j++)
			for (int i = 0; i+(1<<j) <= n/b; i++)
				t[n/b*j+i] = op(t[n/b*(j-1)+i], t[n/b*(j-1)+i+(1<<(j-1))]);
	}
	int index_query(int l, int r) {
		if (r-l+1 <= b) return small(r, r-l+1);
		int x = l/b+1, y = r/b-1;
		if (x > y) return op(small(l+b-1), small(r));
		int j = msb(y-x+1);
		int ans = op(small(l+b-1), op(t[n/b*j+x], t[n/b*j+y-(1<<j)+1]));
		return op(ans, small(r));
	}
	T query(int l, int r) { return v[index_query(l, r)]; }
};

template<typename T> struct maxq {
	vector<T> v;
	int n; static const int b = 30;
	vector<int> mask, t;

	int op(int x, int y) { return v[x] >= v[y] ? x : y; }
	int msb(int x) { return __builtin_clz(1) - __builtin_clz(x); }
	int small(int r, int sz = b) { return r-msb(mask[r]&((1<<sz)-1)); }
	maxq() {}
	maxq(const vector<T>& v_) : v(v_), n(v.size()), mask(n), t(n) {
		for (int i = 0, at = 0; i < n; mask[i++] = at |= 1) {
			at = (at<<1)&((1<<b)-1);
			while (at and op(i-msb(at&-at), i) == i) at ^= at&-at;
		}
		for (int i = 0; i < n/b; i++) t[i] = small(b*i+b-1);
		for (int j = 1; (1<<j) <= n/b; j++)
			for (int i = 0; i+(1<<j) <= n/b; i++)
				t[n/b*j+i] = op(t[n/b*(j-1)+i], t[n/b*(j-1)+i+(1<<(j-1))]);
	}
	int index_query(int l, int r) {
		if (r-l+1 <= b) return small(r, r-l+1);
		int x = l/b+1, y = r/b-1;
		if (x > y) return op(small(l+b-1), small(r));
		int j = msb(y-x+1);
		int ans = op(small(l+b-1), op(t[n/b*j+x], t[n/b*j+y-(1<<j)+1]));
		return op(ans, small(r));
	}
	T query(int l, int r) { return v[index_query(l, r)]; }
};

int32_t main() {
	fast_io;

	int n; cin >> n;
	int q; cin >> q;

	vector<int> a(n);
	for (auto &i : a) cin >> i;

	vector<pair<int, int>> queries(q);
	for (auto &[l, r] : queries) {
		cin >> l >> r;
		--l, --r;
	}

	minq mn(a);
	maxq mx(a);

	vector<int> dp(n), lx(n), rx(n);
	auto go = [&] (auto&& self, int l, int r) -> int {
		if (l >= r) return 0;
		int m = mx.index_query(l, r);

		lx[m] = l;
		rx[m] = r;

		dp[m] = max(self(self, l, m - 1), self(self, m + 1, r)) + 1;
		return dp[m];
	};
	go(go, 0, n - 1);

	map<pair<int, int>, int> memo;
	auto go2 = [&] (auto&& self, int l, int r) -> int {
		if (l >= r) return 0;
		int m = mx.index_query(l, r);
		if (lx[m] == l && rx[m] == r) return dp[m];

		memo[pair(l, r)] = max(self(self, l, m - 1), self(self, m + 1, r)) + 1;
		return memo[pair(l, r)];
	};
	for (auto [l, r] : queries) {
		cout << go2(go2, l, r) << endl;
	}
}
