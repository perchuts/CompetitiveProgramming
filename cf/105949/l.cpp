#include <bits/stdc++.h>
#define GATO
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

struct Bit {
	int n;
	vector<int> tree;
	Bit(int _n) : n(_n), tree(n + 1) {}
	void update(int i, int x) {
		for (++i; i <= n; i += i & -i) tree[i] += x;
	}
	int pref(int i) {
		int ans = 0;
		for (++i; i <= n; i += i & -i) ans += tree[i];
		return ans;
	}
	int query(int l, int r) { return pref(r) - pref(l - 1); }
};

int solve(int n, string s) {
	vector<int> a(n+1), b(n+1), c(n+1);
	vector<int> x(n+1), y(n+1);
	for (int i = 1; i <= n; i++) {
		a[i] = a[i-1] + (s[i-1] == 'a');
		b[i] = a[i-1] + (s[i-1] == 'b');
		c[i] = a[i-1] + (s[i-1] == 'c');
		x[i] = b[i] - a[i];
		y[i] = c[i] - a[i];
	}
	int ans = 0;
	for(int iii=0;iii<3;iii++){
		vector<int> ord(n+1);
		for(int i=0;i<=n;i++) ord[i] = i;

		sort(ord.begin(), ord.end(), [&](int i, int j){
			if(x[i] != x[j]) return x[i] < x[j];
			return y[i] < y[j];
		});

		int MX = 5*n;
		int SH = 2*n;
		Bit b1(MX), b2(MX);
		
		for(auto j : ord){
			ans += b1.query(y[j]+SH, MX) * (x[j] - y[j]);
			ans += b2.query(y[j]+SH, MX);
			b1.update(y[j]+SH, 1);
			b2.update(y[j]+SH, y[j]-x[j]);
		}
		vector<int> nx(n+1), ny(n+1);
		for(int i=0;i<=n;i++) nx[i] += x[i], ny[i] += x[i], nx[i] -= y[i];
		swap(y, ny);
		swap(x, nx);
	}

	return -ans;
}

int brute(int n, string s) {
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int va = 0;
		int vb = 0;
		int vc = 0;
		for (int j = i; j < n; j++) {
			va += s[j] == 'a';
			vb += s[j] == 'b';
			vc += s[j] == 'c';
			
			int mx = 0, mn = 1e9;
			if (va) mx = max(mx, va), mn = min(mn, va);
			if (vb) mx = max(mx, vb), mn = min(mn, vb);
			if (vc) mx = max(mx, vc), mn = min(mn, vc);

			ans += mx - mn;
		}
	}

	return ans;
}

int32_t main() {
#ifndef GATO
	fast_io;

	int n; cin >> n;
	string s; cin >> s;
	auto ans1 = solve(n, s);
	auto ans2 = brute(n, s);
	cout << ans1 << endl;
	cout << ans2 << endl;

#else

	for (int seed = 1; ; seed++) {
		int n = rand() % 3 + 1;
		string s;
		for (int i = 0; i < n; i++) s += ('a' + (rand() % 3));
		auto ans1 = solve(n, s);
		auto ans2 = brute(n, s);
		if (ans1 != ans2) {
			cout << "WA " << seed << endl;
			cout << n << endl;
			cout << s << endl;

			cout << ans1 << endl;
			cout << ans2 << endl;
			break;
		}
		cout << "AC " << seed << endl;
	}

#endif
}
