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

const int inf = 1e9+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int solve(int n, int m, vector<string> rubens) {

    vector dp(n, vector(m, vector(n, vector(m, vector(n, vector(m, inf))))));

    auto grid = dp;

    vector good(n, vector(m, vector(n, vector(m, 1))));

    ii st;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c = rubens[i][j];
            if (c == 'T') st = {i, j}, grid[0][0][0][0][i][j] = 0;
            else if (c == '.') grid[0][0][0][0][i][j] = 0;
            else grid[0][0][0][0][i][j] = 1, good[0][0][0][0] = 0;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int i2 = 0; i2 < n; ++i2) {
                for (int j2 = 0; j2 < m; ++j2) {
                    if (i + j + i2 + j2 == 0) continue;
                    for (int a = 0; a < n; ++a) {
                        for (int b = 0; b < m; ++b) {
                            if (i <= a and a <= i2 and j <= b and b <= j2) grid[i][j][i2][j2][a][b] = grid[0][0][0][0][a][b];
                            else grid[i][j][i2][j2][a][b] = 0;
                            if (grid[i][j][i2][j2][a][b]) good[i][j][i2][j2] = 0;
                        }
                    }
                }
            }
        }
    }

    dp[0][0][n-1][m-1][st.first][st.second] = 0;


    queue<array<int, 6>> q;

    vector A = {1, -1, 0, 0, 0, 0, 1, -1};

    int s1 = st.first,s2 = st.second,s3 = n-1-s1,s4 = m-1-s2;

    q.push({0, 0, n-1, m-1, s1, s2});
    int ans = inf;
    while (!q.empty()) {
        auto arr = q.front(); q.pop();
        int i1 = arr[0], j1 = arr[1], i2 = arr[2], j2 = arr[3], x = arr[4], y = arr[5];
        if (good[i1][j1][i2][j2]) ckmin(ans, dp[i1][j1][i2][j2][x][y]);
		if (dp[i1][j1][i2][j2][x][y] == 2 and good[i1][j1][i2][j2]) {
			cout << i1 << ' ' << j1 << ' ' << i2 << ' ' << j2 << ' ' << x << ' ' << y << endl;
		}
        for (int z = 0; z < 4; ++z) {
            int dx = A[z], dy = A[z+4];
            int x2 = dx + x, y2 = dy + y; 
            if (x2 < n and y2 < m and min(x2, y2) >= 0 and grid[i1][j1][i2][j2][x2][y2]) continue;
            int ni1 = i1, nj1 = j1, ni2 = i2, nj2 = j2;
            if (x2 == -1) ni2--;
            else if (y2 == -1) nj2--;
            else if (x2 == n) ni1++;
            else if (y2 == m) nj1++;
            else ni1 = x2-s1, nj1 = y2-s2, ni2 = x2+s3, nj2 = y2+s4;
            if (ni1 >= n or nj1 >= m or min(ni2, nj2) < 0) ckmin(ans, dp[i1][j1][i2][j2][x][y]+1);
            ckmin(ni1, n-1), ckmax(ni1, 0);
            ckmin(ni2, n-1), ckmax(ni2, 0);
            ckmin(nj1, m-1), ckmax(nj1, 0);
            ckmin(nj2, m-1), ckmax(nj2, 0);
            ckmin(x2, n-1), ckmax(x2, 0);
            ckmin(y2, m-1), ckmax(y2, 0);
            ckmax(ni1, i1), ckmax(nj1, j1), ckmin(ni2, i2), ckmin(nj2, j2);
            if (dp[ni1][nj1][ni2][nj2][x2][y2] == inf) {
                dp[ni1][nj1][ni2][nj2][x2][y2] = dp[i1][j1][i2][j2][x][y]+1;
                q.push({ni1,nj1,ni2,nj2,x2,y2});
            }
        }
    }
    return (ans==inf?-1:ans);
}

int brute(int n, int m, vector<string> grid) {
    map<vector<string>, int> mp;
    queue<vector<string>> q;
    q.push(grid);
    vector<int> a = {1, -1, 0, 0, 0, 0, 1, -1};
    vector can(4, vector(n+2, vector(m+2, 0)));
    // down, up, right, left
    mp[grid] = 0;
    while (!q.empty()) {
        auto g = q.front(); q.pop();
        int x, y;
        int bad = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (g[i][j] == 'T') x = i, y = j;
                if (g[i][j] == '#') bad = 1;
            }
        }
        if (!bad) return mp[g];
        for (int i = 0; i < 4; ++i) {
            vector<string> g2(n, string(m, '.'));
            g2[x][y] = 'T';
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < m; ++k) {
                    int jj = j + a[i], kk = k + a[i+4];
                    if (min(jj, kk) >= 0 and jj < n and kk < m and g[jj][kk] == '#') g2[j][k] = '#';
                }
            }
            if (g2[x][y] == 'T' and mp.count(g2) == false) mp[g2] = mp[g]+1, q.push(g2);
        }
    }
    return -1;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    int n, m; cin >> n >> m;
    vector<string> rubens(n);
    for (auto& x : rubens) cin >> x;
    cout << brute(n, m, rubens) << endl;
#else
    int t = 1;
    while (true) {
    int n = rnd(1, 4), m = rnd(1, 4);
        vector<string> grid(n, string(m, '.'));
        grid[rnd(0, n-1)][rnd(0, m-1)] = 'T';
        for (auto& s : grid) for (auto& c : s) {
            if (c != 'T' and rnd(0, 3) == 3) c = '#';
        }
        int my = solve(n, m, grid), ans = brute(n, m, grid);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << m << endl;
            for (auto x : grid) cout << x << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

