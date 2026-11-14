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

ld dp[5005][5005];

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb(v);
    }
    using ld = long double;
    vector<ld> dp2(n);
    dp2[n-1] = 1;
    for (int i = n-2; ~i; --i) {
        sort(begin(g[i]), end(g[i]), [&] (int x, int y) { return dp2[x] > dp2[y]; });
        int k = sz(g[i]);
        for (int j = 0; j < k; ++j) dp2[i] += dp2[g[i][j]] * dp[k][j];
        // |g[i]| = k
        // in a world of K objects, i am ordered at position X
        // success, picking before me, picking after me
        // (j-1)/k * dp[k-2][j-2] + (k-j-1)/k * dp[k-2][j-1]
        // dp[k][j] = 1/k + 
        // so it will be sum of dp[g[i][j]]*dp[k][j]
    }
    cout << fixed << setprecision(10) << dp2[0] << endl;
}

int32_t main() {_
    for (int i = 1; i <= 5000; ++i) {
        dp[i][0] = 1.0/i;
        for (int j = 1; j < i; ++j) {
            if (j >= 2) dp[i][j] += ld(j-1)/i * dp[i-2][j-2];
            if (j >= 1) dp[i][j] += ld(i-j-1)/i * dp[i-2][j-1];
        }
    }
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
