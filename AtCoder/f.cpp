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
    int l, r; cin >> l >> r;
    int msbl = -1, msbr = -1;
    int cur = l;
    while (cur) msbl++, cur /= 2;
    cur = r;
    while (cur) msbr++, cur /= 2;
    vector dp(2, vector(2, 0LL));
    for (int i = 59; ~i; --i) {
        vector ndp(2, vector(2, 0LL));
        int bl = l >> i & 1, br = r >> i & 1;
        if (br == 0 and bl == 0) {
            ndp[0][0] = (3 * dp[0][0] + dp[0][1]) % mod;
            ndp[0][1] = 2 * dp[0][1] % mod;
            ndp[1][0] = dp[1][0];
            ndp[1][1] = dp[1][1];
        } else if (br == 0 and bl == 1) {
            ndp[0][0] = (3 * dp[0][0]) % mod;
            ndp[0][1] = dp[0][1];
            ndp[1][0] = dp[1][0];
        } else if (br == 1 and bl == 0) {
            ndp[0][0] = (3 * dp[0][0] + dp[0][1] + dp[1][0]) % mod;
            ndp[0][1] = (2 * dp[0][1] + dp[1][1]) % mod;
            ndp[1][0] = (2 * dp[1][0] + dp[1][1]) % mod;
            ndp[1][1] = dp[1][1];
        } else {
            ndp[0][0] = (3 * dp[0][0] + dp[1][0]) % mod;
            ndp[0][1] = dp[0][1];
            ndp[1][0] = 2 * dp[1][0] % mod;
            ndp[1][1] = dp[1][1];
        }
        if (msbl <= i and i <= msbr) ndp[i==msbr][i==msbl] = (ndp[i==msbr][i==msbl]+1)%mod; 
        swap(dp, ndp);
    }
    int ans = (dp[0][0] + dp[0][1] + dp[1][0] + dp[1][1]) % mod;
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
