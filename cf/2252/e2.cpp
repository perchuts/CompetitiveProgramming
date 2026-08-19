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
    int k = 0;
    while ((1LL << (k+1)) <= n) ++k;
    auto add = [&] (int& x, int y) {
        x += y;
        if (x >= mod) x -= mod;
    };
    vector<array<int, 2>> dp(k+2);
    for (int i = k-1; ~i; --i) {

        if (n >> i & 1) {
            if ((n >> (i + 1) & 1) and i+1 == k) add(dp[i][1], 1);
            else add(dp[i][0], 1);
            // 000
            add(dp[i][0], dp[i+1][1]);
            add(dp[i][0], dp[i+1][0]);
            // 110, 101
            if (n >> (i+1) & 1) add(dp[i][0], dp[i+2][1]);
            else add(dp[i][1], dp[i+2][1]);
            add(dp[i][0], dp[i+2][0]);
            // 011, 101
            if (n >> (i+1) & 1) add(dp[i][1], dp[i+2][1]);
            else {}
            add(dp[i][0], dp[i+2][0]);
        } else {
            if ((3LL << i) < n) add(dp[i][0], 1);
            // 000
            add(dp[i][1], dp[i+1][1]);
            add(dp[i][0], dp[i+1][0]);
            // 110, 101
            if (n >> (i+1) & 1) add(dp[i][0], dp[i+2][1]);
            else {}
            add(dp[i][0], dp[i+2][0]);
            // 011, 101
            add(dp[i][0], dp[i+2][0]);

        }
    }
    cout << (dp[0][0] + dp[0][1]) % mod << endl;
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
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
