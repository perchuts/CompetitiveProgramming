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
    int n; cin >> n;
    vector<vector<int>> dp(n+1, vector<int>(n+1));
    vector<vector<int>> ncr(n+1, vector<int>(n+1));
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (j == 0 or j == i) ncr[i][j] = 1;
            else ncr[i][j] = (ncr[i-1][j] + ncr[i-1][j-1]) % mod;
        }
    }
    vector<int> pot(n*n+1, 1);
    for (int i = 1; i <= n*n; ++i) pot[i] = 2 * pot[i-1] % mod;
    dp[1][1] = 1;
    for (int i = 2; i <= n; ++i) {
        dp[i][1] = pot[i*(i-1)/2];
        for (int j = 2; j <= i; ++j) {
            for (int k = 1; k < i; ++k) dp[i][j] = (dp[i][j] + ncr[i][k] * dp[k][1] % mod * dp[i-k][j-1]) % mod;
            dp[i][1] = (dp[i][1] - dp[i][j] + mod) % mod;
        }
    }
    for (int i = 1; i <= n; ++i) cout << dp[n][i] << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
