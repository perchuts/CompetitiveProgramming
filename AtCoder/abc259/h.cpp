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

void solve() {
    int n; cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (auto& x : a) for (auto& y : x) cin >> y, --y;
    vector<vector<ii>> occ(n*n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            occ[a[i][j]].pb({i, j});
        }
    }
    vector<vector<int>> dp(n+1, vector<int>(n+1));
    auto add = [&] (int& x, int y) {
        x += y;
        if (x >= mod) x -= mod;
    };
    auto solve = [&] (int x) {
        int ret = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                dp[i][j] = dp[i-1][j];
                add(dp[i][j], dp[i][j-1]);
                if (a[i-1][j-1] == x) {
                    add(dp[i][j], 1);
                    add(ret, dp[i][j]);
                }
            }
        }
        return ret;
    };
    int ans = 0, N = 2*n+5;
    vector<vector<int>> ncr(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (i == j or j == 0) ncr[i][j] = 1;
            else ncr[i][j] = (ncr[i-1][j] + ncr[i-1][j-1]) % mod;
        }
    }
    for (int i = 0; i < n*n; ++i) {
        if (sz(occ[i]) >= n) add(ans, solve(i));
        else {
            for (int j = 0; j < sz(occ[i]); ++j) {
                auto [x1, y1] = occ[i][j];
                for (int k = j; k < sz(occ[i]); ++k) {
                    auto [x2, y2] = occ[i][k];
                    if (y1 > y2) continue;
                    add(ans, ncr[x2+y2-x1-y1][x2-x1]);
                }
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
