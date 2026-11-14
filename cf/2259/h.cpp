#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

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

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int solve(int n, vector<int> a) {
    bool tudo = 1;
    for (auto& x : a) tudo &= (x == -1);
    if (tudo) {
        int ans = 1;
        for (int i = 1; i < n; ++i) ans = (2 * ans + 1) % mod;
        return ans;
    }
    set<int> alive;
    for (int i = 0; i < n; ++i) alive.insert(i);
    vector<int> type(n, -1);
    vector<ii> edg;
    for (int i = 0; i < n; ++i) {
        if (a[i] == -1) continue;
        int l = i - a[i], r = i + a[i];
        {
            auto it = alive.upper_bound(l);
            while (it != end(alive) and (*it) < r) {
                int x = *it;
                type[x] = 0;
                it = next(it);
                alive.erase(x);
            }
        }
        edg.pb({l, r});
    }
    sort(all(edg), [&] (ii x, ii y) {
        int t1 = x.second-x.first, t2 = y.second-y.first;
        if (t1 == t2) return x.first < y.first;
        return t1 < t2;
    });
    edg.erase(unique(all(edg)), end(edg));
    vector<vector<int>> g(n);
    vector<ii> ee;
    for (auto [l, r] : edg) {
        if (l < 0 and r >= n) return 0;
        if (l < 0 or type[l] == 0) {
            if (n <= r or type[r] == 0) return 0;
            type[r] = 1;
            continue;
        }
        if (n <= r or type[r] == 0) {
            if (l < 0 or type[l] == 0) return 0;
            type[l] = 1;
            continue;
        }
        if (l == r) {
            type[l] = 1;
            continue;
        }
        if (type[l] == 1 or type[r] == 1) continue;
        ee.pb({l, r});
    }
    for (auto [l, r] : ee) {
        if (type[l] == 1 or type[r] == 1) continue;
        g[l].pb(r), g[r].pb(l);
    }
    for (int i = 0; i < n; ++i) assert(sz(g[i]) <= 2);
    vector<int> vis(n), dp(n+2);
    auto dfs = [&] (auto&& self, int u) -> int {
        int t = 1;
        vis[u] = 1;
        for (auto v : g[u]) {
            if (vis[v]) continue;
            t += self(self, v);
        }
        return t;
    };
    dp[1] = 2, dp[2] = 3;
    for (int i = 3; i < n; ++i) {
        dp[i] = (dp[i-1] + dp[i-2]) % mod;
    }
    int ans = 1;
    for (int i = 0; i < n; ++i) {
        //cout << type[i] << " ";
        if (type[i] != -1) continue;
        if (!vis[i]) {
            int t = dfs(dfs, i);
            ans = ans * dp[t] % mod;
        }
    }
    //cout << endl;
    return ans;
}

int brute(int n, vector<int> a) {
    vector<int> type(n), esq(n, n), dir(n, n);
    int ans = 0;
    for (int i = 1; i < (1 << n); ++i) {
        for (int j = 0; j < n; ++j) type[j] = (i >> j & 1);
        esq[0] = (type[0] ? 0 : n);
        dir[n-1] = (type[n-1] ? 0 : n);
        for (int j = 1; j < n; ++j) esq[j] = (type[j] ? 0 : esq[j-1]+1);
        for (int j = n-2; j >= 0; --j) dir[j] = (type[j] ? 0 : dir[j+1]+1);
        int ok = 1;
        for (int j = 0; j < n; ++j) {
            if (a[j] == -1) continue;
            ok &= (min(esq[j], dir[j]) == a[j]);
        }
        ans += ok;
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        cout << solve(n, a) << endl;;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 12);
        vector<int> a(n);
        for (auto& x : a) x = rnd(-n, n-1), ckmax(x, -1);
        int my = solve(n, a), ans = brute(n, a);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : a) cout << x << " ";
            cout << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
