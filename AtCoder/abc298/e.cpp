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
    int n, a, b, p, q; cin >> n >> a >> b >> p >> q;
    vector dp(2, vector(n+1, vector(n+1, 0)));
    for (int i = b; i < n; ++i) dp[0][n][i] = dp[1][n][i] = 1;
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            b = b * b % mod, e /= 2;
        }
        return ans;
    };
    int invp = fexp(p, mod-2);
    int invq = fexp(q, mod-2);
    for (int i = n-1; i >= a; --i) {
        for (int j = n-1; j >= b; --j) {
            for (int w = 1; w <= p; ++w) dp[0][i][j] = (dp[0][i][j] + dp[1][min(n, i+w)][j]) % mod; 
            for (int w = 1; w <= q; ++w) dp[1][i][j] = (dp[1][i][j] + dp[0][i][min(j+w, n)]) % mod; 
            dp[0][i][j] = dp[0][i][j] * invp % mod;
            dp[1][i][j] = dp[1][i][j] * invq % mod;
        }
    }
    cout << dp[0][a][b] << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
