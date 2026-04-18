#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
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

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int brute(int n, int m, vector<string> grid) {
    map<vector<string>, int> table;
int x, y;
for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    if (grid[i][j] == 'E') x = i, y = j;
}
    auto rec = [&] (auto&& self, vector<string> s) -> int {
        if (table.count(s)) return table[s];
        table[s] = 0;
        auto t = s;
        int nice = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i == x and j == y) {
                    if (i != n-1 and s[i+1][j] == 'o') nice = 1;
                } else {
                    if (i == n-1) t[i][j] = '.';
                    else t[i][j] = s[i+1][j];
                }
            }
        }
        table[s] = max(table[s], self(self, t)+nice), nice = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i == x and j == y) {
                    if (i and s[i-1][j] == 'o') nice = 1;
                } else {
                    if (i == 0) t[i][j] = '.';
                    else t[i][j] = s[i-1][j];
                }
            }
        }
        table[s] = max(table[s], self(self, t)+nice), nice = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i == x and j == y) {
                    if (j != m-1 and s[i][j+1] == 'o') nice = 1;
                } else {
                    if (j == m-1) t[i][j] = '.';
                    else t[i][j] = s[i][j+1];
                }
            }
        }
        table[s] = max(table[s], self(self, t)+nice), nice = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i == x and j == y) {
                    if (j and s[i][j-1] == 'o') nice = 1;
                } else {
                    if (j == 0) t[i][j] = '.';
                    else t[i][j] = s[i][j-1];
                }
            }
        }
        table[s] = max(table[s], self(self, t)+nice), nice = 0;
        return table[s];
    };
    return rec(rec, grid);
}

short int ps[101][101], ps2[101][101];

short int dp[101][101][101][101];

int solve(int n, int m, vector<string> grid) {
    ii z; for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) if (grid[i][j] == 'E') z = {i+1,j+1};

    int x = z.first, y = z.second;

    int ans = 0;

    
    auto get = [&] (int x1, int y1, int x2, int y2) {
        int a = x2, b = y2;
        int c = x1+n-1, d = y1+m-1;
        a -= x-1, b -= y-1, c -= x-1, d -= y-1;
        return array<int, 4>{a, b, c, d};
    };

    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) ps[i][j] = ps[i][j-1] + (grid[i-1][j-1] == 'o'), ps2[i][j] = ps2[i-1][j] + (grid[i-1][j-1] == 'o');

    for (int x1 = n; x1; --x1) {
        for (int y1 = m; y1; --y1) {
            for (int x2 = x1; x2 <= n; ++x2) {
                for (int y2 = y1; y2 <= m; ++y2) { 
                        dp[x1][y1][x2][y2] = 0;
                    if (!(x1 <= x and x <= x2) or !(y1 <= y and y <= y2)) continue;
                    if (x1 == x2 and y1 == y2) continue;
                    bool penis = (x1 == 1 and y1 == 1 and x2 == 3 and y2 == 1);
                    if (x1 != x2) {
                        // tenta explorar ir por cima ou por baixo
                        array<int, 4> eu = get(x1, y1, x2-1, y2);
                        int adc = 0;  
                        if (eu[0] <= x2 and x2 <= eu[2]) {
                            int lx = max(eu[1], y1), rx = min(eu[3], y2);
                            if (lx <= rx) adc = ps[x2][rx]-ps[x2][lx-1];
                            else adc = 0;
                        } else adc = 0;
                        ckmax(dp[x1][y1][x2][y2], dp[x1][y1][x2-1][y2]+adc);
                        // (y1, y2) da linha x2. quantos contem o retangulo (x1, y1), (x2-1, y2)?
                        eu = get(x1+1, y1, x2, y2);
                        if (eu[0] <= x1 and x1 <= eu[2]) {
                            int lx = max(eu[1], y1), rx = min(eu[3], y2);
                            if (lx <= rx) adc = ps[x1][rx]-ps[x1][lx-1];
                            else adc = 0;
                        } else adc = 0;
                        ckmax(dp[x1][y1][x2][y2], dp[x1+1][y1][x2][y2]+adc);
                        // retangulo NxM terminando em (i+x, j+y)
                    }
                    if (y1 != y2) {
                        // tenta explorar ir pela esquerda ou pela direita
                        array<int, 4> eu = get(x1, y1+1, x2, y2);
                        int adc = 0;
                        if (eu[1] <= y1 and y1 <= eu[3]) {
                            int lx = max(eu[0], x1), rx = min(eu[2], x2);
                            if (lx <= rx) adc = ps2[rx][y1]-ps2[lx-1][y1];
                            else adc = 0;
                        } else adc = 0;
                        ckmax(dp[x1][y1][x2][y2], dp[x1][y1+1][x2][y2]+adc);
                        eu = get(x1, y1, x2, y2-1);
                        if (eu[1] <= y2 and y2 <= eu[3]) {
                            int lx = max(eu[0], x1), rx = min(eu[2], x2);
                            if (lx <= rx) adc = ps2[rx][y2]-ps2[lx-1][y2];
                            else adc = 0;
                        } else adc = 0;
                        ckmax(dp[x1][y1][x2][y2], dp[x1][y1][x2][y2-1]+adc);
                    }
                    ckmax(ans, dp[x1][y1][x2][y2]);
                }
            }
        }
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int n, m; cin >> n >> m;
    vector<string> grid(n);
    for (auto& x : grid) cin >> x;
    cout << solve(n, m, grid) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 4), m = rnd(2, 4);
        vector<string> grid(n, string(m, '.'));
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
            if (rnd(0, 3) >= 2) grid[i][j] = 'o';
        }
        int x = rnd(0, n-1), y = rnd(0, m-1);
        grid[x][y] = 'E';
        int my = solve(n, m, grid), ans = brute(n, m, grid);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << " " << m << endl;
            for (auto x : grid) cout << x << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
