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

void solve() {
    int n, k; cin >> n >> k;
    vector dp(k+1, vector(5001, -inf));
    dp[0][0] = 0;
    for (int t = 0; t < n; ++t) {
        int p2 = 0, p5 = 0;
        long long x; cin >> x;
        while (x % 2 == 0) p2++, x /= 2;
        while (x % 5 == 0) p5++, x /= 5;
        auto ndp = dp;
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j+p5 <= 5000; ++j) {
                ckmax(ndp[i+1][j+p5], dp[i][j] + p2);
            }
        }
        swap(dp, ndp);
    }
    int ans = 0;
    for (int i = 0; i <= 5000; ++i) ckmax(ans, min(i, dp[k][i]));
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
