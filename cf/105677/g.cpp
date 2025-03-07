#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

int32_t main() {
	fast_io;
	int r, n; cin >> r >> n;
	vector<int> d(n);
	for (auto& x : d) cin >> x;
	int cur1 = 0, cur2 = r;
	for (int i = 0; i < n; ++i) {
		if (d[i] <= 0) cur1 = max(0LL, cur1 + d[i]), cur2 = max(0LL, cur2 + d[i]);
		else cur1 = min(r, cur1 + d[i]), cur2 = min(r, cur2 + d[i]);
	}
	if (cur1 == cur2) cout << cur1 << endl;
	else cout << "uncertain" << endl;
}
