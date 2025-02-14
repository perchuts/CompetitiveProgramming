#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

void solve(){
	int n; cin >> n;
	vector<vector<int>> v(3, vector<int>(n));
	for (auto& x : v) for (auto& y : x) cin >> y;
	const int MAX = 100050;
	map<tuple<int, int, int>, int> exist;
	for (int i = 0; i < n; ++i) {
		// distinct points please
		assert(exist.count({v[0][i], v[1][i], v[2][i]}) == false); 
		exist[{v[0][i], v[1][i], v[2][i]}] = i;
	}
	for (int c = 0; c < 3; ++c) {
		map<pair<int, int>, int> mn, mx, cnt;
		int c2 = (c == 0 ? 1 : 0);
		int c3 = 3 - c2 - c;
		vector<int> par(n), lvl(n);
		iota(all(par), 0);
		auto findp = [&] (auto&& self, int u) -> int {
			if (par[u] == u) return par[u] = u;
			return par[u] = self(self, par[u]);
		};
		auto unite = [&] (int u, int vv) {
			u = findp(findp, u), vv = findp(findp, vv);
			if (u == vv) return;
			if (lvl[u] < lvl[vv]) swap(u, vv);
			par[vv] = u;
			if (lvl[u] == lvl[vv]) lvl[u]++;
		};
		vector<vector<int>> pts(MAX);
		int a[8] = {1, -1, 0, 0, 0, 0, 1, -1};
		for (int i = 0; i < n; ++i) {
			pts[v[c][i]].push_back(i);
			pair<int, int> pt = {v[c2][i], v[c3][i]};
			auto& z = cnt[pt];
			z++;
			if (z == 1) mn[pt] = mx[pt] = v[c][i]; 
			else ckmin(mn[pt], v[c][i]), ckmax(mx[pt], v[c][i]);
		}
		for (int i = 0; i < n; ++i) {
			auto l = mn[{v[c2][i], v[c3][i]}];
			auto r = mx[{v[c2][i], v[c3][i]}];
			if (r-l+1 != cnt[{v[c2][i], v[c3][i]}]) {
				cout << "NO" << endl;
				exit(0);
			}
		}
		for (int i = 0; i < MAX; ++i) {
			if (pts[i].empty()) continue;
			map<pair<int, int>, int> exist2;
			for (auto id : pts[i]) exist2[{v[c2][id], v[c3][id]}] = id;
			for (auto id : pts[i]) {
				int x = v[c2][id], y = v[c3][id]; 
				for (int j = 0; j < 4; ++j) {
					auto x2 = x + a[j], y2 = y + a[j+4]; 
					if (exist2.count({x2, y2})) unite(id, exist2[{x2, y2}]);
				}
			}
			int comp = findp(findp, pts[i][0]);
			for (auto id : pts[i]) {
				if (findp(findp, id) != comp) {
					cout << "NO" << endl;
					exit(0);
				}
			}
		}
	}
	vector<int> par(n), lvl(n);
	iota(all(par), 0);
	auto findp = [&] (auto&& self, int u) -> int {
		if (par[u] == u) return par[u] = u;
		return par[u] = self(self, par[u]);
	};
	auto unite = [&] (int u, int vv) {
		u = findp(findp, u), vv = findp(findp, vv);
		if (u == vv) return;
		if (lvl[u] < lvl[vv]) swap(u, vv);
		par[vv] = u;
		if (lvl[u] == lvl[vv]) lvl[u]++;
	};
	for (int i = 0; i < n; ++i) {
		for (int a = -1; a <= 1; ++a) {
			for (int b = -1; b <= 1; ++b) {
				for (int c = -1; c <= 1; ++c) {
					int cnt = (a != 0) + (b != 0) + (c != 0);
					if (cnt != 1) continue;
					int x2 = v[0][i] + a, y2 = v[1][i] + b, z2 = v[2][i] + c;
					if (exist.count({x2, y2, z2})) unite(i, exist[{x2, y2, z2}]);
				}
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		if (findp(findp, i) != findp(findp, 0)) {
			cout << "NO" << endl;
			exit(0);
		}
	}
	cout << "YES" << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
