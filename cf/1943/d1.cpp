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

int p;

inline void add(int& x, int y) {
    x += y;
    if (x >= p) x -= p;
}

void solve() {
    int n, k; cin >> n >> k >> p;
    vector<vector<int>> dp(k+1, vector<int>(k+1));
    dp[0][0] = 1;
    for (int z = 0; z < n; ++z) {
        vector<vector<int>> ndp(k+1, vector<int>(k+1)), row = ndp;
        for (int i = 0; i <= k; ++i) {
            for (int j = 0; i+j <= k; ++j) {
                // dp[i][j] manda pra ndp[i+j-z][0], 1 <= z <= i
                add(row[j][0], dp[i][j]);
                add(row[i+j][0], p-dp[i][j]);
                // balanco em j, quantos abres tem em w
                add(ndp[i+j][0], dp[i][j]);
                // dp[i][j] manda pra ndp[i+j][z], 0 <= z <= k-i-j
            }
        }
        for (int i = 0; i <= k; ++i) {
            for (int j = 0; i + j <= k; ++j) {
                if (i) add(row[i][j], row[i-1][j]);
                if (j) add(ndp[i][j], ndp[i][j-1]);
            }
        }
        for (int i = 0; i <= k; ++i) {
            for (int j = 0; i + j <= k; ++j) {
                add(ndp[i][j], row[i][j]);
            }
        }
        swap(dp, ndp);
    }
    int ans = 0;
    for (int i = 0; i <= k; ++i) add(ans, dp[i][0]);
    cout << ans << endl;
}

int32_t main() {_
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
