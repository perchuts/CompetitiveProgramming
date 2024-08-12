#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define sz(x) (int) x.size()
#define pb push_back
#define fast ios_base::sync_with_stdio(0); cin.tie(0);
using namespace std;

using ll = long long;

const int mod = 998244353;
const int inf = 2e9 + 100;

using pii = pair<int, int>;
struct Seg {
	int n;
	vector<pii> tree;
	Seg(int _n = 0) : n(_n), tree(2 * n, {-1, -1}) {}
	void update(int i, int v) { // a[i] = v
		i += n;
		tree[i] = {v, i};
		for (; i; i /= 2) {
			tree[i/2] = max(tree[i], tree[i^1]);
		}
	}
	pii query(int l, int r) { // query(l, r)
		pii ans = {-1, -1};
		for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
			if (r & 1) ans = max(ans, tree[--r]);
			if (l & 1) ans = max(ans, tree[l++]);
		}
		return ans;
	}
};

int32_t main() {fast
	int n; cin >> n;
	vector<tuple<int, int, int>> inter(n);
	vector<int> bag;
	int _id = 0;
	for (auto &[l, r, i] : inter) {
		cin >> l >> r;
		r += l;
		bag.push_back(l);
		bag.push_back(r);
		i = _id++;
	}

	sort(bag.begin(), bag.end());
	bag.erase(unique(bag.begin(), bag.end()), bag.end());
	int m = bag.size();
	for (auto &[l, r, i] : inter) {
		l = lower_bound(bag.begin(), bag.end(), l) - bag.begin();
		r = lower_bound(bag.begin(), bag.end(), r) - bag.begin();
	}

	Seg st(m);
	
	sort(inter.begin(), inter.end(), [](auto a, auto b) {
		auto [la, ra, _] = a;
		auto [lb, rb, __] = b;
		if (ra == rb) return la < lb;
		else return ra > rb;
	});

	vector<int> ans(n);
	for (auto [l, r, i] : inter) {
		ans[i] = st.query(0, l).first + 1;
		int nw = max(st.query(l, l).first, ans[i]);
		st.update(l, nw);
	}
	
	for (int i = 0; i < n; i++)
		cout << ans[i] << " \n"[i == n - 1];
}
