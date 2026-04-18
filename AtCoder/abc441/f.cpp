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
    int n, m; cin >> n >> m;
    vector<int> p(n), v(n);
    for (int i = 0; i < n; ++i) cin >> p[i] >> v[i];
    vector<vector<int>> dp1(n+1, vector<int>(m+1)), dp2 = dp1;
    for (int i = 1; i <= n; ++i) {
        dp1[i] = dp1[i-1];
        for (int j = p[i-1]; j <= m; ++j) {
            ckmax(dp1[i][j], dp1[i-1][j-p[i-1]] + v[i-1]);
            ckmax(dp1[i][j], dp1[i][j-1]);
        }
    }
    for (int i = n; i; --i) {
        if (i != n) dp2[i] = dp2[i+1];
        for (int j = p[i-1]; j <= m; ++j) {
            ckmax(dp2[i][j], (i == n ? 0 : dp2[i+1][j-p[i-1]]) + v[i-1]);
            ckmax(dp2[i][j], dp2[i][j-1]);
        }
    }
    int opt = dp1[n][m];
    for (int i = 1; i <= n; ++i) {
        int mx = 0, mxn = 0;
        for (int j = 0; j <= m; ++j) {
            int other = m - j - p[i-1];
            if (other >= 0) ckmax(mx, dp1[i-1][j] + (i == n ? 0 : dp2[i+1][other]));
        }
        for (int j = 0; j <= m; ++j) {
            int other = m - j;
            if (other >= 0) ckmax(mxn, dp1[i-1][j] + (i == n ? 0 : dp2[i+1][other]));
        }
        mx += v[i-1];
        if (mxn < opt) {
            cout << "A";
        } else if (mx < opt) {
            cout << "C";
        } else {
            cout << "B";
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
