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

int solve(int l, int n, int m, vector<int> a, vector<vector<int>> grid){
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
	return (sz(ganha) > 0);
}
mt19937 rng(time(0));
int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}
int32_t main(){_
	int tt = 1;
	while (true) {
		int l = rnd(1, 10), n = rnd(1, 3), m = rnd(1, 3);
		vector<vector<int>> grid(n, vector<int>(m));
		for (auto& x : grid) for (auto& y : x) y = rnd(1, n*m);
		vector<int> a(l);
		for (auto& x : a) x = rnd(1, n*m);
		int my = solve(l, n, m, a, grid), win = 0;
		vector dp(l, vector(n, vector(m, 0)));
		for (int i = l-1; i >= 0; --i) {
			for (int j = 0; j < n; ++j) {
				for (int k = 0; k < m; ++k) {
					if (grid[j][k] != a[i]) continue;
					if (i == l-1) {
						dp[i][j][k] = 1;
						if (i == 0) win |= dp[i][j][k];
						continue;
					}
					bool has = 0, lose = 0;
					for (int x = j+1; x < n; ++x) {
						for (int y = k+1; y < m; ++y) {
							if (grid[x][y] != a[i+1]) continue;
							has = 1;
							lose |= (dp[i+1][x][y]^1);
						}
					}
					dp[i][j][k] = (!has || lose);
					if (i == 0) win |= dp[i][j][k];
				}
			}
		}
		if (my != win) {
			cout << "Wrong answer on test " << tt << endl;
			cout << l << ' ' << n << ' ' << m << endl;
			for (auto x : a) cout << x << ' ';
			cout << endl;
			for (auto x : grid) {
				for (auto y : x) cout << y << ' ';
				cout << endl;
			}
			cout << "Your output: " << my << endl;
			cout << "Correct answer: " << win << endl;
			exit(0);
		}
		cout << "Accepted on test " << tt++ << endl;
	}
}
