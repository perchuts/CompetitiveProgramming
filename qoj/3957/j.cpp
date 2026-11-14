#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;

int32_t main() {_
	int n; cin >> n;
	vector<tuple<int, int, int>> v(2*n);
	int base = 0;
	for (auto &[a, b, c] : v) cin >> a >> b >> c, base += a;

	vector<int> bag;
	for (auto [a, b, c] : v) bag.push_back(c);
	sort(bag.begin(), bag.end());
	bag.erase(unique(bag.begin(), bag.end()), bag.end());
	int m = bag.size();

	for (auto &[a, b, c] : v) c = lower_bound(bag.begin(), bag.end(), c) - bag.begin();

	sort(v.begin(), v.end(), [&] (auto x, auto y) {
		int vx = get<1>(x) - get<0>(x);
		int vy = get<1>(y) - get<0>(y);
		return vx > vy;
	});
	vector<int> val(2*n);

	vector<vector<int>> occ(m);
	for (int i = 0; i < 2*n; i++) {
		auto [a, b, c] = v[i];
		val[i] = b - a;
		occ[c].push_back(i);
	}

	priority_queue<int> top, bottom;

	int delta = 0;
	
	for (int c = 0; c < m; c++) {
		auto &a = occ[c];
		if (a.empty()) continue;
		int k = a.size();
		int cnt = 0;
		for (int i = 0; i < k; i++)
			cnt += a[i] < n;

		cnt = min(cnt, k - cnt);

		base += cnt * bag[c];
		for (int i = 0; i < cnt; i++) base += val[a[i]];

		vector<int> na;
		for (int i = cnt; i < k - cnt; i++) na.push_back(a[i]);

		if (na.size() % 2 == 1) {
			if (na[0] < n) {
				base += val[na.back()];
				na.pop_back();
				a = na;
				delta += 1;
			} else {
				a.clear();
				for (int i = 1; i < na.size(); i++)
					a.push_back(na[i]);
				delta -= 1;
			}
		}
	}

	for (int c = 0; c < m; c++) {
		auto &a = occ[c];
		int k = a.size();
		if (a.empty()) continue;

		bool is_top = a[0] < n;

		vector<int> at;
		for (int i : a) at.push_back(val[i]);

		vector<int> pref = at;
		for (int i = 1; i < k; i++) pref[i] += pref[i - 1];

		vector<int> opts;
		opts.push_back(pref[k/2 - 1] + (k/2) * bag[c]);
		for (int i = 0; i < k/2; i++) {
			if (is_top) {
				opts.push_back(pref[k/2 + i] + (k/2 - i - 1) * bag[c]);
			} else {
				int p = k/2 - (i + 1);
				opts.push_back((p >= 0 ? pref[p] : 0) + (k/2 - i - 1) * bag[c]);
			}
		}
		base += opts[0];
		for (int i = 1; i <= k/2; i++) {
			if (is_top) top.push(opts[i] - opts[i - 1]);
			else bottom.push(opts[i] - opts[i - 1]);
		}

		cout << "opts " << bag[c] << endl;
		for (int x : opts) cout << x << " ";
		cout << endl;
	}

	while (delta != 0) {
		if (delta > 0) {
			assert(bottom.size());
			int dx = bottom.top();
			bottom.pop();
			base += dx;
			delta -= 2;
		} else {
			assert(top.size());
			int dx = top.top();
			top.pop();
			base += dx;
			delta += 2;
		}
	}

	int ans = base;
	int at = base;
	while (top.size() && bottom.size()) {
		cout << "HI" << endl;
		int du = top.top();
		int dv = bottom.top();
		top.pop();
		bottom.pop();
		at += du + dv;
		cout << "du " << du << " " << dv << endl;
		ans = max(ans, at);
	}

	cout << ans << endl;
}
