#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
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
ll inv(ll a, ll b) {
    return a > 1 ? b - inv(b%a, a)*b/a : 1;
}
ii calc(int n, vector<string> grid) {
    int x = 0, y = 0, w = 0;
    vector<int> qt_r(n), qt_c(n);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        if (grid[i][j] == '#') qt_r[i]++, qt_c[j]++, w++;
    }
    int winv = inv(w, n);
    for (int i = 0; i < n; ++i) x = (x + qt_r[i] * i) % n, y = (y + qt_c[i] * i) % n;
    x = x * winv % n;
    y = y * winv % n;
    return {x, y};
}

array<int, 4> cht(int n, vector<string> grid, int tx, int ty) {
    int w = 0;
    for (auto x : grid) for (auto y : x) w += (y == '#');
    if (w < n*n/2) {
        for (auto& x : grid) for (auto& y : x) y = (y == '.' ? '#' : '.');
        w = n*n - w;
    }
    auto [cx, cy] = calc(n, grid); 
    int need_x = (tx - cx + n) % n, need_y = (ty - cy + n) % n;
    if (max(need_x, need_y) == 0) return {0, 0, 0, 0};
    int dx = need_x * w % n, dy = need_y * w % n;
    array<int, 4> choice = {-1};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int i2 = (i - dx + n) % n, j2 = (j - dy + n) % n;
            if (grid[i][j] == '.' and grid[i2][j2] == '#') {
                choice = {i, j, i2, j2};
            }
        }
    }
    assert(choice[0] != -1);
    return choice;
}

ii wil(int n, vector<string> grid) {
    int w = 0;
    for (auto x : grid) for (auto y : x) w += (y == '#');
    if (w < n*n/2) {
        for (auto& x : grid) for (auto& y : x) y = (y == '.' ? '#' : '.');
        w = n*n - w;
    }
    auto [x, y] = calc(n, grid);
    return {x, y};
}

int32_t main() {_
#ifndef gato
    string s; cin >> s;
    if (s[0] == 'f') {
        int t = 1; cin >> t;
        while(t--) {
            int n; cin >> n;
            vector<string> grid(n);
            for (auto& x : grid) cin >> x;
            int tx, ty; cin >> tx >> ty, --tx, --ty;
            auto ans = cht(n, grid, tx, ty);
            for (int i = 0; i < 4; ++i) cout << ans[i]+1 << " \n"[i==3];
        }
    } else {
        int t = 1; cin >> t;
        while(t--) {
            int n; cin >> n;
            vector<string> grid(n);
            for (auto& x : grid) cin >> x;
            auto [x, y] = wil(n, grid);
            cout << x+1 << " " << y+1 << endl;
        }
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 15);
        vector<string> grid(n, string(n, '.'));
        int w = 0;
        for (auto& x : grid) for (auto& y : x) {
            if (rnd(0, 2)) w++, y = '#';
        }
        if (gcd(w, n) != 1) continue;
        int hx = rnd(0, n-1), hy = rnd(0, n-1);
        auto change = cht(n, grid, hx, hy);
        swap(grid[change[0]][change[1]], grid[change[2]][change[3]]);
        int tx = rnd(0, n-1), ty = rnd(0, n-1);
        ii rx = {1, 0}, ry = {0, 1};
        if (rnd(0, 1)) swap(rx, ry);
        if (rnd(0, 1)) rx.first *= -1, rx.second *= -1;
        if (rnd(0, 1)) ry.first *= -1, ry.second *= -1;
        auto get = [&] (int i, int j) {
            ii res = {(10*n*n + tx + i * rx.first + j * ry.first) % n, (10 * n * n + ty + i * rx.second + j * ry.second) % n};
            return res;
        };
        auto grid2 = grid;
        for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
            auto [i2, j2] = get(i, j);
            grid2[i2][j2] = grid[i][j];
        }
        auto my = wil(n, grid);
        if (hx != my.first or hy != my.second) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            swap(grid[change[0]][change[1]], grid[change[2]][change[3]]);
            for (auto x : grid) cout << x << " ";
            cout << endl;
            cout << "hidden: " << hx << " " << hy << endl;
            cout << "change: ";
            for (auto x : change) cout << x << " ";
            cout << endl;
            cout << "my: " << my.first << " " << my.second << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
