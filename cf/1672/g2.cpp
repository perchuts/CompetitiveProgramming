#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void get_dim(int n, int m) {
    vector<int> ops;
    auto get_pos = [&] (int i, int j) { return (1LL << (m * i + j)); };
    vector<vector<int>> op(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int x = 0;
            for (int k = 0; k < n; ++k) x |= get_pos(k, j);
            for (int k = 0; k < m; ++k) x |= get_pos(i, k);
            ops.pb(x);
            op[i][j] = x;
        }
    }
    vector<int> basis(n*m);
    int dim = 0;
    for (auto x : ops) {
        for (int i = 0; i < n*m; ++i) {
            if (x >> i & 1) {
                if (basis[i] == 0) { dim++, basis[i] = x; break; }
                x ^= basis[i];
            }
        }
    }
    cout << dim << endl;
}

void solve() {
    int n, m; cin >> n >> m;
    vector<string> grid(n);
    for (auto& x : grid) cin >> x;
    vector<ii> apply;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '?') apply.pb({i, j});
        }
    }
    if (n % 2 == 0 and m % 2 == 0) { 
        int ans = 1;
        for (int i = 0; i < sz(apply); ++i) ans = (ans + ans) % mod;
        cout << ans << endl;
        return;
    }
    int ans = 0;
    auto go = [&] (auto&& self, int id) -> void {
        if (id == sz(apply)) {
            vector<int> row(n), col(m);
            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
                if (grid[i][j] == '1') row[i] ^= 1, col[j] ^= 1;
            }
            if (n % 2 == 1 and m % 2 == 1) {
                bool ok = row[0] == col[0];
                for (int i = 0; i < n; ++i) ok &= row[i] == row[0];
                for (int i = 0; i < m; ++i) ok &= col[i] == col[0];
                ans += ok;
            } else if (n % 2) {
                bool ok = row[0] == 0;
                for (int i = 1; i < m; ++i) ok &= col[i] == col[0];
                ans += ok;
            } else {
                bool ok = col[0] == 0;
                for (int i = 1; i < n; ++i) ok &= row[i] == row[0];
                ans += ok;
            }
            return;
        }
        auto [x, y] = apply[id];
        grid[x][y] = '0';
        self(self, id+1);
        grid[x][y] = '1';
        self(self, id+1);
    };
    go(go, 0);
    cout << ans << endl;
}

int32_t main() {_
    while (true) {
        int n, m; cin >> n >> m;
        get_dim(n, m);
    }
#ifndef gato
    solve();
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
