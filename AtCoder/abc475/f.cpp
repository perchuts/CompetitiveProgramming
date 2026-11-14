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
    int n, m; cin >> n >> m;
    vector<string> grid(n);
    for (auto& x : grid) cin >> x;
    if (n > m) {
        vector<string> g(m, string(n, '.'));
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) g[j][i] = grid[i][j];
        swap(n, m);
        swap(grid, g);
    }
    int ans = 1;
    vector<int> last_white(n, -1);
    vector ps(m, vector(n, vector(n, 0LL)));
    for (int col = 0; col < m; ++col) {
        for (int i = 0; i < n; ++i) if (grid[i][col] == '.') last_white[i] = col;
        for (int l = 0; l < n; ++l) {
            bool ok = 1;
            for (int r = l; r < n; ++r) {
                if (col) ps[col][l][r] = ps[col-1][l][r]; 
                ok &= (grid[r][col] == '#');
                ps[col][l][r] += ok;
                int r2 = min((l == 0 ? inf : last_white[l-1]), last_white[r]);
                if (!ok and r2 != -1) ans += r2+1-ps[r2][l][r];
            }
        }
    }
    cout << ans << endl;
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
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
