#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back
//#define gato

using ll = long long;
using namespace std;

int brute(int n, int w, vector<int> v, vector<int> c) {
	vector<int> dp(w+1);
	for (int i = 0; i < n; ++i) {
		for (int j = w; j >= v[i]; --j) {
			dp[j] = max(dp[j], dp[j-v[i]] + c[i]);
		}
	}
	return *max_element(begin(dp), end(dp));
}

int solve(int n, int w, vector<int> v, vector<int> c) {
	if (w <= 400) {
		vector<int> dp(w+1);
		for (int i = 0; i < n; ++i) {
			for (int j = w; j >= v[i]; --j) {
				dp[j] = max(dp[j], dp[j-v[i]] + c[i]);
			}
		}
		return *max_element(begin(dp), end(dp));
	} 
	int ans = 0;
	// pegar 1
	for (int i = 0; i < n; ++i) if (v[i] <= w) ans = max(ans, c[i]);
	vector<int> ord(n); iota(begin(ord), end(ord), 0);
	sort(begin(ord), end(ord), [&] (int x, int y) { return v[x] < v[y]; });
	set<pair<int, int>> bons;
	int ptr = -1;
	for (int i = 0; i < n; ++i) {
		if (v[ord[i]] <= w) bons.insert({-c[ord[i]], ord[i]}), ptr = i;
	}
	for (auto i : ord) {
		if (v[i] > w) break;
		while (ptr >= 0 and v[i] + v[ord[ptr]] > w) {
			bons.erase({-c[ord[ptr]], ord[ptr]});
			ptr--;
		}
		if (v[i] + v[i] <= w) {
			bons.erase({-c[i], i});
		}
		if (!bons.empty()) ans = max(ans, c[i] - (begin(bons)->first));
		if (v[i] + v[i] <= w) {
			bons.insert({-c[i], i});
		}
	}
	vector<int> sm, lg;
	for (int i = 0; i < n; ++i) {
		if (3 * v[i] <= w) sm.pb(i);
		else lg.pb(i);
	}
	sort(begin(sm), end(sm), [&] (int x, int y) {
			return c[x] > c[y];
			});
	if (sm.size() >= 3) {
		ans = max(ans, c[sm[0]] + c[sm[1]] + c[sm[2]]);
	}
	vector<vector<int>> ss(101);
	for (auto i : sm) {
		ss[w - 3 * v[i]].pb(i);
	}
	sort(begin(lg), end(lg), [&] (int x, int y) {
			return v[x] < v[y];
			});
	int m = lg.size();
	vector<int> mx(m+1);
	for (int i = 1; i <= m; ++i) mx[i] = max(mx[i-1], c[lg[i-1]]);
	for (int i = 0; i <= 100; ++i) {
		sort(begin(ss[i]), end(ss[i]), [&] (int x, int y) {
				return c[x] > c[y];
				});
	}
	vector<int> vals;
	for (int i = 0; i < m; ++i) vals.pb(v[lg[i]]);
	for (int i = 0; i <= 100; ++i) {
		if (ss[i].size() >= 2) {
			int mx_pode = w - v[ss[i][0]] - v[ss[i][1]];
			int lb = lower_bound(begin(vals), end(vals), mx_pode + 1) - begin(vals);
			ans = max(ans, c[ss[i][0]] + c[ss[i][1]] + mx[lb]);
		}
		for (int j = i + 1; j <= 100; ++j) {
			if (ss[i].empty() or ss[j].empty()) continue;
			int mx_pode = w - v[ss[i][0]] - v[ss[j][0]];
			int lb = lower_bound(begin(vals), end(vals), mx_pode + 1) - begin(vals);
			ans = max(ans, c[ss[i][0]] + c[ss[j][0]] + mx[lb]);
		}
	}
	vector<pair<int, int>> opt(m+1, make_pair(-1, -1));
	for (int i = 1; i <= m; ++i) {
		opt[i] = opt[i-1];
		if (opt[i].first == -1) {
			opt[i].first = lg[i-1];
			continue;
		}
		if (opt[i].second == -1) {
			opt[i].second = lg[i-1];
			if (c[opt[i].second] > c[opt[i].first]) swap(opt[i].first, opt[i].second);
			continue;
		}
		int f = c[opt[i].first], s = c[opt[i].second];
		int idx = lg[i-1];
		if (c[idx] > s) {
			if (c[idx] >= f) {
				opt[i].second = opt[i].first;
				opt[i].first = idx;
			} else opt[i].second = idx;
		}
	}
	for (int i = 0; i <= 100; ++i) {
		if (ss[i].empty()) continue;
		ptr = m;
		int id_peq = ss[i][0];
		for (int j = 1; j <= m; ++j) {
			while (ptr >= 1 and v[id_peq] + vals[j-1] + vals[ptr-1] > w) ptr--;
			if (ptr == 0) break;
			int choice = opt[ptr].first;
			if (choice == lg[j-1]) choice = opt[ptr].second;
			if (choice != -1) {
				ans = max(ans, c[id_peq] + c[lg[j-1]] + c[choice]);
			}
		}
	}
	return ans;
}

int32_t main() {_
#ifndef gato
	int t; cin >> t;
	while (t--) {
		int n, w; cin >> n >> w;
		vector<int> c(n), v(n);
		for (auto& x : v) cin >> x;
		for (auto& x : c) cin >> x;
		cout << solve(n, w, v, c) << endl;
	}
#else
	int t = 1;
	while (true) {
		int n = rand() % 50 + 1, w = rand() % 3000 + 1;
		vector<int> v(n), c(n);
		for (int i = 0; i < n; ++i) {
			c[i] = rand() % 10 + 1;
			int lb = max(1LL, (w - 98) / 3);
			v[i] = lb + (rand() % 100);
		}
		auto ans = brute(n, w, v, c);
		auto my = solve(n, w, v, c);
		if (ans != my) {
			cout << n << " " << w << endl;
			for (int i = 0; i < n; ++i) cout << v[i] << " ";
			cout << endl;
			for (int i = 0; i < n; ++i) cout << c[i] << " ";
			cout << endl;
			cout << "solve: " << my << endl;
			cout << "brute: " << ans << endl;
			exit(0);
		}
		cout << "AC " << t++ << endl;
	}
#endif
}
