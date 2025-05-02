#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

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

int solve(int n, vector<int> a) {
    vector<vector<int>> dp(n+1, vector<int>(3, -1e18));
    dp[1][0] = a[0], dp[0][0] = 0;
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j < 3; ++j) dp[i][j] = a[i-1] + dp[i-2][j];
        if (i >= 3) ckmax(dp[i][1], dp[i-3][0] + a[i-1]), ckmax(dp[i][2], dp[i-3][1] + a[i-1]);
        if (i >= 4) ckmax(dp[i][2], dp[i-4][0] + a[i-1]);
    }
    if (n&1) return max({dp[n][2], dp[n][1], dp[n-1][0], dp[n-1][1], dp[n-2][0]});
    return max({dp[n][0], dp[n-1][0], dp[n][1]});
}
int brute(int n, vector<int> a) {
    vector<vector<int>> dp(n+1, vector<int>(n+1, -1e18));
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < n; ++j) {
            dp[i][j] = dp[i-1][j];
            if (j) ckmax(dp[i][j], dp[max(0LL, i-2)][j-1] + a[i-1]);
        }
    }
    return dp[n][n/2];
};
int32_t main(){_
#ifndef gato
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    cout << solve(n, a) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 100), lim = 10000;
        vector<int> a(n);
        for (auto& x : a) x = rnd(-lim, lim);
        int my = solve(n, a), ans = brute(n, a);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : a) cout << x << ' ';
            cout << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
