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

void solve(){
    int n, m; cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m)), b = a;
    for (auto& x : a) for (auto& y : x) cin >> y;
    for (auto& x : b) for (auto& y : x) cin >> y;
    int lim = 80*(n+m-1);
    vector dp(n+1, vector(m+1, vector(2*lim+69, false)));
    dp[0][1][lim] = dp[1][0][lim] = true;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int k = -80*(i+j-1); k <= 80*(i+j-1); ++k) {
                int val = a[i-1][j-1] - b[i-1][j-1], x = k+val, y = k-val;
                bool DP = 0;
                if (abs(y) <= 80*(i+j-2)) DP |= (dp[i-1][j][y+lim] or dp[i][j-1][y+lim]);
                if (abs(x) <= 80*(i+j-2)) DP |= (dp[i-1][j][x+lim] or dp[i][j-1][x+lim]);
                dp[i][j][k+lim] = DP;
            }
        }
    }
    for (int i = 0; ; ++i) {
        if (dp[n][m][i+lim] or dp[n][m][-i+lim]) {
            cout << i << endl;
            exit(0);
        }
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
