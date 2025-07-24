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

const int inf = 1e18;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int solve(int n, int m, vector<int> a, vector<int> b) {
    sort(all(a)), sort(all(b));
    int ans = inf;
    // x1+x2
    // y1+y2
    //
    return ans;
}

int solve2(int n, int m, vector<int> a, vector<int> b) {
    sort(all(a)), sort(all(b));
    vector dp(n+1, vector(m+1, vector(n+1, vector(m+1, inf))));
    dp[0][0][0][0] = 0;
    int ans = inf;
    for (int x1 = 0; x1 <= n; ++x1) {
        for (int x2 = 0; x2+x1 <= n; ++x2) {
            for (int y1 = 0; y1 <= m; ++y1) {
                for (int y2 = 0; y2 + y1 <= m; ++y2) {
                    auto& DP = dp[x1][y1][x2][y2];
                    if (x1) ckmin(DP, dp[x1-1][y1][x2][y2] + abs(2*y1-m)*a[x1+x2-1]);
                    if (x2) ckmin(DP, dp[x1][y1][x2-1][y2] + abs(2*y2-m)*a[x1+x2-1]);
                    if (y1) ckmin(DP, dp[x1][y1-1][x2][y2] + abs(2*x1-n)*b[y1+y2-1]);
                    if (y2) ckmin(DP, dp[x1][y1][x2][y2-1] + abs(2*x2-n)*b[y1+y2-1]);
                    if (x1 + x2 == n and y1 + y2 == m) ckmin(ans, DP);
                }
            }
        }
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int n, m; cin >> n >> m;
    vector<int> a(n), b(m);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    cout << solve(n, m, a, b) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 5), m = rnd(1, 5);
        vector<int> a(n), b(m);
        for (auto& x : a) x = rnd(1, 10);
        for (auto& x : b) x = rnd(1, 10:
        int my = solve(n, m, a, b), ans = brute(n, m, a, b);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << m << endl;
            for (auto x : a) cout << x << ' ';
            cout << endl;
            for (auto x : b) cout << x << ' ';
            cout << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
