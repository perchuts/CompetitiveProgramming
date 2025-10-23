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

const int inf = 1e9+1;
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
    vector<vector<int>> g(n);
    vector<int> w(n);
    for (int i = 1; i < n; ++i) {
        int j; cin >> j; --j;
        g[j].pb(i);
    }
    for (auto& x : w) cin >> x;
    vector<int> dp(n);
    auto dfs = [&] (auto&& self, int u) -> void { 
        vector<vector<int>> opt(2, vector<int>(w[u]+1, inf));
        opt[0][0] = 0;
        int turn = 0;
        for (auto v : g[u]) {
            self(self, v);
            for (int i = 0; i <= w[u]; ++i) {
                opt[turn^1][i] = inf;
                if (i >= w[v]) ckmin(opt[turn^1][i], opt[turn][i-w[v]] + dp[v]);
                if (i >= dp[v]) ckmin(opt[turn^1][i], opt[turn][i-dp[v]] + w[v]);
            }
            turn ^= 1;
        }
        dp[u] = inf;
        for (int i = 0; i <= w[u]; ++i) ckmin(dp[u], opt[turn][i]);
        if (dp[u] == inf) {
            cout << "IMPOSSIBLE" << endl;
            exit(0);
        }
    };
    dfs(dfs, 0);
    cout << "POSSIBLE" << endl;
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
