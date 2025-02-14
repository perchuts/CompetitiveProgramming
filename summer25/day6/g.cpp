#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;
	int n; cin >> n;
	vector<array<int, 3>> v(n);
	int id = 0;
	vector<pair<int, int>> events;
	double x2 = 0, x = 0, c = 0;
	for (auto& a : v) {
		cin >> a[0] >> a[1] >> a[2];	
		x2 += a[0], x += a[1], c += a[2]; 
		int l; cin >> l;
		events.emplace_back(l, id++);
	}
	sort(begin(events), end(events));
	double last = 0;
	double ans = 0;
	auto eval = [&] (double coord) {
		return coord*coord*x2+coord*x+c; 
	};
	for (int l = 0, r = 0; l < n; l = r) {
		// vou tentar aqui
		double cx = events[l].first;
		ans = max(ans, eval(last)), ans = max(ans, eval(cx));
		if (x2 != 0) {
			double opt = -x / (2*x2);
			if (last <= opt and opt <= cx) ans = max(ans, eval(opt));
		}
		while (r < n and events[r].first == events[l].first) {
			id = events[r].second;
			x2 -= v[id][0];
			x -= v[id][1];
			c -= v[id][2];
			r++;
		}
		last = cx;
	}
	cout << fixed << setprecision(10) << ans << endl;
}
