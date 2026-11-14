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
    int n; cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (auto& x : a) for (auto& y : x) cin >> y;
    vector<vector<int>> dp_s(n, vector<int>(n, 1e18)), dp_d = dp_s;
    vector<vector<int>> cost(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) cost[i][j] += a[i][j-1];
            if (j < n-1) cost[i][j] += a[i][j+1];
        }
    }
    dp_s = dp_d = cost;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int add = 1e18;
            if (j > 0) ckmin(add, dp_s[i-1][j-1]);
            if (j < n-1) ckmin(add, dp_s[i-1][j+1]);
            dp_s[i][j] += add;
        }
    }
    for (int i = n-2; ~i; --i) {
        for (int j = 0; j < n; ++j) {
            int add = 1e18;
            if (j > 0) ckmin(add, dp_d[i+1][j-1]);
            if (j < n-1) ckmin(add, dp_d[i+1][j+1]);
            dp_d[i][j] += add;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int opt = 1e18;
            if (j > 0) ckmin(opt, dp_s[i][j-1] + dp_d[i][j-1] - cost[i][j-1]);
            if (j < n-1) ckmin(opt, dp_s[i][j+1] + dp_d[i][j+1] - cost[i][j+1]);
            cout << opt << " \n"[j==n-1];
        }
    }
    cout << endl;
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
