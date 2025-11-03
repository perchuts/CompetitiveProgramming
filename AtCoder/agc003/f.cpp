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

void solve() {
	int n, m, k; cin >> n >> m >> k;
	vector<string> grid(n);
	for (auto& x : grid) cin >> x;
	if (k == 0) {
		cout << 1 << endl;
		exit(0);
	}
	auto fexp = [&] (int b, int e, int m) {
		int ans = 1;
		while (e) {
			if (e&1) ans = ans * b % m;
			e /= 2, b = b * b % m;
		}
		return ans;
	};
	int ones = 0;
	for (auto x : grid) for (auto y : x) ones += (y == '#');
	auto f = [] (vector<string> v) {
		int n = v.size();
		int m = v[0].size();
		vector<string> g(n*n, string(m*m, '.'));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (v[i][j] == '.') continue;
				for (int a = 0; a < n; ++a) for (int b = 0; b < m; ++b) g[n*i+a][m*j+b] = v[a][b];
			}
		}
		return g;
	};
	int lim = 2;
		for (int z = 1; ; ++z) {
			for (auto x : grid) cout << x << endl;
				cout << endl << endl << endl;
				if (z == lim) break;
				grid = f(grid);
		}
	int tt = 0;
	for (int i = 0; i < n; ++i) if (grid[i][0] == '#' and grid[i][m-1] == '#') tt = 1;
	for (int i = 0; i < m; ++i) if (grid[0][i] == '#' and grid[n-1][i] == '#') tt |= 2;
	if (tt == 0) {
		// na vdd acho q eh ones^(2^k-1)...
		cout << fexp(ones, fexp(2, k-1, mod-1), mod) << endl;
		exit(0);
	}
	if (tt == 3) {
		cout << 1 << endl;
		exit(0);
	}
	if (tt == 2) {
		vector<string> gg(m, string(n, '^'));;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				gg[j][i] = grid[i][j];
			}
		}
		swap(n, m);
		swap(grid, gg);
	}

	// se tem x comps conexas na linha,
	// na proxima iteracao vai ter
	// x * tot(it anterior) comps conexas ali ao todo.
	// n faco ideia de quantas comps conexas vai ter nas proximas linhas.

}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
