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
const int mod = (119<<23)+1;
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
    vector dp(n+1, vector(n+1, 0LL));
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            for (int k = 0; k * i <= j; ++k) dp[i][j] = (dp[i][j] + dp[i-1][j-k*i]) % mod;
            if (i == m) {
                if (j == 0) dp[i][j] = 0;
            } else if (i > m) {
                for (int k = 1; k * (i-m) <= j; ++k) dp[i][j] = (dp[i][j] - dp[i-m-1][j-k*(i-m)] + mod) % mod;
            }
        }
        // usando 3 elementos: (soma igual a 4)
        int ans = 0;
        for (int k = 1; k * i <= n; ++k) ans = (ans + dp[i-1][n-k*i]) % mod;
        cout << ans << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
