#include <bits/stdc++.h>
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

int32_t main() {
	fast_io;

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		string s; cin >> s;

		vector<int> v(n);
		for (int i = 0; i < n; i++) {
			if (s[i] == '?') v[i] = 2;
			else v[i] = s[i] - '0';
		}

		Bit bit(n);

		array<vector<int>, 3> cnt = {vector<int>(n), vector<int>(n), vector<int>(n)};
		for (int x = 0; x < 3; x++) {
			for (int i = 0; i < n; i++) {
				cnt[x][i] = v[i] == x;
				if (i) cnt[x][i] += cnt[x][i - 1];
			}
		}

		// tudo 1
		int inv = 0;
		for (int i = 0; i < n; i++) {
			if (s[i] == '0') inv += cnt[1][i] + cnt[2][i];
		}

		int ans = inv;
		for (int i = n - 1; i >= 0; --i) {
			if (v[i] == 2) {
				inv -= (cnt[0][n-1] - cnt[0][i]) + (cnt[2][n-1] - cnt[2][i]);
				inv += cnt[1][i] + cnt[2][i] - 1;
				ans = max(ans, inv);
			}
		}
		
		cout << -ans << endl;
	}

}
