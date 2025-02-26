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
    if (n == 1) {
        cout << 1 << endl;
        exit(0);
    }
    vector<int> dp(n+1);
    dp[0] = 1;
    int ps = 1;
    for (int i = 1; i <= n; ++i) {
        dp[i] = (ps - (i == 1 ? 0 : dp[i-2]) + mod) % mod;
        ps = (ps + dp[i]) % mod;
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int falta = n - i;
        if (falta == 1) ans = (ans + (n-1) * dp[i]) % mod;
        else if (falta == 0) ans = (ans + dp[i]) % mod;
        else {
            ans = (ans + (n-1) * (n-1) % mod * dp[i]) % mod;
            ans = (ans + (n-falta+1) * dp[i]) % mod;
        }
    }
    ans = (ans + (n-1) * (n-1) + 1) % mod;
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
