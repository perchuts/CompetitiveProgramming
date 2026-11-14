#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
//#define gato

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

vector<string> solve(int n, int m, vector<string> grid) {
	vector<vector<int>> mark(n, vector<int>(m));
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
		mark[i][j] = (j % 3 == 0 or grid[i][j] == 'X');
	}

	for (int j = 0; j + 3 < m; j += 3) {
		if (n > 1 and (grid[1][j+1] == 'X' or grid[1][j+2] == 'X')) mark[1][j+1] = mark[1][j+2] = 1;
		else mark[0][j+1] = mark[0][j+2] = 1;
	}

	if (m % 3 == 0) {
		for (int i = 0; i < n; ++i) {
			if (grid[i][m-1] == 'X') mark[i][m-2] = 1;
		}
	}
	vector<string> ans(n);	
    for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) ans[i] += ".X"[mark[i][j]];
	}
	return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
		int n, m; cin >> n >> m;
		vector<string> grid(n);
		for (auto& x : grid) cin >> x;
		auto ans = solve(n, m, grid);
		for (auto x : ans) cout << x << endl;
		cout << endl;
	}
#else
    int t = 1;
    while (true) {
		int n = rnd(1, 8), m = rnd(1, 8);
		vector<string> grid(n, string(m, '.'));
		vector<vector<int>> can(n, vector<int>(m, 1));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (!can[i][j]) continue;
				int r = rnd(0, 9);
				if (r >= 8) {
					for (int a = -1; a <= 1; ++a) for (int b = -1; b <= 1; ++b) {
						int i2 = i+a, j2 = j+b;
						if (min(i2, j2) >= 0 and i2 < n and j2 < m) can[i2][j2] = 0;
					}
					grid[i][j] = 'X';
				}
			}
		}
		cout << "input: ";
		cout << n << " " << m << endl;
		for (auto x : grid) cout << x << endl;
		cout << endl;
		solve(n, m, grid);
    }
#endif
}
