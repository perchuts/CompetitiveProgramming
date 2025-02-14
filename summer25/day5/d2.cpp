#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;

	int t; cin >> t;
	while (t--) {

		int n;
		cin >> n;

		vector<pair<int, int>> a(n), b(n);
		for (int i = 0; i < n; i++) {
			cin >> a[i].second >> a[i].first >> b[i].first;
			b[i].second = a[i].second;
		}

		sort(a.rbegin(), a.rend());
		sort(b.rbegin(), b.rend());

		a.emplace_back();
		b.emplace_back();

		vector<tuple<int, int, int>> events;
		int ta = 0, tb = 0;
		for (int i = 0; i < n; i++) {
			ta += a[i].second;
			tb += b[i].second;
			events.emplace_back(ta, 0, i + 1);
			events.emplace_back(tb, 1, i + 1);
		}

		bool ok = true;
		sort(events.begin(), events.end());

		int last = 0;
		int va = a[0].first, vb = b[0].first;

		int tot = 0;
		for (auto [pos, tp, i] : events) {
			int v, sz;
			if (tp) tie(v, sz) = b[i];
			else tie(v, sz) = a[i];

			tot += (pos - last) * va;
			tot -= (pos - last) * vb;
			last = pos;

			if (tp) vb = v;
			else va = v;
			ok &= tot >= 0;
		}

		ok &= tot == 0;

		cout << (ok ? "TAK" : "NIE") << endl;
	}
}
