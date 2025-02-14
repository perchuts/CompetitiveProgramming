#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;

	int n; cin >> n;
	vector<int> a(n);
	for (auto &i : a) cin >> i;

	vector<int> bag = a;
	sort(bag.begin(), bag.end());
	bag.erase(unique(bag.begin(), bag.end()), bag.end());

	auto id = [&] (int i) {
		return lower_bound(bag.begin(), bag.end(), i) - bag.begin();
	};

	vector<int> p(n + 1, 0);
	vector<vector<int>> w(n + 1);
	iota(p.begin(), p.end(), 0);

	for (int i = 0; i < n; i++)
		w[i].push_back(i);

	auto findp = [&] (auto&& findp, int a) {
		if (a == p[a]) return a;
		return findp(findp, p[a]);
	};
	auto unite = [&] (int a, int b) {
		a = findp(findp, a);
		b = findp(findp, b);
		if (a == b) return;
		if (w[a].size() < w[b].size()) swap(a, b);
		for (auto i : w[b]) w[a].push_back(i);
		w[b].clear();
		p[b] = a;
	};
	for (int i = 0; i < n; i++) {
		int j = n - i - 1;
		unite(id(a[i]), id(a[j]));
	}

	vector<pair<int, int>> ops;
	for (int i = 0; i < n; i++) {
		//cout << i << " " << findp(findp, i) << " " << w[i].size() << endl;
		if (findp(findp, i) == i) {
			vector<int> v = w[i];
			sort(v.begin(), v.end());
			for (int j = 1; j < v.size(); j++)
				ops.emplace_back(bag[v[j]], bag[v[0]]);
		}
	}

	cout << ops.size() << endl;
	for (auto [a, b] : ops)
		cout << a << " " << b << endl;
}
