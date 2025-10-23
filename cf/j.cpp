#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

int32_t main() {
	fast_io;
	int n; cin >> n;
	vector<vector<int>> a(n), b(n);
	vector<int> aa, bb;
	for (int i = 0; i < n; ++i) {
		int k; cin >> k;
		a[i].resize(k);
		for (auto& x : a[i]) cin >> x, aa.push_back(x);
	}
	for (int i = 0; i < n; ++i) {
		int k; cin >> k;
		b[i].resize(k);
		for (auto& x : b[i]) cin >> x, bb.push_back(x);
	}
	if (n >= 3) {
		sort(begin(aa), end(aa));
		sort(begin(bb), end(bb));
		cout << (aa == bb ? "S" : "N") << endl;
		exit(0);
	}
	if (n == 1) {
		cout << (a == b ? "S" : "N") << endl;
		exit(0);
	}
	auto go = [] (vector<vector<int>> &c) {
		while (!c[1].empty() and (c[0].empty() or c[0].back() >= c[1].back())) {
			int k = c[1].back(); c[1].pop_back();
			c[0].push_back(k);
		}
	};
	go(a), go(b);
	cout << (a == b ? "S" : "N") << endl;
}
