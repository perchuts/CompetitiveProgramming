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
    int n; cin >> n;
    vector<int> p(n);
    for (auto& x : p) cin >> x;
    vector dp(n+1, vector(n+1, vector(2, 0LL)));
    // dp[l][r][0] = subarvore obrigatoria
    // [1] = colecao de subarvores
    for (int l = n; l >= 1; --l) {
        for (int r = l; r <= n; ++r) {
            if (l == r) {
                dp[l][r][0] = dp[l][r][1] = 1;
                continue;
            }
            for (int k = l+1; k < r; ++k) {
                // ate onde vai a primeira subarvore
                if (p[l] < p[k]) dp[l][r][0] = (dp[l][r][0] + dp[l+1][k][0] * dp[k+1][r][1]) % mod;
                if (p[l-1] < p[k]) dp[l][r][1] = (dp[l][r][1] + dp[l][k][0] * dp[k+1][r][1]) % mod;
            }
            dp[l][r][0] = (dp[l][r][0] + dp[l+1][r][0]) % mod;
            if (p[l-1] < p[l]) dp[l][r][1] = (dp[l][r][1] + dp[l+1][r][1]) % mod;
            dp[l][r][1] = (dp[l][r][1] + dp[l][r][0]) % mod;
        }
    }
    cout << dp[1][n][0] << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
