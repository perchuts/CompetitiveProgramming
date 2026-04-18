#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define endl '\n'
#define pb push_back
using namespace std;

using ll = long long;


void solve() {
	int n; cin >> n;
	vector<int> a;
	for (int i = 0; i < n; ++i) {
		int x; cin >> x;
		if (x > 0) a.pb(x);
	}
	sort(rbegin(a), rend(a));
	n = a.size();
	if (n == 0) {
		cout << 0 << endl;
		return;
	}
	if (a[0] == 1) {
		cout << (n % 2 ? n : 0) << endl;
		return;
	}
	if (n == 1) {
		cout << 1 << endl;
		return;
	}
	// n >= 2, a[0] > 1
	if (a[1] > 1) {
		cout << 0 << endl;
		return;
	}
	cout << 1 << endl;
}

int32_t main() {_
	int t; cin >> t;
	while (t--) solve();
}
