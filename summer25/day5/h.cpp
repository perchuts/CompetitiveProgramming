#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;

	int n; cin >> n;
	int k; cin >> k;
	string s; cin >> s;

	int tot = 0;

	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		a[i] = s[i] == 'T' ? 2 : 1;
		tot += a[i];
	}

	int i = 0, j = n - 1;
	while (i < n && a[i] == 2) {
		i++;
	}
	while (j >= 0 && a[j] == 2) {
		j--;
	}

	if (i == n) {
		while (k--) {
			int x; cin >> x;
			if (x % 2 || tot < x) {
				cout << "NIE" << endl;
				continue;
			}

			cout << 1 << " " << x/2 << endl;
		}
		return 0;
	}

	vector<pair<int, int>> ans(tot + 1, pair(-1, -1));
	ans[1] = {i, i};

	int at = 0;
	for (int p = i + 1; p < n; p++) {
		at += a[p];
		ans[at] = {i + 1, p};
		ans[at + 1] = {i, p};
	}
	at = 0;
	for (int p = j - 1; p >= 0; --p) {
		at += a[p];
		ans[at] = {p, j - 1};
		ans[at + 1] = {p, j};
	}

	at = 0;
	for (int p = 0; p < n; p++) {
		at += a[p];
		ans[at] = {0, p};
	}
	at = 0;
	for (int p = n - 1; p >= 0; --p) {
		at += a[p];
		ans[at] = {p, n - 1};
	}

	while (k--) {
		int x; cin >> x;
		if (x > tot || ans[x].first == -1) {
			cout << "NIE" << endl;
			continue;
		}

		cout << ans[x].first + 1 << " " << ans[x].second + 1 << endl;
	}

}
