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
    int n, m; cin >> n >> m;
    vector<vector<int>> g(m, vector<int>(n));
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> g[j][i];
    if (n == 1) {
        int ans = inf;
        for (int j = 0; j < m-1; ++j) ckmin(ans, abs(g[j][0]-g[j+1][0]));
        cout << ans << endl;
        exit(0);
    }
    // dp[start][mask][last]
    // 2^n * n^3 => faz um max
    vector<int> a(n), b(n);
    vector<vector<int>> tr(n, vector<int>(n, inf));
    for (int i = 0; i < m; ++i) for (int j = 0; j < n; ++j) for (int k = j+1; k < n; ++k) ckmin(tr[j][k], abs(g[i][j] - g[i][k]));
    for (int j = 0; j < n; ++j) for (int k = j+1; k < n; ++k) tr[k][j] = tr[j][k];
    int ans = 0;
    for (int start = 0; start < n; ++start) {
        vector dp(1<<n, vector(n, -inf));
        dp[1<<start][start] = inf;
        for (int i = (1<<start); i < (1 << n); ++i) {
            int x1 = 0, x2 = 0;
            for (int j = 0; j < n; ++j) {
                if (i >> j & 1) a[x1++] = j;
                else b[x2++] = j;
            }
            for (int j = 0; j < x1; ++j) {
                for (int k = 0; k < x2; ++k) {
                    ckmax(dp[i + (1 << b[k])][b[k]], min(dp[i][a[j]], tr[a[j]][b[k]]));
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            if (i != start) {
                int worst = dp[(1<<n)-1][i];
                for (int j = 0; j < m-1; ++j) ckmin(worst, abs(g[j+1][start]-g[j][i]));
                ckmax(ans, worst);
            }
        }
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
