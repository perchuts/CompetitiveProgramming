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
    vector dp(4, vector(n+2, vector(m+2, 0LL)));
    vector<string> grid(n);
    for (auto& x : grid) cin >> x;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
         if (grid[i-1][j-1] == '.') {
            dp[0][i][j] = 1 + dp[0][i-1][j]; 
            dp[1][i][j] = 1 + dp[1][i][j-1]; 
         }
    }
    for (int i = n; i >= 1; --i) for (int j = m; j >= 1; --j) {
         if (grid[i-1][j-1] == '.') {
            dp[2][i][j] = 1 + dp[2][i+1][j]; 
            dp[3][i][j] = 1 + dp[3][i][j+1]; 
         }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) ckmax(ans, dp[0][i][j] + dp[1][i][j] + dp[2][i][j] + dp[3][i][j] - 3);
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
