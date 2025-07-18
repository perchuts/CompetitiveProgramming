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
    int n, k, c; cin >> n >> k >> c;
    vector<int> dp(n+1, 0);
    dp[1] = c % mod;
    for (int i = 2; i <= n; ++i) {
        dp[i] = c * (c-1) % mod;
        dp[i] = (dp[i] + dp[i-1] - dp[max(1LL, i-k+1)] + mod) % mod;
        if (i >= k) dp[i] = (dp[i] + (c-1)*(dp[i - k + 1] - dp[1] + mod)) % mod;
        dp[i] = (dp[i] + dp[i-1]) % mod;
    }
    cout << dp[n] << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
