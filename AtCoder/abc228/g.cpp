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
    int n, m, k; cin >> n >> m >> k;
    vector<vector<int>> grid(n, vector<int>(m));
    for (auto& x : grid) for (auto& y : x) {
        char c; cin >> c;
        y = c - '0';
    }
    vector<int> dp(1024);
    vector<vector<int>> row(1<<n, vector<int>(10)), col(1<<m, vector<int>(10));
    for (int mask = 1; mask < (1<<n); ++mask) {
        for (int i = 0; i < n; ++i) {
            if (mask >> i & 1) {
                for (int j = 0; j < m; ++j) row[mask][grid[i][j]] |= (1 << j);
            }
        }
    }
    for (int mask = 1; mask < (1<<m); ++mask) {
        for (int j = 0; j < m; ++j) {
            if (mask >> j & 1) {
                for (int i = 0; i < n; ++i) col[mask][grid[i][j]] |= (1 << i);
            }
        }
    }
    auto add = [&] (int& x, int y) {
        x += y;
        if (x >= mod) x -= mod;
    };
    dp[(1<<n)-1] = 1; 
    for (int turn = 0; turn < 2 * k; ++turn) {
        vector<int> ndp(1024);
        if (turn&1) {
            for (int i = 1; i < (1 << m); ++i) {
                for (int d = 1; d <= 9; ++d) {
                    add(ndp[col[i][d]], dp[i]);
                }
            }
        } else {
            for (int i = 1; i < (1 << n); ++i) {
                for (int d = 1; d <= 9; ++d) {
                    add(ndp[row[i][d]], dp[i]);
                }
            }
        }
        swap(dp, ndp);
    }
    int ans = 0;
    for (auto x : dp) add(ans, x);
    add(ans, mod-dp[0]);
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
