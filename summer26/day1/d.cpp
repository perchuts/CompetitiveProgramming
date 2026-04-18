#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back
//#define gato

using ll = long long;
using namespace std;



vector<int> brute(int n, int q,vector<int> a, vector<int> b, vector<pair<int, int>> qq) {
	vector<int> resp;
	for (auto [l, r] : qq) {
		int val = 0;
		for (int i = l; i <= r; ++i) {
			val *= b[i];
			val += a[i];
			val %= 998244353;
		}
		resp.pb(val);
	}
	return resp;
}

vector<int> solve(int n, int q,vector<int> a, vector<int> b, vector<pair<int, int>> qq) {
	const int mod = (119<<23)+1;
	struct node {
		int a, b;
	};
	vector<node> seg(4*n);
	auto merge = [&] (node f, node g) {
		// g(f(x))
		node res;
		res.a = f.a * g.a % mod;
		res.b = (g.b + g.a * f.b) % mod;
		return res;
	};
	auto build = [&] (auto&& self, int i, int l, int r) -> void {
		if (l == r) {
			seg[i].b = a[l], seg[i].a = b[l];
			return;
		}
		int md = (l+r)/2;
		self(self, 2*i, l, md);
		self(self, 2*i+1, md+1, r);
		seg[i] = merge(seg[2*i], seg[2*i+1]);
	};
	auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> node {
		if (x <= l and r <= y) return seg[i];
		int md = (l+r)/2;
		if (y <= md) return self(self, 2*i, l, md, x, y);
		if (md < x) return self(self, 2*i+1, md+1, r, x, y);
		auto lx = self(self, 2*i, l, md, x, y);
		auto rx = self(self, 2*i+1, md+1, r, x, y);
		return merge(lx, rx);
	};
	build(build, 1, 0, n-1);
	vector<int> resp;
	for (auto [l, r] : qq) {
		auto ans = query(query, 1, 0, n-1, l, r);
		resp.pb(ans.b%mod);
	}
	return resp;
}

int32_t main() {
#ifndef gato
	int n; cin >> n;
	vector<int> a(n), b;
	for (auto& x : a) cin >> x;
	b.pb(0);
	for (int i = 0; i < n-1; ++i) {
		int x; cin >> x;
		b.pb(x);
	}
	int q; cin >> q;
	vector<pair<int, int>> qq;
	for (int i = 0; i < q; ++i) {
		int l, r; cin >> l >> r; --l, --r;
		qq.push_back({l, r});
	}
	auto ans = solve(n, q, a, b, qq);
	for (auto x : ans) cout << x << endl;
#else 
	int t = 1;
	while (true) {
		int n = rand() % 3 + 1, q = 1;
		vector<pair<int, int>> qq(q);
		vector<int> a(n), b(n);
		for (int i = 0; i < n; ++i) a[i] = rand() % 1000000000;
		for (int i = 1; i < n; ++i) b[i] = rand() % 1000000000;
		for (int i = 0; i < q; ++i) {
			int l = rand() % n, r = rand() % n;
			if (l > r) swap(l, r);
			qq[i] = {l, r};
		}
		auto my = solve(n, q, a, b, qq);
		auto ans = brute(n, q, a, b, qq);
		if (my != ans) {
			cout << n << endl;
			for (auto x : a) cout << x << " ";
			cout << endl;
			for (int i = 1; i < n; ++i) cout << b[i] << " ";
			cout << endl;
			cout << q << endl;
			for (int i = 0; i < q; ++i) cout << qq[i].first+1 << " " <<qq[i].second+1 << endl;
			cout << "solve: ";
			for (auto x : my) cout << x << " ";
			cout << endl;
			cout << "brute: ";
			for (auto x : ans) cout << x << " ";
			cout << endl;
			exit(0);
		}
		cout << "Accepted on test " << t++ << endl;
	}
#endif
}
