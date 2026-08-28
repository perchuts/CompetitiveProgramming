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

void solve() {
    int n; cin >> n;
    vector<int> v((1<<n));
    for (int i = 1; i < (1 << n); ++i) cin >> v[i];
    // conte as mascaras M tais que:
    // popcount(M & i) eh um bit ligado de V_i, pra  1<=i<2^n
    // entao V_i representa quais os tamanhos de intersecao que M pode ter com i
    vector<vector<int>> dp(1<<n, vector<int>(n+1));
    vector<int> tam(1<<n);
    // dp[i][j][k] = forcing first j bits to be equal to my mask, and the shift is k
    // lets try to free some bit j:
    //
    // dp[i][j][k] = dp[i-(1<<j)][j+1][k] and dp[i][j+1][k] if bit j is turned on
    // dp[i][j][k] = dp[i][j+1][k] and dp[i+(1<<j)][j+1][k+1] if bit j is turned off
    //
    // => dp[i][j] = dp[i-(1<<j)][j+1] and dp[i][j+1]
    // dp[i][j] = dp[i][j+1] and dp[i+(1<<j)][j+1]/2
    for (int i = 0; i < (1<<n); ++i) {
        tam[i] = __builtin_popcount(i);
        for (int j = 0; j <= tam[i]; ++j) {
            if (v[i] >> (tam[i]-j) & 1) dp[i][n] += (1 << j);
        }
    }
    dp[0][n] = 1;
    // remember mask 0!
    for (int j = n-1; ~j; --j) {
        for (int i = 0; i < (1 << n); ++i) {
            if (i >> j & 1) dp[i][j] = dp[i-(1<<j)][j+1] & dp[i][j+1];
            else dp[i][j] = (dp[i][j+1] & (dp[i+(1<<j)][j+1]>>1));
        }
    }
    vector<int> ans;
    bool ok = 1;
    for (int i = 1; i < (1 << n); ++i) ok &= (v[i] & 1);
    if (ok) ans.pb(0);
    for (int i = 1; i < (1 << n); ++i) if (dp[i][0] & 1) ans.pb(i);
    cout << sz(ans) << endl;
    for (auto x : ans) cout << x << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
