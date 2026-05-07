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

void solve() {
    int n, s, t; cin >> n >> s >> t;
    vector<int> a(n);
    int ss = 0;
    for (auto& x : a) cin >> x, ss += x;
    vector<vector<int>> dp(n+1, vector<int>(ss+1));
    dp[0][0] = 1;
    for (auto x : a) {
        vector<vector<int>> ndp(n+1, vector<int>(ss+1));
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= ss; ++j) {
                ndp[i][j] = dp[i][j];
                if (i and j >= x) ndp[i][j] += dp[i-1][j-x];
                ndp[i][j] %= mod;
            }
        }
        swap(dp, ndp);
    }
    int cs = s, ct = t;
    vector<vector<int>> dp2(2*n+1, vector<int>(2*ss+1));
    for (int i = 0; i <= n; ++i) for (int j = 0; j <= ss; ++j) {
        dp2[i][j] = dp[i][j];
    }
    dp[0][0] = 0;
    while (cs or ct) {
        vector<vector<int>> ndp2(2*n+1, vector<int>(2*ss+1));
        for (int i = cs % 2; i <= 2*n; i += 2) {
            for (int j = ct % 2; j <= 2*ss; j += 2) {
                ndp2[i/2][j/2] = dp2[i][j];
            }
        }
        // (n*ss)^2 * log
        // (4000) * log
        for (int i = n; ~i; --i) {
            for (int j = ss; ~j; --j) {
                for (int i2 = 0; i2 <= n; ++i2) {
                    for (int j2 = 0; j2 <= ss; ++j2) {
                        ndp2[i+i2][j+j2] = (ndp2[i+i2][j+j2] + dp[i2][j2] * ndp2[i][j]) % mod;
                    }
                }
            }
        }
        swap(dp2, ndp2);
        cs /= 2, ct /= 2;
    }
    cout << dp2[0][0] << endl;
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
