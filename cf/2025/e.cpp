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

inline void add(int& x, int y) {
    x += y;
    if (x >= mod) x -= mod;
}

void solve() {
    int n, m; cin >> n >> m;
    vector<int> dp1(m+1);
    dp1[0] = 1;
    for (int i = 1; i <= m; ++i) {
        vector<int> ndp1(m+1);
        for (int j = 0; j <= m; ++j) {
            // can do
            if (j != m) add(ndp1[j+1], dp1[j]);
            if (j != 0) add(ndp1[j-1], dp1[j]);
        }
        swap(dp1, ndp1);
    }
    if (n == 1) {
        cout << dp1[0] << endl;
        return;
    }
    // agora faz um fexp sobre esses bichos
    auto dp = dp1;
    for (int turns = 0; turns < n-2; ++turns) {
        vector<int> ndp(m+1);
        for (int i = 0; i <= m; ++i) {
            for (int j = 0; i + j <= m; ++j) {
                ndp[i+j] = (ndp[i+j] + dp[i] * dp1[j]) % mod;
            }
        }
        swap(dp, ndp);
    }
    int ans = 0;
    for (int i = 0; i <= m; ++i) ans = (ans + dp1[i] * dp[i]) % mod;
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
