#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define endl '\n'
#define pb push_back

using namespace std;

using ll = long long;

int32_t main() {_
	int n; cin >> n;
	vector<int> a(n);
	int S = 0;
	for (auto& x : a) cin >> x, S += x;
	vector<pair<int, int>> ans;
	set<pair<int, int>> s;
	auto apply = [&] (int i, int j) {
		ans.push_back({i, j});
		s.erase({a[j], j});
		s.erase({a[i], i});
		int sx = (a[i] + a[j]);
		a[i] = (sx/2), a[j] = (sx+1)/2;
		s.insert({a[i], i});
		s.insert({a[j], j});
	};
	for (int i = 0; i < n; ++i) s.insert({a[i], i});
	while (true) {
		auto [v1, id1] = *begin(s);
		auto [v2, id2] = *prev(end(s));
		if (v1 == S/n and v2 == (S+n-1)/n) break;
		apply(id1, id2);
	}
	int need = S % n;
	for (int i = n-1; i >= n - need; --i) {
		if (a[i] != (S+n-1)/n) {
			bool ok = 0;
			for (int j = 0; j < i; ++j) {
				if (a[j] == (S+n-1)/n) {
					apply(j, i);
					ok = 1;
					break;
				}
			}
			assert(ok);
		}
	}
	for (int i = 1; i < n; ++i) assert(a[i] >= a[i-1]);
	cout << ans.size() << endl;
	for (auto [x, y] : ans) cout << x + 1 << " " << y + 1 << endl;
}
