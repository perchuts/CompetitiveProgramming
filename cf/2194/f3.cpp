#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define gato
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

int correct(int n, int k, vector<vector<int>> g, vector<int> a, vector<int> b) {
    vector<int> mask(1<<k);
    auto subt = a;
    for (int i = 0; i < (1 << k); ++i) for (int j = 0; j < k; ++j) if (i >> j & 1) mask[i] ^= b[j];
    vector<vector<int>> dp(n, vector<int>(1<<k));
    int ans = 0;
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        dp[u][0] = 1;
        vector<int> temp(1<<k);
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
            subt[u] ^= subt[v];
            for (int i = 0; i < (1 << k); ++i) temp[i] = 0;
            for (int i = 0; i < (1 << k); ++i) {
                for (int j = 0; j < (1 << k); ++j) {
                    temp[i^j] = (temp[i^j] + dp[u][i] * dp[v][j]) % mod; 
                }
            }
            swap(dp[u], temp);
        }
        temp = dp[u];
        for (int i = 0; i < (1 << k); ++i) {
            int z = mask[i] ^ subt[u];
            int x = 0;
            for (int j = 0; j < k; ++j) if (z == b[j]) x = (1 << j);
            if (x) {
                if (u == 0) ans = (ans + dp[u][i]) % mod;
                temp[i^x] = (temp[i^x] + dp[u][i]) % mod;
            }
        }
        dp[u] = temp;
    };
    dfs(dfs, 0, 0);
    return ans;
}

int solve(int n, int k, vector<vector<int>> g, vector<int> a, vector<int> b) {
    vector<int> base(30), id(30), nice(1 << k), pc(1 << k), cf(1 << k), cc(k); vector<vector<int>> dp(n, vector<int>(1<<k, 1));
    auto subt = a;
    for (int i = 0; i < k; ++i) {
        int tp = b[i];
        int m = (1 << i);
        for (int j = 0; j < 30; ++j) {
            if (tp >> j & 1) {
                if (base[j] == 0) {
                    id[j] = m;
                    base[j] = tp;
                    break;
                }
                tp ^= base[j];
                m ^= id[j];
            }
        }
    }
    for (int i = 1; i < (1 << k); ++i) pc[i] = 1 ^ pc[i - (i & (-i))];
    auto get = [&] (int x) {
        int c = 0;
        for (int j = 0; j < 30; ++j) {
            if (x >> j & 1) {
                if (base[j] == 0) return -1LL;
                c ^= id[j];
                x ^= base[j];
            }
        }
        return c;
    };
    for (int i = 0; i < (1 << k); ++i) {
        int x = 0;
        for (int j = 0; j < k; ++j) if (i >> j & 1) x ^= b[j];
        for (int j = 0; j < k; ++j) {
            if (b[j] == x) nice[i] = 1;
        }
    }
    for (int i = 0; i < k; ++i) cc[i] = get(b[i]);
    for (int i = 0; i < (1 << k); ++i) {
        for (int j = 0; j < k; ++j) {
            if (pc[cc[j] & i]) cf[i] = (cf[i] + mod - 1) % mod;
            else cf[i] = (cf[i] + 1) % mod;
        }
    }
    int ans = 0, inv2k = 1;
    for (int i = 0; i < k; ++i) inv2k = (inv2k * ((mod+1)/2)) % mod;
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
            subt[u] ^= subt[v];
            for (int i = 0; i < (1 << k); ++i) dp[u][i] = dp[u][i] * dp[v][i] % mod;
        }
        int eu = get(subt[u]);
        if (eu != -1 and u != 0) {
            int add = 0;
            for (int i = 0; i < (1 << k); ++i) {
                if (pc[i & eu]) add = (add - cf[i] * dp[u][i]) % mod;
                else add = (add + cf[i] * dp[u][i]) % mod;
                if (add < 0) add += mod;
            }
            add = add * inv2k % mod;
            for (int i = 0; i < (1 << k); ++i) {
                if (pc[i & eu]) dp[u][i] = (dp[u][i] + mod - add) % mod;
                else dp[u][i] = (dp[u][i] + add) % mod;
            }
        }
    };
    dfs(dfs, 0, 0);
    auto ifwht = [&] (int u) {
        for (int len = 1; 2*len <= (1<<k); len *= 2) {
            for (int j = 0; j < (1 << k); j += 2 * len) {
                for (int i = 0; i < len; ++i) {
                    assert(((i+j) & len) == 0);
                    assert(((i+j+len) & len) == len);
                    int x = dp[u][j+i], y = dp[u][j+i + len];
                    dp[u][j+i] = (x + y) % mod;
                    dp[u][j+i + len] = (x + mod - y) % mod;
                }
            }
        }
        for (int i = 0; i < (1 << k); ++i) dp[u][i] = dp[u][i] * inv2k % mod;
    };
    ifwht(0);
    int eu = get(subt[0]);
    for (int i = 0; i < (1 << k); ++i) {
        if (eu != -1 and nice[i ^ eu]) ans = (ans + dp[0][i]) % mod;
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n, k; cin >> n >> k;
        vector<vector<int>> g(n);
        for (int i = 0; i < n-1; ++i) {
            int u, v; cin >> u >> v; --u, --v;
            g[u].pb(v), g[v].pb(u);
        } 
        vector<int> a(n), b(k);
        for (auto& x : a) cin >> x;
        auto subt = a;
        for (auto& x : b) cin >> x;
        cout << solve(n, k, g, a, b) << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 50), k = rnd(1, 4);
        vector<ii> edg;
        vector<int> p(n); iota(all(p), 0); shuffle(all(p), rng);
        vector<vector<int>> g(n);
        for (int i = 1; i < n; ++i) {
            int j = rnd(0, i-1);
            edg.pb({p[i], p[j]});
            g[p[i]].pb(p[j]), g[p[j]].pb(p[i]);
        }
        vector<int> a(n), b(k);
        for (auto& x : a) x = rnd(0, 7);
        for (auto& x : b) x = rnd(0, 7);
        sort(all(b)), b.erase(unique(all(b)), end(b));
        k = sz(b);
        int my = solve(n, k, g, a, b), ans = correct(n, k, g, a, b);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << " " << k << endl;
            for (auto [x, y] : edg) cout << x + 1 << " " << y + 1 << endl;
            for (auto x : a) cout << x << " ";
            cout << endl;
            for (auto x : b) cout << x << " ";
            cout << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << ans << endl;
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
