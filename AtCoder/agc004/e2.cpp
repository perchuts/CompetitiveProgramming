#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
short int dp[100][100][100][100];
short int dpr[100][100], dpc[100][100];
void solve() {
    int n, m; cin >> n >> m;
    vector<string> grid(n);
    ii z;
    for (auto& x : grid) cin >> x;
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) if (grid[i][j] == 'E') z = {i,j};
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
        dpr[i][j] = (i ? dpr[i-1][j] : 0) + (grid[i][j] == 'o');
        dpc[i][j] = (j ? dpc[i][j-1] : 0) + (grid[i][j] == 'o');
    }
    memset(dp, -n*m, sizeof(dp));
    // dp[l1,r1,l2,r2] >= dp[l1, r1-1, l2, r2] + valid(r1, l2...r2)
    auto [sx, sy] = z;
    dp[sx][sx][sy][sy] = 0;
    for (int l1 = n-1; ~l1; --l1) {
        for (int r1 = l1; r1 < n; ++r1) {
            for (int l2 = m-1; ~l2; --l2) {
                for (int r2 = l2; r2 < m; ++r2) {
                    if (r1 != l1) {
                        // go up last
                        if (l1 - (r1-sx) >= 0) {
                            // l2, r2 goes to
                            // l2-(r2-sy), r2+(sy-l2)
                            // l2 <= i <= r2
                            // 0 <= i-(r2-sy)
                            // i >= r2-sy
                            // i+(sy-l2) < m
                            // i < m-sy+l2
                            // i <= m-sy+l2-1
                            int bl = max(l2, r2-sy);
                            int br = min(r2, m-sy+l2-1);
                            if (bl <= br)
                                ckmax(dp[l1][r1][l2][r2], dp[l1+1][r1][l2][r2] + dpr[l1][br] - (bl ? dpr[l1][bl-1] : 0));
                        }
                        // go down last
                        if (r1 + (sx-l1) < n) {
                            // l2, r2 goes to
                            // l2-(r2-sy), r2+(sy-l2)
                            // l2 <= i <= r2
                            // 0 <= i-(r2-sy)
                            // i >= r2-sy
                            // i+(sy-l2) < m
                            // i < m-sy+l2
                            // i <= m-sy+l2-1
                            int bl = max(l2, r2-sy);
                            int br = min(r2, m-sy+l2-1);
                            if (bl <= br)
                                ckmax(dp[l1][r1][l2][r2], dp[l1][r1-1][l2][r2] + dpr[r1][br] - (bl ? dpr[r1][bl-1] : 0));
                        }
                    }
                    if (r2 != l2) {
                        // go left last
                        if (l2 - (r2-sy) >= 0) {
                            // l1, r1 goes to
                            // l1-(r1-sx), r1+(sx-l1)
                            // i-(r1-sx) >= 0
                            // i+(sx-l1) <= n-1
                            int bl = max(l1, r1-sx);
                            int br = min(r1, n-1-sx+l1);
                            if (bl <= br) ckmax(dp[l1][r1][l2][r2], dp[l1][r1][l2+1][r2] + dpc[l2][br] - (bl ? dpc[l2][bl-1] : 0));
                        }
                        // go right last
                        if (r2 + (sy-l2) < m) {
                            // l1, r1 goes to
                            // l1-(r1-sx), r1+(sx-l1)
                            // i-(r1-sx) >= 0
                            // i+(sx-l1) <= n-1
                            int bl = max(l1, r1-sx);
                            int br = min(r1, n-1-sx+l1);
                            if (bl <= br) ckmax(dp[l1][r1][l2][r2], dp[l1][r1][l2][r2-1] + dpc[r2][br] - (bl ? dpc[r2][bl-1] : 0));
                        }
                    }
                }
            }

        }
    }

    cout << dp[0][n-1][0][m-1] << endl;
    cout << dp[2][2][2][3] << endl;

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
