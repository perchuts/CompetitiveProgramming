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
const int maxn = 5e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int dp[maxn]; 

void solve() {
    int n; cin >> n;
    if (n % 2 == 0) {
        cout << -1 << endl;
        return;
    }
    cout << dp[n] << endl;
}

int32_t main() {_
    vector<vector<int>> div(maxn);
    for (int i = 3; i < maxn; ++i) {
        if (i % 2 == 0) continue;
        for (int j = 3*i; j < maxn; j += 2*i) div[j].pb(i);
    }
    dp[1] = 1;
    for (int i = 3; i < maxn; i += 2) {
        dp[i] = dp[i-2] + 1;
        for (auto d : div[i]) {
            // d1 * d2 * d3 * ... dk = i
            // dp[d1-2] + ... + dp[dk-2] + 1
            ckmin(dp[i], dp[d-2] + dp[i/d-2] + 1);
            ckmin(dp[i], dp[d-2] + dp[i/d]);
            // dp[d1-2] + {algo cujo produtorio eh igual a i/d1} + 1
        }
    }
    //for (int i = 1; i < 50; i += 2) {
    //    cout << i << ": " << dp[i] << endl;
    //}
    //cout << dp[499999] << endl;
    // \prod (2t[i] + 3)
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
