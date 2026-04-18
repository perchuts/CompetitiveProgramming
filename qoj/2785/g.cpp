#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back

using namespace std;

using ll = long long;

void solve() {
	int n; cin >> n;
	vector<int> a(n), x(n);
	for (auto& z : a) cin >> z;
	if (n % 2 == 0) {
		x[0] = a[0];
		for (int i = 1; i < n; ++i) x[i] = a[i] - x[i-1];
		vector<int> mn(2, 1e18);
		for (int i = 0; i < n; ++i) mn[i&1] = min(mn[i&1], x[i]);
		int l = -mn[0], r = mn[1];
		vector<int> mx(2, -1e18);
		for (int i = 0; i < n; ++i) {
			if (i & 1) x[i] -= l;
			else x[i] += l;
			mx[i&1] = max(mx[i&1], x[i]);
		}
		r = r - l, l = 0;
		int delta = mx[1] - mx[0];
		int work = min(delta/2, r);
		work = max(work, 0LL);
		for (int i = 0; i < n; ++i) {
			if (i & 1) x[i] -= work;
			else x[i] += work;
		}
	} else {
		int k1 = a[0];
		for (int i = 1; i < n; ++i) k1 += (i % 2 ? a[i] : -a[i]);
		k1 /= 2;
		x[0] = k1;
		for (int i = 1; i < n; ++i) x[i] = a[i] - x[i-1];
	}
	int p2 = *max_element(begin(x), end(x)), S = 0;
	for (int i = 0; i < n; ++i) S += x[i];
	S = (S + n - 2) / (n-1);
	cout << max(p2, S) << endl;
}
int32_t main() {_
	int t; cin >> t;
	while (t--) solve();
}
