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
    int n, m, k; cin >> n >> m >> k;
    swap(n, m);
    // n = #1
    // m = #0
    int max_height = (n + m - 1) / (k - 1);
    vector dp(n+1, 0LL);
    dp[0] = 1;
    int ans = 0;
    for (int h = 1; h <= max_height; ++h) {
        vector ndp(n+1, 0LL);
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j < k and i + j <= n; ++j) {
                ndp[i + j] = (ndp[i + j] + dp[i]) % mod;
            }
        }
        //for (auto x : dp) cout << x << " ";
        //cout << endl;
        for (int i = n % (k-1); i <= n; i += k-1) {
            int qt_m = h * k - i - h + 1;
            if (qt_m % (k-1) == m % (k-1) and qt_m <= m) ans = (ans + ndp[i] - dp[i] + mod) % mod;
        }
        swap(dp, ndp);
        //cout << "ans = " << ans << endl;
    }
    cout << ans << endl;
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
