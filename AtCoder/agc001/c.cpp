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

void solve() {
    int n, k; cin >> n >> k; k++;
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    auto merge = [&] (vector<int> a, vector<int> b) {
        vector<int> res(min(k+1, max(sz(a), sz(b)+1)), n);
        res[0] = a[0] + b[0];
        for (int i = 1; i < sz(a); ++i) {
            for (int j = 0; j < min(sz(b), k + 1 - i); ++j) {
                ckmin(res[max(i, j+1)], a[i] + b[j]);
            }
        }
        return res;
    };
    vector<vector<int>> dp(n);
    int ans = n;
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        dp[u] = {1, 0};
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
            dp[u] = merge(dp[u], dp[v]);
        }
        for (auto x : dp[u]) ckmin(ans, x + n - dp[u][0]);
    };
    dfs(dfs, 0, 0);
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
