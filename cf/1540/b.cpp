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
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v);
        g[v].pb(u);
    }
    vector<vector<int>> pre(n, vector<int>(n));
    for (int i = 1; i < n; ++i) pre[0][i] = 1;
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    for (int i = 1; i < n; ++i) for (int j = 1; j < n; ++j) pre[i][j] = (mod+1)/2 * (pre[i-1][j] + pre[i][j-1]) % mod;
    int ans = 0;
    vector<int> par(n), imp(n);
    for (int i = 0; i < n; ++i) {
        auto dfs = [&] (auto&& self, int u, int p) -> void {
            par[u] = p;
            for (auto v : g[u]) {
                if (v == p) continue;
                self(self, v, u);
            }
        };
        dfs(dfs, i, i);
        for (int j = i + 1; j < n; ++j) {
            for (int k = 0; k < n; ++k) imp[k] = 0;
            int cur = j;
            int D = 0;
            while (cur != i) imp[cur] = 1, cur = par[cur], D++;
            imp[i] = 1;
            auto dfs2 = [&] (auto&& self, int u, int p, int du) -> void {
                // e se eu comecar por esse vertice, qual a chance de j chegar antes de i?
                ans += pre[D-du][du];
                if (ans >= mod) ans -= mod;
                for (auto v : g[u]) {
                    if (v == p) continue;
                    self(self, v, u, du+imp[v]);
                }
            };
            dfs2(dfs2, i, i, 0);
        }
    }
    ans = ans * fexp(n, mod-2) % mod;
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
