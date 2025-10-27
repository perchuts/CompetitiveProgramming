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



int dp[2][200][200][200];

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n), gr(n);
    for (int i = 0; i < 200; ++i) for (int j = 0; j < 200; ++j) for (int k = 0; k < 200; ++k) dp[0][i][j][k] = dp[1][i][j][k] = -1e18;
    for (int j = 0; j < n; ++j) dp[0][0][j][0] = 0;
    const int T = 300 * 300;
    vector dps(n, vector(T, 0LL));
    vector<int> c(n), w(n);
    for (int i = 0; i < n; ++i) cin >> c[i] >> w[i];
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v);
    }
    for (int i = 0; i < n; ++i) {
        int cc = c[i], cw = w[i];
        for (int pot = 0; pot < 8; ++pot) {
            // usar exatamente isso
            for (int j = 0; j < n; ++j) {
                if (j == i) continue;
                if (w[i] * c[j] > w[j] * c[i] or (w[i] * c[j] == w[j] * c[i] and pair(c[i], i) < pair(c[j], j))) continue;
                for (int k = 0, md = (-cc + 1000 * 1000 * c[j]) % c[j]; k < c[j]; ++k, md++) {
                    if (md == c[j]) md = 0;
                    int need = 0;
                    if (k < cc) need = (cc - k + c[j] - 1) / c[j];
                    int delta = cw - need * w[j];
                    ckmax(dp[0][i][j][k], delta + dp[0][i][j][md]);
                    ckmax(dp[1][i][j][k], delta + dp[1][i][j][md]);
                }
            }
            cc += cc, cw += cw;
        }
        for (int j = 0; j < c[i]; ++j) dp[1][i][i][j] = dp[0][i][i][j];

        for (int j = 1; j < T; ++j) {
            ckmax(dps[i][j], dps[i][j-1]);
            if (j >= c[i]) ckmax(dps[i][j], dps[i][j-c[i]] + w[i]);
        }
        for (auto v : g[i]) {
            for (int j = 0; j < T; ++j) ckmax(dps[v][j], dps[i][j]);
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < c[j]; ++k) {
                    ckmax(dp[0][v][j][k], dp[0][i][j][k]);
                    ckmax(dp[1][v][j][k], dp[1][i][j][k]);
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) for (int k = 1; k < c[j]; ++k) ckmax(dp[1][i][j][k], dp[1][i][j][k-1]);
    int q; cin >> q;
    while (q--) {
        int p, r; cin >> p >> r; --p;
        if (r < T) {
            cout << dps[p][r] << endl;
            continue;
        }
        int opt = 0;
        for (int i = 0; i <= p; ++i) {
            int best = max((r / c[i]) * w[i] + dp[1][p][i][r%c[i]], (r / c[i]) * w[i] + dp[1][p][i][c[i]-1] - w[i]);
            ckmax(opt, (r / c[i]) * w[i] + dp[1][p][i][r%c[i]]);
            ckmax(opt, (r / c[i]) * w[i] + dp[1][p][i][c[i]-1] - w[i]);
        }
        cout << opt << endl;
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
