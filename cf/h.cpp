#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

int32_t main() {
	fast_io;

	int n; cin >> n;
	vector<int> a(n);
	for (auto &i : a) cin >> i;

	sort(a.begin(), a.end());

	if (n == 1 && a[0] == 1) {
		cout << "*" << endl;
		return 0;
	}

	if (a[0] != 1) {
		cout << a.back() << " " << 1 << endl;
		return 0;
	} else {
		int val = -1, cnt = 0;
		bool ok = true;
		for (int i = 0; i < n; i++) {
			ok &= a.back() % a[i] == 0;
			if (!binary_search(a.begin(), a.end(), a.back() / a[i])) {
				val = a.back() / a[i], cnt++;
			}
		}

		int sq = sqrt(a.back()) + 5;
		while (sq*sq > a.back()) --sq;

		if (sq * sq == a.back() && !binary_search(a.begin(), a.end(), sq)) {
			val = sq, cnt++;
		}

		if (ok && (cnt == 1)) {
			cout << a.back() << " " << val << endl;
			return 0;
		}

		cout << a[1] * a.back() << " " << a[1] * a.back() << endl;
	}
}
