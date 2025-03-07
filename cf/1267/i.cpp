#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;

vector<int> perm, pos;
bool query(int a, int b) {
	cout << "? " << a+1 << " " << b+1 << endl;
	char x; cin >> x;
	//char x = (pos[a] < pos[b] ? '>' : '<');
	//if (x == '>') adj[a][b] = 1;
	//else adj[b][a] = 1;
	//cout << x << endl;
	//return pos[a] < pos[b];

	return x == '>';
}

vector<vector<int>> gera(int n) {
	vector<int> p(n);
	iota(p.begin(), p.end(), 0);

	vector<vector<int>> ps;
	do {
		ps.push_back(p);
	} while (next_permutation(p.begin(), p.end()));
	return ps;
}

int n;

void test_case(int seed=0) {
	int n; cin >> n;
	//srand(seed);
	//perm.resize(2*n); pos.resize(2*n);
	//iota(perm.begin(), perm.end(), 0);
	//random_shuffle(perm.begin(), perm.end());
	//for (int i = 0; i < 2*n; i++) pos[perm[i]] = i;

	//for (int i : perm) cout << i+1 << " ";
	//cout << endl;

	adj.assign(2*n, vector<int>(2*n, 0));
	if (n <= 4) {
		vector<vector<int>> ps = gera(2*n);

		vector<pair<int, int>> perguntas;
		for (int i = 0; i < 2*n; i++)
			for (int j = i + 1; j < 2*n; j++)
				perguntas.emplace_back(i, j);
		random_shuffle(perguntas.begin(), perguntas.end());
		map<vector<int>, int> memo;
		map<vector<int>, pair<int, int>> recup;

		auto W = [&] (vector<int>& mask) {
			vector<int> st, p;
			bool dif = false;
			for (auto i : mask) {
				auto cur = ps[i];
				cur.resize(n);
				if (st.empty()) {
					st = cur;
					p = cur;
					sort(st.begin(), st.end());
				} else {
					if (!dif && p != cur) dif = true;
					sort(cur.begin(), cur.end());
					if (cur != st) return false;
				}
			}
			return dif;
		};

		auto L = [&] (vector<int>& mask) {
			vector<int> p;
			for (int i : mask) {
				auto cur = ps[i];
				cur.resize(n);
				if (p.empty()) {
					p = cur;
				} else {
					if (p != cur) return false;
				}
			}
			return true;
		};

		auto filtra = [&] (vector<int>& mask, int a, int b) {
			vector<int> nmask;
			for (int i : mask) {
				auto& cur = ps[i];
				int pa = 0, pb = 0;
				for (int j = 0; j < 2*n; j++) {
					if (cur[j] == a) pa = j;
					if (cur[j] == b) pb = j;
				}
				if (pa < pb) nmask.push_back(i);
			}
			return nmask;
		};

		auto solve = [&] (auto&& self, vector<int>& mask) -> int {
			if (memo.count(mask)) return memo[mask];
			if (W(mask)) return 1;
			if (L(mask)) return 0;
			int ans = 0;
			for (auto [i, j] : perguntas) {
				auto m1 = filtra(mask, i, j);
				auto m2 = filtra(mask, j, i);
				if (m1 == mask || m2 == mask) continue;
				if (self(self, m1) && self(self, m2)) {
					ans = 1;
					recup[mask] = {i, j};
					break;
				}
			}
			memo[mask] = ans;
			return ans;
		};

		vector<int> at(ps.size());
		iota(at.begin(), at.end(), 0);

		vector<int> v(2*n);
		iota(v.begin(), v.end(), 0);
		//for (int iter = 0; iter < (n == 4 ? 3 : 1); iter++) {
		//	while (v.size() != 1) {
		//		if (v.size() % 2) {
		//			int a = v.back(); v.pop_back();
		//			int b = v.back(); v.pop_back();
		//			int resp = query(a, b);
		//			if (resp) {
		//				v.push_back(b);
		//				at = filtra(at, a, b);
		//			} else {
		//				v.push_back(a);
		//				at = filtra(at, b, a);
		//			}
		//		} else {
		//			vector<int> nv;
		//			for (int i = 1; i < v.size(); i += 2) {
		//				int a = v[i];
		//				int b = v[i-1];
		//				int resp = query(a, b);
		//				if (resp) {
		//					nv.push_back(b);
		//					at = filtra(at, a, b);
		//				} else {
		//					nv.push_back(a);
		//					at = filtra(at, b, a);
		//				}
		//			}
		//			v = nv;
		//		}
		//	}
		//}

		for (int a = 0; a < n; a++) {
			int b = a + n;
			int resp = query(a, b);
			if (resp) at = filtra(at, a, b);
			else at = filtra(at, b, a);
		}

		int step = 0;
		while (!W(at)) {
			solve(solve, at);
			assert(recup.count(at));
			auto [a, b] = recup[at];
			int resp = query(a, b);
			if (resp) at = filtra(at, a, b);
			else at = filtra(at, b, a);
		}
		cout << "!" << endl;
		return;
	}

	vector<int> dead(2*n);
	for (int iter = 0; iter < n; iter++) {
		vector<int> v;
		for (int i = 0; i < 2*n; i++) {
			if (dead[i]) continue;
			bool is_min = true;
			for (int j = 0; j < 2*n; j++) {
				if (dead[j]) continue;
				if (adj[i][j] == 1) is_min = false;
			}
			if (is_min) v.push_back(i);
		}
		//srand(time(0));
		random_shuffle(v.begin(), v.end());
		while (v.size() != 1) {
			if (v.size() % 2) {
				int a = v.back(); v.pop_back();
				int b = v.back(); v.pop_back();
				if (query(a, b)) v.push_back(b);
				else v.push_back(a);
			} else {
				vector<int> nv;
				for (int i = 1; i < v.size(); i += 2) {
					int a = v[i];
					int b = v[i-1];
					if (query(a, b)) nv.push_back(b);
					else nv.push_back(a);
				}
				v = nv;
			}
		}
		//cerr << v[0]+1 << " eh min" << endl;
		dead[v[0]] = true;
	}
	//cout << "!" << endl;

	vector saw(2*n, vector<int>(2*n, 0));

	bool ok = false;
	for (int i = 0; i < 2*n; i++) {
		if (dead[i]) continue;
		vector<int> vis(2*n, 0);
		auto dfs = [&] (auto&& self, int u) -> void {
			if (vis[u]) return;
			vis[u] = true;
			for (int v = 0; v < 2*n; v++) if (!dead[v] && adj[u][v]) {
				self(self, v);
			}
		};
		dfs(dfs, i);
		for (int j = 0; j < 2*n; j++) if (!dead[j] && vis[j]) saw[i][j] = true;
	}
	for (int i = 0; i < 2*n; i++) if (!dead[i]) {
		for (int j = 0; j < 2*n; j++) if (!dead[j])
			ok |= !saw[i][j] && !saw[j][i];
	}

	assert(ok);
}

int32_t main() {
	srand(6969420);

	int t; cin >> t;
	while (t--) test_case();

	//cin >> n;
	//for (int seed = 1; seed <= 10000/n/n; seed++) {
	//	cout << seed << endl;
	//	test_case(seed);
	//}
}

