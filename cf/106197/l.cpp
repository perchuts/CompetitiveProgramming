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
    int n; cin >> n;
	if (n == 3) {
		cout << "443\n211\n111\n" << endl;
		return;
	}
    vector<vector<int>> grid(n, vector<int>(n));
    vector<int> row(n), col(n);
    int par = n&1;
    for (int i = 0; i < n-par; ++i) {
        for (int j = 0; j < n-par; ++j) {
            grid[i+par][j+par] =  1 + (i > j) + 2 * (max(i, j) * 2 < n-par);
        }
    }
    if (n & 1) {
        for (int i = 0; i < n; ++i) grid[0][i] = grid[i][0] = 4;
        grid[0][n-1] = 1;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << grid[i][j];
            row[i] += grid[i][j];
            col[j] += grid[i][j];
        }
        cout << endl;
    }
}

int32_t main() {_
    //int bits = 3*3;
    //for (int i = 0; i < (2<<bits); ++i) {
    //    vector<vector<int>> grid(3, vector<int>(3));
    //    vector<int> row(3), col(3);
    //    vector<int> mark(30);
    //    bool ok = 1;
    //    for (int a = 0; a < 3; ++a) {
    //        for (int b = 0; b < 3; ++b) {
    //            int pos_bit = 3*a+b;
    //            int val = (i>>(2*pos_bit))&3;
    //            grid[a][b] = val+1;
    //            row[a] += val+1;
    //            col[b] += val+1;
    //        }
    //    }
    //    for (int a = 0; a < 3; ++a) {
    //        ok &= (mark[row[a]] == 0);
    //        mark[row[a]] = 1;
    //    }
    //    for (int a = 0; a < 3; ++a) {
    //        ok &= (mark[col[a]] == 0);
    //        mark[col[a]] = 1;
    //    }
    //    if (ok) {
    //        for (auto x : grid) {
    //            for (auto y : x) cout << y;
    //            cout << endl;
    //        }
    //        exit(0);
    //    }
    //}
#ifndef gato
    int t = 1; cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
