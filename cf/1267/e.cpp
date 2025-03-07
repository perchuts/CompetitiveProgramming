#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;

	int n; cin >> n;
	int m; cin >> m;
	vector a(m, vector<int>(n));
	for (auto &v : a) for (auto &i : v) cin >> i;

	int best = -1;
	vector<int> ans;
	for (int w = 0; w < n - 1; w++) {
		vector<pair<int, int>> v;
		int at = 0;
		for (int i = 0; i < m; i++) {
			at += a[i][n - 1] - a[i][w];
			v.push_back({a[i][n - 1] - a[i][w], i});
		}
		sort(v.begin(), v.end());
		vector<int> st;
		while (at > 0) {
			auto [dx, i] = v.back();
			v.pop_back();
			at -= dx;
			st.push_back(i);
		}

		if (best == -1 || st.size() < best) {
			best = st.size();
			swap(st, ans);
		}
	}

	cout << ans.size() << endl;
	for (auto i : ans) cout << i + 1 << " ";
	cout << endl;
}
