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
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}


int solve(int n, int m, vector<ii> ranges) {
    vector<int> dp(n+1);
    vector<int> c(n+2);
    for (auto [l, r] : ranges) c[l]++, c[r+1]--;
    for (int i = 2; i <= n; ++i) c[i] += c[i-1];
    // quero updatar c[j]'s.
    // start by doing dp[i] * c[i+1]
    // look at ranges with r[j] = i
    // for each one of those, do -= dp[k] for all l[j]-1 <= k <= r[j]
    vector<vector<int>> pr(n+1, vector<int>(4));
    vector<int> sum(4);
    vector<vector<int>> fins(n+1);
    pr[0][0] = dp[0] = 1;
    sum[0] = c[1];
    for (int j = 0; j < m; ++j) fins[ranges[j].second].pb(j);
    for (int i = 1; i <= n; ++i) {
        dp[i] = dp[i-1];
        int other = (i + 2) % 4;
        dp[i] = (dp[i] + sum[other] - sum[i%4] + mod) % mod;
        //for (int w = 0; w < 4; ++w) cout << sum[w] << ' ';
        //cout << endl;
        for (auto j : fins[i]) {
            auto [lx, rx] = ranges[j];
            --lx;
            for (int w = 0; w < 4; ++w) { 
                int lose = pr[rx-1][w] - (lx ? pr[lx-1][w] : 0);
                lose = (lose + mod) % mod;
                sum[w] = (sum[w] + mod - lose) % mod;
            }
        }
        for (int w = 0; w < 4; ++w) pr[i][w] = pr[i-1][w];
        pr[i][i%4] = (pr[i][i%4] + dp[i]) % mod;
        sum[i%4] = (sum[i%4] + c[i+1] * dp[i]) % mod;
    }
    //cout << endl;
    return dp[n];
}
int brute(int n, int m, vector<ii> ranges) {
    vector<vector<int>> dp(n+1, vector<int>(m+1));
    vector<int> S(n+1);
    dp[0][0] = 1;
    S[0] = 1;
    for (int i = 1; i <= n; ++i) {
        dp[i][0] = dp[i-1][0];
        for (int j = 1; j <= m; ++j) {
            dp[i][0] = (dp[i][0] + dp[i-1][j]) % mod;
            auto [l, r] = ranges[j-1];
            if (l <= i-1 and i <= r) dp[i][j] = (S[i-2] - dp[i-2][j] + mod) % mod;
        }
        for (auto x : dp[i]) S[i] = (S[i] + x) % mod;
    }
    return S[n];
}

int32_t main() {_
#ifndef gato
    int n, m; cin >> n >> m;
    vector<ii> ranges(m);
    for (auto& [x, y] : ranges) cin >> x >> y;
    cout << solve(n, m, ranges) << endl;
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
