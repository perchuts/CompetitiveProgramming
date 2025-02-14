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
    vector dp(n+1, vector(4, vector(4, vector(4, 0LL))));
    dp[0][0][0][0] = 1;
    // t == 0
    // a == 1
    // g == 2
    // c == 3
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                for (int l = 0; l < 4; ++l) {
                    for (int m = 0; m < 4; ++m) {
                        if (k == 1 and l == 2 and m == 3) continue;
                        if (k == 2 and l == 1 and m == 3) continue;
                        if (k == 1 and l == 3 and m == 2) continue;
                        if (j == 1 and k == 2 and m == 3) continue;
                        if (j == 1 and l == 2 and m == 3) continue;
                        dp[i][k][l][m] = (dp[i][k][l][m] + dp[i-1][j][k][l]) % mod;
                    }
                }
            }
        }
    }
    for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) for (int k = 0; k < 4; ++k) ans += dp[n][i][j][k];
    ans %= mod;
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
