#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

struct kuhn {
	int n, m;
	vector<vector<int>> g;
	vector<int> vis, ma, mb;

	kuhn(int n_, int m_) : n(n_), m(m_), g(n),
			vis(n+m), ma(n, -1), mb(m, -1) {}

	void add(int a, int b) { g[a].push_back(b); }
	bool dfs(int i) {
		vis[i] = 1;
		for (int j : g[i]) if (!vis[n + j]) {
			vis[n+j] = 1;
			if (mb[j] == -1 or dfs(mb[j])) {
				ma[i] = j, mb[j] = i;
				return true;
			}
		}
		return false;
	}
	int solve() {
		int ret = 0, aum = 1;
		for (auto& i : g) shuffle(i.begin(), i.end(), rng);
		while (aum) {
			for (int j = 0; j < m; j++) vis[n+j] = 0;
			aum = 0;
			for (int i = 0; i < n; i++)
				if (ma[i] == -1 and dfs(i)) ret++, aum = 1;
		}
		return ret;
	}
};

int32_t main() {
	fast_io;

	int n, k;
	cin >> n >> k;

	vector<pair<int, int>> v;
	map<pair<int, int>, int> st, ot;

	for (int i = 0; i < k; i++) {
		int a, b;
		cin >> a >> b;
		v.emplace_back(a, b);
		if ((a+b) % 2) {
			int sz = st.size();
			st[pair(a, b)] = sz;
		} else {
			int sz = ot.size();
			ot[pair(a, b)] = sz;
		}
	}

	kuhn ku(st.size(), ot.size());
	
	int dx[] = {1, 1, -1, -1, 2, 2, -2, -2};
	int dy[] = {2, -2, -2, 2, 1, -1, -1, 1};
	for (auto [p, i] : st) {
		auto [x, y] = p;
		for (int j = 0; j < 8; j++) {
			int x1 = x + dx[j];
			int y1 = y + dy[j];

			if (ot.count(pair(x1, y1))) {
				ku.add(i, ot[pair(x1, y1)]);
			}
		}
	}

	cout << ku.solve() << endl;
}
