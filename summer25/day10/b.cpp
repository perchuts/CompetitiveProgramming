#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;
	int n, k, m; cin >> n >> k >> m;
	vector<int> v(n);
	for (auto& x : v) cin >> x;
	int l = 0, r = n-1, ans = -1;
	vector<pair<int, int>> ops(m);
	for (auto& [x, y] : ops) cin >> x >> y;
	while (l <= r) {
		int md = l + (r-l+1)/2;
		int act = md, ok = 0;
		for (auto [x, y] : ops) {
			if (v[act] == x) act += y;
			if (act == -1) { ok = true; break; } 
		}
		if (ok) ans = md, l = md+1;
		else r = md-1;
	}
	l = 0, r = n-1; int ans2 = n;
	while (l <= r) {
		int md = l + (r-l+1)/2;
		int act = md, ok = 0;
		for (auto [x, y] : ops) {
			if (v[act] == x) act += y;
			if (act == n) { ok = true; break; } 
		}
		if (ok) ans2 = md, r = md-1;
		else l = md+1;
	}
	if (ans2 <= ans) cout << n << endl;
	else cout << ans+1 + n-ans2 << endl;
}
