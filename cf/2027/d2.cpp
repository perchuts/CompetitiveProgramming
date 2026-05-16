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

void solve(int n, int m, vector<int> a, vector<int> b) {
    vector<vector<int>> dp(n+1, vector<int>(m+1, 1e18)), qtd(n+1, vector<int>(m+1));
    vector<set<iii>> sdp(m+1);
    vector<ii> aux(m+1);
    for (int i = 1; i <= m; ++i) dp[0][i] = 0, qtd[0][i] = 1, sdp[i].insert({0, 1, 1});
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (j != 1 and i != n and ckmin(dp[i][j], dp[i][j-1])) qtd[i][j] = qtd[i][j-1];
            aux[j].second += a[i-1];
            while (aux[j].second > b[j-1]) {
                if (dp[aux[j].first][j] == 1e18) {
                    aux[j].second -= a[aux[j].first++];
                    continue;
                }
                auto [val, qt, qt2] = *sdp[j].lower_bound(tuple(dp[aux[j].first][j], 0, 0));
                sdp[j].erase({val, qt, qt2});
                qt = (qt + mod - qtd[aux[j].first][j]) % mod;
                qt2--;
                if (qt2 != 0) sdp[j].insert({val, qt, qt2});
                aux[j].second -= a[aux[j].first++];
            }
            if (aux[j].first < i and !sdp[j].empty()) {
                auto [val, qt, qt2] = *sdp[j].begin();
                if (ckmin(dp[i][j], val + m - j)) qtd[i][j] = qt;
                else if (dp[i][j] == val + m - j) qtd[i][j] = (qtd[i][j] + qt) % mod;
            }
            if (dp[i][j] != 1e18) {
                auto it = sdp[j].lower_bound(tuple(dp[i][j], 0, 0));
                if (it != end(sdp[j]) and get<0>(*it) == dp[i][j]) {
                    auto [val, qt, qt2] = *it; sdp[j].erase({val, qt, qt2});
                    qt = (qt + qtd[i][j]) % mod;
                    sdp[j].insert({val, qt, qt2+1});
                } else {
                    sdp[j].insert({dp[i][j], qtd[i][j], 1});
                }
            }
        }
    }
    //for (int i = 1; i <= n; ++i) {
    //    for (int j = 1; j <= m; ++j) {
    //        cout << dp[i][j] << " \n"[j==m];
    //    }
    //}
    //cout << endl;
    //for (int i = 1; i <= n; ++i) {
    //    for (int j = 1; j <= m; ++j) {
    //        cout << qtd[i][j] << " \n"[j==m];
    //    }
    //}
    int opt = 1e18;
    int ways = 0;
    for (int j = 1; j <= m; ++j) {
        if (ckmin(opt, dp[n][j])) ways = qtd[n][j];
        else if (opt == dp[n][j]) ways = (ways + qtd[n][j]) % mod;
    }
    if (opt == 1e18) {
        cout << -1 << endl;
        return;
    }
    cout << opt << " " << ways << endl;
    //cout << opt << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        vector<int> a(n), b(m);
        for (auto& x : a) cin >> x;
        for (auto& x : b) cin >> x;
        solve(n, m, a, b);
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 3), m = rnd(1, 2);
        vector<int> a(n), b(m);
        for (auto& x : a) x = rnd(0, 10);
        for (auto& x : b) x = rnd(0, 10);
        sort(all(b));
        reverse(all(b));
        bool ok = 1;
        for (int i = 1; i < m; ++i) {
            if (b[i] == b[i-1]) ok = 0;
        }
        if (!ok) continue;
        cout << n << " " << m << endl;
        for (auto x : a) cout << x << " ";
        cout << endl;
        for (auto x : b) cout << x << " ";
        cout << endl;
        solve(n, m, a, b);
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
