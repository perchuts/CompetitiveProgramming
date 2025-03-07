#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

void test_case() {
	int n, m, q; cin >> n >> m >> q;

	vector<pair<int, int>> tasks(n);
	for (int i = 0; i < n; i++) cin >> tasks[i].second;
	for (int i = 0; i < n; i++) cin >> tasks[i].first;

	sort(tasks.begin(), tasks.end());
	for (int i = 1; i < n; i++) {
		tasks[i].second += tasks[i - 1].second;
	}

	vector<int> mn(n);
	for (int i = n - 1; i >= 0; --i) {
		mn[i] = tasks[i].first - tasks[i].second;
		if (i + 1 < n) mn[i] = min(mn[i], mn[i + 1]);
	}

	vector<int> s(m);
	for (auto &i : s) cin >> i;
	for (int i = 1; i < m; i++) s[i] += s[i - 1];

	const int INF = 1e10;

	while (q--) {
		int t; cin >> t;

		int pos = upper_bound(tasks.begin(), tasks.end(), pair<int, int>(t, INF)) - tasks.begin();

		int aqui = t - (pos == 0 ? 0 : tasks[pos - 1].first);
		if (pos) aqui += (tasks[pos - 1].first - tasks[pos - 1].second);

		int folga = aqui;
		if (pos != n) folga = min(folga, mn[pos]);
		
		int j = upper_bound(s.begin(), s.end(), folga) - s.begin();
		cout << j << " \n"[!q];
	}
}

int32_t main() {
	fast_io;

	int t; cin >> t;
	while (t--) test_case();
}
