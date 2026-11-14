#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;

template<bool directed=true> struct euler {
	int n;
	vector<vector<pair<int, int>>> g;
	vector<int> used;

	euler(int n_) : n(n_), g(n) {}
	void add(int a, int b) {
		int at = used.size();
		used.push_back(0);
		g[a].emplace_back(b, at);
	}

	pair<bool, vector<pair<int, int>>> get_path(int src) {
		if (!used.size()) return {true, {}};
		vector<int> beg(n, 0);
		for (int& i : used) i = 0;
		vector<pair<pair<int, int>, int>> ret, st = {{{src, -1}, -1}};
		while (st.size()) {
			int at = st.back().first.first;
			int& it = beg[at];
			while (it < g[at].size() and used[g[at][it].second]) it++;
			if (it == g[at].size()) {
				if (ret.size() and ret.back().first.second != at)
					return {false, {}};
				ret.push_back(st.back()), st.pop_back();
			} else {
				st.push_back({{g[at][it].first, at}, g[at][it].second});
				used[g[at][it].second] = 1;
			}
		}
		if (ret.size() != used.size()+1) return {false, {}};
		vector<pair<int, int>> ans;
		for (auto i : ret) ans.emplace_back(i.first.first, i.second);
		reverse(begin(ans), end(ans));
		return {true, ans};
	}
	pair<bool, vector<pair<int, int>>> get_cycle() {
		if (!used.size()) return {true, {}};
		int src = 0;
		while (!g[src].size()) src++;
		auto ans = get_path(src);
		if (!ans.first or ans.second[0].first != ans.second.back().first)
			return {false, {}};

		ans.second[0].second = ans.second.back().second;
		ans.second.pop_back();
		return ans;
	}

};

int32_t main() {_
	int n; cin >> n;
	vector<int> a(n);
	for (auto& x : a) cin >> x, --x;
	auto b = a; sort(begin(b), end(b));
	if (a == b) {
		cout << 0 << endl;
		return 0;
	}
	auto solve1 = [&] () {
		euler E(2*n);
		for (int i = 0; i < n; ++i) {
			if (a[i] == b[i]) continue;
			E.add(i, a[i]+n);
			E.add(b[i]+n, i);
		}
		auto [can, cyc] = E.get_cycle();
		if (!can) return vector<int>();
		vector<int> ans;
		for (auto [x, y] : cyc) if (x < n) ans.pb(x);
		reverse(begin(ans), end(ans));
		return ans;
	};
	{
		auto v = solve1();
		if (!v.empty()) {
			cout << 1 << endl;
			cout << v.size() << endl;
			for (auto x : v) cout << x+1 << " ";
			cout << endl;
			return 0;
		}
	}
	cout << 2 << endl;
	vector<vector<int>> cycles;
	vector<int> vis(n), ord(n);
	iota(begin(ord), end(ord), 0);
	sort(begin(ord), end(ord), [&] (int x, int y) { if (a[x] == a[y]) return x < y; return a[x] < a[y]; });
	vector<int> op1;
	for (int i = 0; i < n; ++i) {
		if (vis[i]) continue;
		int cur = i;
		vector<int> cyc;
		while (!vis[cur]) cyc.pb(cur), vis[cur] = 1, cur = ord[cur];
		if (cyc.size() == 1) continue;
		op1.pb(cyc[0]);
		cycles.pb(cyc);
	}
	int t = op1.size();
	cout << t << endl;
	for (auto x : op1) cout << x+1 << " ";
	cout << endl;
	{
		auto na = a;
		for (int i = 0; i < t; ++i) na[op1[i]] = a[op1[(i+1)%t]];
		swap(a, na);
	}
	auto v = solve1();
	assert(!v.empty());
	cout << v.size() << endl;
	for (auto x : v) cout << x+1 << " ";
	cout << endl;
	return 0;
}
