#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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

bool solve(int l, int n, int m, vector<int> a, vector<vector<int>> grid){
	for (auto& x : a) --x;
	for (auto& x : grid) for (auto& y : x) --y;
	vector<vector<ii>> pos(n*m);
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) pos[grid[i][j]].pb({i, j});
	for (int i = 0; i < n * m; ++i) {
		sort(all(pos[i]));
		vector<ii> npos;
		for (auto [x, y] : pos[i]) {
			while (!npos.empty() && npos.back().second <= y) npos.pop_back();
			npos.pb({x, y});
		}
		swap(pos[i], npos);
	}
	set<ii> lose, ganha;
	for (int i = l-1; i >= 0; --i) {
		set<ii> nlose, nganha;
		for (auto [x, y] : pos[a[i]]) {
			auto it2 = ganha.lower_bound({x+1, 0});
			if (it2 != end(ganha) and y < (*it2).second) nlose.insert({x, y});
			else nganha.insert({x, y});
			//cout << "round: " << i+1 << " x: " << x << " y: " << y << " win: " << win << endl;
		}
		swap(lose, nlose), swap(ganha, nganha);
	}
	return (sz(ganha) == 0);
}
mt19937 rng(time(0));
int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}
int32_t main(){_
	int t; cin >> t;
	while (t--) {
		int l, n, m; cin >> l >> n >> m;
		vector<int> a(l);
		for (auto& x : a) cin >> x;
		vector<vector<int>> grid(n, vector<int>(m));
		for (auto& x : grid) for (auto& y : x) cin >> y;
		int s = solve(l, n, m, a, grid);
		cout << (s ? "N" : "T") << endl;
	}
}
