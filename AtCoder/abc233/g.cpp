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

void solve(){
    int n; cin >> n;
    vector<string> grid(n);
    for (auto& x : grid) cin >> x;
    vector dp(n+2, vector(n+2, vector(n+2, vector(n+2, n))));
    vector prow(n+1, vector(n+1, 0)), pcol(n+1, vector(n+1, 0));
    for (int i = 0; i <= n+1; ++i) for (int j = 0; j <= n+1; ++j) for (int k = 0; k <= n+1; ++k) for (int l = 0; l <= n+1; ++l) {
        if (i > k or j > l) dp[i][j][k][l] = 0;
    }
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) {
        prow[i][j] = prow[i][j-1] + (grid[i-1][j-1] == '#');
        pcol[i][j] = pcol[i-1][j] + (grid[i-1][j-1] == '#');
    }
    for (int i = n; i >= 1; --i) {
        for (int j = n; j >= 1; --j) {
            for (int k = i; k <= n; ++k) {
                for (int l = j; l <= n; ++l) {
                    dp[i][j][k][l] = max(k-i, l-j)+1;
                    for (int m = i; m <= k; ++m) {
                        if (prow[m][l]-prow[m][j-1] == 0) {
                            ckmin(dp[i][j][k][l], dp[i][j][m-1][l] + dp[m+1][j][k][l]);
                        }
                    }
                    for (int m = j; m <= l; ++m) {
                        if (pcol[k][m] - pcol[i-1][m] == 0) {
                            ckmin(dp[i][j][k][l], dp[i][j][k][m-1] + dp[i][m+1][k][l]);
                        }
                    }
                }
            }
        }
    }
    cout << dp[1][1][n][n] << endl;
    // can we have overlaps in any optimal solution?
    // ...........
    // ..xxx......
    // ..xxxxx....
    // ..xxxxx....
    // ....xxx..xx
    // .........xx
    // ...........
    // ......xx...
    // ...xx.xx...
    // ...xx......
    // ...........
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
