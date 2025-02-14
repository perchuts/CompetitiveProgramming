#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

struct not_kuhn {
	int n, m;
	vector<vector<int>> g;
	vector<int> dist, nxt, ma, mb, blockeda, blockedb;

	not_kuhn(int n_, int m_) : n(n_), m(m_), g(n),
			dist(n), nxt(n), ma(n, -1), mb(m, -1),
			blockeda(n), blockedb(m) {}
	bool get(int part, int i) {
		int ret;
		if (part) {
			if (mb[i] == -1) return true;
			auto na = ma, nb = mb;
			int i0 = mb[i];
			mb[i] = ma[i0] = -1;
			blockedb[i] = true;
			ret = matching();
			if (ret) ma = na, mb = nb;
			else {
				mb[i] = i0;
				ma[i0] = i;
			}
			blockedb[i] = false;
		} else {
			if (ma[i] == -1) return true;
			auto na = ma, nb = mb;
			int i1 = ma[i];
			ma[i] = mb[i1] = -1;
			blockeda[i] = true;
			ret = matching();
			if (ret) ma = na, mb = nb;
			else {
				ma[i] = i1;
				mb[i1] = i;
			}
			blockeda[i] = false;
		}
		return ret;
	}
	void add(int a, int b) { g[a].push_back(b); }
	bool dfs(int i) {
		for (int &id = nxt[i]; id < g[i].size(); id++) {
			int j = g[i][id];
			if (blockedb[j]) continue;
			if (mb[j] == -1 or (dist[mb[j]] == dist[i] + 1 and dfs(mb[j]))) {
				ma[i] = j, mb[j] = i;
				return true;
			}
		}
		return false;
	}
	bool bfs() {
		for (int i = 0; i < n; i++) dist[i] = n;
		queue<int> q;
		for (int i = 0; i < n; i++) if (!blockeda[i] && ma[i] == -1) {
			dist[i] = 0;
			q.push(i);
		}
		bool rep = 0;
		while (q.size()) {
			int i = q.front(); q.pop();
			for (int j : g[i]) {
				if (blockedb[j]) continue;
				if (mb[j] == -1) rep = 1;
				else if (dist[mb[j]] > dist[i] + 1) {
					dist[mb[j]] = dist[i] + 1;
					q.push(mb[j]);
				}
			}
		}
		return rep;
	}
	int matching(bool init=false) {
		int ret = 0;
		if (init) for (auto& i : g) shuffle(i.begin(), i.end(), rng);
		while (bfs()) {
			for (int j = 0; j < n; j++) nxt[j] = 0;
			for (int i = 0; i < n; i++)
				if (!blockeda[i] && ma[i] == -1 and dfs(i)) ret++;
		}
		return ret;
	}
};

int32_t main() {
	fast_io;

	int n; cin >> n;
	vector<pair<int, int>> a(n);

	array<vector<int>, 2> part;
	int id = 0;
	for (auto &[x, y] : a) {
		cin >> x >> y;
		
		part[(x+y)&1].push_back(id++);
	}

	map<pair<int, int>, int> pos;
	for (int p : {0, 1}) {
		for (int i = 0; i < part[p].size(); i++) {
			pos[a[part[p][i]]] = i;
		}
	}


	vector<pair<int, int>> mv = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	vector<vector<int>> g(n);
	id = 0;
	for (int i : part[0]) {
		auto [x, y] = a[i];
		
		for (auto [x1, y1] : mv) {
			x1 += x, y1 += y;
			if (pos.count({x1, y1})) {
				int j = pos[pair(x1, y1)];
				g[id].push_back(j);
				g[part[0].size() + j].push_back(id);
			}
		}
		id++;
	}

	not_kuhn kh(part[0].size(), part[1].size());
	//vector<int> whoa(part[0].size(), -1), whob(part[1].size(), -1);
	{
		for (int i = 0; i < part[0].size(); i++)
			for (int j : g[i])
				kh.add(i, j);
		kh.matching(true);
		//for (int i = 0; i < part[0].size(); i++) {
		//	if (kh.ma[i] != -1) {
		//		whoa[i] = kh.ma[i];
		//		whob[kh.ma[i]] = i;
		//	}
		//}
	}

	//cout << "matching" << endl;
	//for (int i = 0; i < part[0].size(); i++) {
	//	if (whoa[i] == -1) continue;
	//	auto [x, y] = a[part[0][i]];
	//	cout << x << " " << y << " ";
	//	auto [x1, y1] = a[part[1][whoa[i]]];
	//	cout << x1 << " " << y1 << endl;
	//}

	vector<pair<int, int>> ans;
	for (int i = 0; i < part[0].size(); i++) {
		if (kh.get(0, i)) {
			ans.push_back(a[part[0][i]]);
		}
		//vector<pair<int, int>> tt;
		//for (int i1 = 0; i1 < part[0].size(); i1++) {
		//	if (i == i1) continue;
		//	if (whoa[i1] == -1) continue;
		//	tt.emplace_back(i1, whoa[i1]);
		//}
		//kh.give(tt);
		//for (int i1 = 0; i1 < part[0].size(); i1++) {
		//	if (i == i1) continue;
		//	for (int j1 : g[i1]) {
		//		kh.add(i1, j1);
		//	}
		//}
		//auto [x, y] = a[part[0][i]];
		////cout << x << " " << y << ": ";
		////for (auto [i, j] : tt) cout << i << " " << j << " ";
		////cout << endl;

		//int me = kh.matching() + tt.size();

		//if (me == tam)
		//	ans.push_back(a[part[0][i]]);
	}
	//cout << kh.get(1, 2) << endl;
	for (int j = 0; j < part[1].size(); j++) {
		if (kh.get(1, j)) {
			ans.push_back(a[part[1][j]]);
		}
		//vector<pair<int, int>> tt;
		//for (int i1 = 0; i1 < part[0].size(); i1++) {
		//	if (whoa[i1] == j) continue;
		//	if (whoa[i1] == -1) continue;
		//	tt.emplace_back(i1, whoa[i1]);
		//}
		//kh.give(tt);
		//for (int i1 = 0; i1 < part[0].size(); i1++) {
		//	for (int j1 : g[i1]) if (j != j1) {
		//		kh.add(i1, j1);
		//	}
		//}
		//int me = kh.matching() + tt.size();
		//if (me == tam)
		//	ans.push_back(a[part[1][j]]);
	}

	cout << ans.size() << endl;
	sort(ans.begin(), ans.end());
	for (auto [i, j] : ans)
		cout << i << " " << j << endl;
}
