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
    int n, k; cin >> n >> k;
    const int LIM = 180180;
    vector<vector<int>> ncr(n+1, vector<int>(n+1));
    for (int i = 0; i <= n; ++i) for (int j = 0; j <= i; ++j) {
        if (i == j or j == 0) ncr[i][j] = 1;
        else ncr[i][j] = (ncr[i-1][j] + ncr[i-1][j-1]) % mod;
    }
    vector<int> fat(n+1, 1);
    for (int i = 1; i <= n; ++i) fat[i] = i * fat[i-1] % mod;
    vector dp(n+1, vector(LIM+1, 0)), table = dp;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= LIM; ++j) table[i][j] = i * j / gcd(i, j);
    for (int i = 1; i <= n; ++i) dp[i][i] = fat[i-1];
    for (int i = 1; i <= n; ++i) {
        for (int lcm = 1; lcm <= LIM; ++lcm) {
            if (dp[i][lcm] == 0) continue;
            for (int j = 1; i + j <= n; ++j) {
                int lcm2 = table[j][lcm];
                dp[i+j][lcm2] = (dp[i+j][lcm2] + dp[i][lcm] * ncr[i+j-1][j-1] % mod * fat[j-1]) % mod;
            }
        }
    }
    int ans = 0;
    auto fexp = [&] (int b, int e) {
        int resp = 1;
        while (e) {
            if (e&1) resp = resp * b % mod;
            e /= 2, b = b * b % mod;
        }
        return resp;
    };
    for (int i = 1; i <= LIM; ++i) ans = (ans + dp[n][i] * fexp(i, k)) % mod;
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
