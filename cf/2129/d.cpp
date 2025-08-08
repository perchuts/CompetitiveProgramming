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
int dp[105][105][20][20], lim[105];

void solve() {
    int n; cin >> n;
    vector<int> s(n);
    for (auto& x : s) cin >> x;
    vector<int> ss; ss.pb(0); for (auto x : s) ss.pb(x); ss.pb(0); s = ss, n += 2;
    for (int i = 1; i <= n; ++i) lim[i] = 1 + lim[i/2];
    vector ncr(n+1, vector(n+1, 0LL));
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (i == j or j == 0) ncr[i][j] = 1;
            else ncr[i][j] = (ncr[i-1][j] + ncr[i-1][j-1]) % mod;
        }
    }
    for (int l = n-1; ~l; --l) {
        for (int r = l; r < n; ++r) {
            for (int a = 0; a <= lim[r-l]; ++a) {
                for (int b = 0; b <= lim[r-l]; ++b) { 
                    if (r <= l+1) { dp[l][r][a][b] = (a == b and b == 0); continue; }
                    dp[l][r][a][b] = 0;
                    for (int k = l+1; k < r; ++k) {
                        for (int esq = 0; esq <= lim[k-l]; ++esq) {
                            for (int dir = 0; dir <= lim[r-k]; ++dir) {
                                if (s[k] != -1 and esq+dir != s[k]) continue;
                                int aa = a, bb = b;
                                if (l != 0 or r != n-1) {
                                    if ((k-l <= r-k and l != 0) or r == n-1) aa--;
                                    else bb--;
                                } else {
                                    if (k-l <= r-k) aa--;
                                    else bb--;
                                }
                                if (min(aa, bb) < 0) continue;
                                int ways = dp[l][k][aa][esq] * dp[k][r][dir][bb] % mod * ncr[r-l-2][k-l-1] % mod;
                                dp[l][r][a][b] += ways;
                                if (dp[l][r][a][b] >= mod) dp[l][r][a][b] -= mod;
                            }
                        }
                    }
                }
            }
        }
    }
    //auto get = [&] (int l, int r, int a, int b) {
    //    cout << "l = " << l << " r = " << r << " a = " << a << " b = " << b << " dp = " << dp[l][r][a][b] << endl;
    //};
    int ans = (dp[0][n-1][0][1] + dp[0][n-1][1][0]) % mod;
    cout << ans << endl;

}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
