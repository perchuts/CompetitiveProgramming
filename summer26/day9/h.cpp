#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll
using namespace std;

using ll = long long;

int32_t main() {_ 
	int n, m; cin >> n >> m;
	vector<int> l(n), r(n);
	for (int i = 0; i < n; ++i) cin >> l[i] >> r[i];
	multiset<pair<int, int>> s;
	vector<tuple<int, int, int>> intr;
	for (int i = 1; i < n; ++i) {
		int lx = l[i] - r[i-1];
		int rx = r[i] - l[i-1];
		intr.pb({rx, lx, i-1});
	}
	for (int i = 0; i < m; ++i) {
		int x; cin >> x;
		s.insert({x, i});
	}
	vector<int> ans(n-1);
	sort(begin(intr), end(intr));
	for (auto [rx, lx, idx] : intr) {
		auto it = s.lower_bound({lx, -1});
		if (it == end(s)) {
			cout << "No" << endl;
			exit(0);
		}
		if (rx < (it->first)) {
			cout << "No" << endl;
			exit(0);
		}
		ans[idx] = it->second;
		s.erase(s.find({it->first, it->second}));
	}
	cout << "Yes" << endl;
	for (auto x : ans) cout << x + 1 << " ";
	cout << endl;
}
