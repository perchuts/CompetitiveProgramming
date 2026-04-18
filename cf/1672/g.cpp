#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
    int n, m; cin >> n >> m;
    vector<string> grid(n);
    for (auto& x : grid) cin >> x;
    if (m % 2 == 0) {
        vector<string> gg(m, string(n, '1'));
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) gg[j][i] = grid[i][j];
        swap(n, m), swap(gg, grid);
    }
    vector<vector<int>> g(n+m);
    vector<int> row(n), col(m);
    int z = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '?') g[i].pb(n+j), g[n+j].pb(i), z++;
            if (grid[i][j] == '1') row[i] ^= 1, col[j] ^= 1;
        }
    }
    if (n % 2 == 0 and m % 2 == 0) { 
        int ans = 1;
        for (int i = 0; i < z; ++i) ans = (ans + ans) % mod;
        cout << ans << endl;
        return;
    }
    auto solve = [&] (vector<int> target) {
        vector<int> vis(n+m, -1);
        int cnt = 0;
        auto dfs = [&] (auto&& self, int u) -> int {
            cnt += target[u];
            int tot = 0;
            for (auto v : g[u]) {
                if (vis[v] > vis[u]) tot++;
                else if (vis[v] == -1) vis[v] = 1 + vis[u], tot += self(self, v);
            }
            return tot;
        };
        int ans = 1;
        for (int i = 0; i < n+m; ++i) {
            if (vis[i] == -1) {
                vis[i] = cnt = 0;
                int k = dfs(dfs, i);
                if (cnt % 2) return 0LL;
                for (int j = 0; j < k; ++j) ans = (ans + ans) % mod;
            }
        }
        return ans;
    };
    int ans = 0;
    if (n % 2 == 0) {
        vector<int> cnt(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == '?') cnt[i]++;
            }
        }
        for (int w = 0; w < 2; ++w) {
            int x = 1;
            for (int i = 0; i < n; ++i) {
                int want = w ^ row[i];
                if (want and cnt[i] == 0) x = 0;
                for (int j = 0; j < cnt[i]-1; ++j) x = x * 2 % mod;
            }
            ans = (ans + x) % mod;
        }
    } else {
        vector<int> target(n+m);
        for (int i = 0; i < n; ++i) target[i] = row[i];
        for (int j = 0; j < m; ++j) target[j+n] = col[j];
        ans = solve(target);
        for (int i = 0; i < n; ++i) target[i] = row[i] ^ 1;
        for (int j = 0; j < m; ++j) target[j+n] = col[j] ^ 1;
        ans = (ans + solve(target)) % mod;
    }
    cout << ans << endl;
}

int32_t main() {_
#ifndef gato
    solve();
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
