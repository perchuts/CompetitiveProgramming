#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

struct bit {
	int n;
	vector<int> tree;
	bit(int _n) : n(_n), tree(n + 1, 0) {}
	void update(int i, int x) {
		for (++i; i <= n; i += i&(-i))
			tree[i] += x;
	}
	int pref(int i) {
		int ans = 0;
		for (++i; i; i -= i&(-i))
			ans += tree[i];
		return ans;
	}
	int query(int l, int r) {
		return pref(r) - pref(l - 1);
	}
};

int32_t main() {
	fast_io;

	string s; cin >> s;
	int n = s.size();

	const int N = 2;
	vector<deque<int>> st(N);

	for (int i = 0; i < n; i++) {
		st[s[i] - 'a'].push_back(i);
	}
	if ((st[0].size() % 2) && (st[1].size() % 2)) {
		cout << -1 << endl;
		return 0;
	}

	bit in(n);
	for (int i = 0; i < n; i++) in.update(i, 1);

	int ans = 0;
	for (int i = 0; 2*i + 2 <= n; i++) {
		int best = n + 2;
		int who = -1;
		for (int c = 0; c < N; c++) {
			if (st[c].size() <= 1) continue;

			int l = st[c].front(), r = st[c].back();
			int qt = in.pref(l - 1) + in.query(r + 1, n - 1);
			if (qt < best) {
				best = qt;
				who = c;
			}
		}
		assert(best < n + 2);

		ans += best;
		int c = who;
		in.update(st[c].front(), -1);
		in.update(st[c].back(), -1);
		st[c].pop_front();
		st[c].pop_back();
	}

	cout << ans << endl;

}
