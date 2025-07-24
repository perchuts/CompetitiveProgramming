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
    int n, k; cin >> n >> k;
    vector<int> p(n), q(n);
    for (auto& x : p) cin >> x, x = n + 1 - x;
    for (auto& x : q) cin >> x, x = n + 1 - x;
    vector<vector<int>> dp(n, vector<int>(n+1));
    vector<vector<int>> tr(n, vector<int>(n));
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) for (int w = 0; w < n; ++w) if (p[w] > p[j] and q[w] > q[j] and q[w] < q[i]) tr[i][j]++;
    vector<int> ind(n); iota(all(ind), 0); sort(all(ind), [&] (int x, int y) { return p[x] < p[y]; });
    auto add = [&] (int& x, int y) {
        x += y;
        if (x >= mod) x -= mod;
    };
    int ans = 0;
    for (auto i : ind) {
        int dom = 0;
        for (int j = 0; j < n; ++j) {
            if (p[j] >= p[i] and q[j] >= q[i]) dom++;
            if (p[j] >= p[i] or q[j] <= q[i]) continue;
            for (int use = 1; use + tr[j][i] + 1 <= n; ++use) add(dp[i][use+tr[j][i]+1], dp[j][use]);
        }
        add(dp[i][dom], 1);
        add(ans, dp[i][k]);
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
