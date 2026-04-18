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

void solve() {
    int n, m, t; cin >> n >> m >> t; t++;
    vector<vector<int>> grid(n+1, vector<int>(m+1)), ps = grid;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) cin >> grid[i][j], ps[i][j] = ps[i-1][j] + ps[i][j-1] + grid[i][j] - ps[i-1][j-1];
    vector ss(n+1, vector(m+1, vector(n+1, vector(m+1, -1LL))));
    for (int x1 = 1; x1 <= n; ++x1) {
        for (int x2 = x1; x2 <= n; ++x2) {
            for (int y1 = 1; y1 <= m; ++y1) {
                for (int y2 = y1; y2 <= m; ++y2) {
                    ss[x1][y1][x2][y2] = ps[x2][y2] - ps[x2][y1-1] - ps[x1-1][y2] + ps[x1-1][y1-1];
                }
            }
        }
    }
    vector dp(n+1, vector(m+1, vector(n+1, vector(m+1, vector(t+1, inf*inf)))));
    auto calc = [&] (int lb) {
        for (int x1 = n; x1; --x1) {
            for (int y1 = m; y1; --y1) {
                for (int x2 = x1; x2 <= n; ++x2) {
                    for (int y2 = y1; y2 <= m; ++y2) {
                        dp[x1][y1][x2][y2][1] = ss[x1][y1][x2][y2];
                        if (dp[x1][y1][x2][y2][1] < lb) dp[x1][y1][x2][y2][1] = inf*inf;
                    }
                }
            }
        }
        for (int cc = 2; cc <= t; ++cc) {
            for (int x1 = n; x1; --x1) {
                for (int y1 = m; y1; --y1) {
                    for (int x2 = x1; x2 <= n; ++x2) {
                        for (int y2 = y1; y2 <= m; ++y2) {
                            if (cc > (x2-x1+1)*(y2-y1+1)) continue;
                            int& eu = dp[x1][y1][x2][y2][cc];
                            eu = inf*inf;
                            for (int cut = 1; cut < cc; ++cut) {
                                for (int h = x1; h < x2; ++h) ckmin(eu, max(dp[x1][y1][h][y2][cut], dp[h+1][y1][x2][y2][cc-cut]));
                                for (int l = y1; l < y2; ++l) ckmin(eu, max(dp[x1][y1][x2][l][cut], dp[x1][l+1][x2][y2][cc-cut]));
                            }
                        }
                    }
                }
            }
        }
        return dp[1][1][n][m][t];
    };
    int ans = 1e18;
    for (int x1 = 1; x1 <= n; ++x1) {
        for (int x2 = x1; x2 <= n; ++x2) {
            for (int y1 = 1; y1 <= m; ++y1) {
                for (int y2 = y1; y2 <= m; ++y2) {
                    ckmin(ans, calc(ss[x1][y1][x2][y2]) - ss[x1][y1][x2][y2]);
                }
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
