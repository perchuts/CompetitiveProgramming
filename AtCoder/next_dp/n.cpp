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
using ld = long double;
void solve() {
    int n, q; cin >> n >> q;
    vector<int> dp(n+1);
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        for (int j = i; j <= n; ++j) ckmax(dp[j], dp[j-i] + x);
    }
    vector<int> ord(n); iota(all(ord), 1);
    sort(all(ord), [&] (int i, int j) { return dp[i]*j > dp[j]*i; });
    int opt = ord[0];
    dp.resize(n*opt+1);
    for (int i = n + 1; i <= n * opt; ++i) {
        int z = 3 * n * n / i + 1; ckmin(z, n);
        for (int j = 0; j < z; ++j) ckmax(dp[i], dp[i-ord[j]] + dp[ord[j]]);
    }
    while (q--) {
        int x; cin >> x;
        if (x <= n * opt) cout << dp[x] << endl;
        else {
            int w = x/opt-n+1;
            cout << dp[x-w*opt] + w*dp[opt] << endl;
        }
    }
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
