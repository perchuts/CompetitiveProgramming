#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<vector<int>> dp(n+1, vector<int>(k+1));
    dp[0][0] = 1;
    int M = 998244853;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= k; ++j) {
            dp[i][j] = dp[i-1][j];
            if (j-a[i-1] >= 0) dp[i][j] = (dp[i-1][j-a[i-1]] + dp[i][j]) % M;
        }
    }
    int ans = 0;
    vector<int> ndp(k+1);
    for (auto val : a) { 
        if (val >= k) continue;
        for (int j = 0; j < k; ++j) {
            if (j < val) ndp[j] = dp[n][j];
            else ndp[j] = (M+dp[n][j] - ndp[j-val])%M;
        }
        bool ok = 1;
        for (int j = k-val; j < k; ++j) ok &= (ndp[j] == 0);
        ans += ok;
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
