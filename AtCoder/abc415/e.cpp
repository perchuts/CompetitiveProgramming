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
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n, vector<int>(m));
    for (auto& x : g) for (auto& y : x) cin >> y;
    vector<int> cost(n+m-1);
    for (auto& x : cost) cin >> x;
    int l = 0, r = (n+m) * inf, ans = r;
    auto possible = [&] (int x) {
        vector<vector<int>> dp(n, vector<int>(m, -inf));
        dp[0][0] = x;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i) ckmax(dp[i][j], dp[i-1][j]);
                if (j) ckmax(dp[i][j], dp[i][j-1]);
                if (dp[i][j] == -inf) continue;
                dp[i][j] += g[i][j];
                if (dp[i][j] < cost[i+j]) dp[i][j] = -inf;
                else dp[i][j] -= cost[i+j];
            }
        }
        return (dp[n-1][m-1] >= 0);
    };
    while (l <= r) {
        int md = l + (r-l+1)/2;
        if (possible(md)) ans = md, r = md-1;
        else l = md+1;
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
