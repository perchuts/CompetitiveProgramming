#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;

	int n; cin >> n;
	vector<int> v(n), ord(n);
	for (auto &x : v) cin >> x;

	iota(ord.begin(), ord.end(), 0);
	sort(ord.begin(), ord.end(), [&] (int i, int j) {
		return v[i] < v[j];
	});
	sort(v.begin(), v.end());

	if (v[n - 1] == v[0]) {
		for (int i = 0; i < n; i++)
			cout << "N";
		cout << endl;
		return 0;
	}

	int lo = 0, hi = n - 1;
	while (lo < hi) {
		int mid = (lo + hi + 1) / 2;

		int val = v[n - 1 - mid];
		bool ok = true;
		for (int i = 0; i < n; i++) {
			if (i == n - 1 - mid) continue;
			if (val <= v[i]) {
				ok = false;
				break;
			}
			val += v[i];
		}
		
		if (ok)
			lo = mid;
		else
			hi = mid - 1;
	}

	vector<int> ans(n, 0);
	for (int i = 0; i <= lo; i++)
		ans[ord[n-1-i]] = true;

	for (int i = 0; i < n; i++)
		cout << (ans[i] ? "T" : "N");
	cout << endl;
}
