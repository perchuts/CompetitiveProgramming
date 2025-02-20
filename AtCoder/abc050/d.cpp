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
    vector dp(61, vector(2, vector(2, 0LL)));
    dp[60][1][0] = 1;
    // dp[i][k] = defini os bits do i pra frente!
    for (int i = 59; ~i; --i) {
        int bit = n >> i & 1;
        // posso fazer ambos os bits aqui serem zero
        // 0 0
        dp[i][0][0] = dp[i+1][0][0];
        dp[i][0][1] = dp[i+1][0][0];
        if (bit) dp[i][1][1] = dp[i+1][1][0], dp[i][0][0] = (dp[i][0][0] + dp[i+1][1][0]) % mod;
        else dp[i][1][0] = dp[i+1][1][0];
        // 1 0
        dp[i][0][0] = (dp[i][0][0] + dp[i+1][0][1]) % mod;
        dp[i][0][1] = (dp[i][0][1] + dp[i+1][0][1]) % mod;
        if (!bit) dp[i][1][0] = (dp[i][1][0] + dp[i+1][1][1]) % mod;
        else dp[i][0][0] = (dp[i][0][0] + dp[i+1][1][1]) % mod, dp[i][1][1] = (dp[i][1][1] + dp[i+1][1][1]) % mod;
        
        // 0 1
        dp[i][0][0] = (dp[i][0][0] + dp[i+1][0][0]) % mod;
        dp[i][0][1] = (dp[i][0][1] + dp[i+1][0][1]) % mod;
        if (bit) dp[i][1][0] = (dp[i][1][0] + dp[i+1][1][0]) % mod, dp[i][0][1] = (dp[i][0][1] + dp[i+1][1][1]) % mod;
        else dp[i][1][1] = (dp[i][1][1] + dp[i+1][1][1]) % mod;
    }
    cout << (dp[0][1][0] + dp[0][0][0]) % mod << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
