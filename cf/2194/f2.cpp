#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
//#define gato
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

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int solve(int n, int k, vector<vector<int>>& g, vector<int>& a, vector<int>& b) {
    vector<int> base(30), id(30), nice(1 << k), cf(1 << k), cc(k); vector<vector<int>> dp(n, vector<int>(1<<k, 1));
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
            if (__builtin_popcount(cc[j] & i) & 1) cf[i]--;
            else cf[i]++;
        }
    }
    int ans = 0, inv2k = 1;
    for (int i = 0; i < k; ++i) inv2k = (inv2k * ((mod+1)/2)) % mod;
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
            subt[u] ^= subt[v];
            for (int i = 0; i < (1 << k); ++i) {
                dp[u][i] = dp[v][i] * dp[u][i] % mod;
            }
        }
        int eu = get(subt[u]);
        if (eu != -1 and u != 0) {
            int add = 0;
            for (int i = 0; i < (1 << k); ++i) {
                if (__builtin_popcount(i & eu) & 1) add -= cf[i] * dp[u][i];
                else add += cf[i] * dp[u][i];
            }
            add %= mod;
            add = (add + mod) % mod;
            add = add * inv2k % mod;
            for (int i = 0; i < (1 << k); ++i) {
                if (__builtin_popcount(i & eu) & 1) dp[u][i] -= add;
                else dp[u][i] += add;
            }
        }
    };
    dfs(dfs, 0, 0);
    auto ifwht = [&] (int u) {
        for (int len = 1; 2*len <= (1<<k); len *= 2) {
            for (int j = 0; j < (1 << k); j += 2 * len) {
                for (int i = 0; i < len; ++i) {
                    int x = dp[u][j+i], y = dp[u][j+i + len];
                    x %= mod, y %= mod;
                    dp[u][j+i] = x + y;
                    dp[u][j+i+len] = x - y;
                }
            }
        }
        for (int i = 0; i < (1 << k); ++i) dp[u][i] = dp[u][i] * inv2k % mod;
    };
    ifwht(0);
    int eu = get(subt[0]);
    for (int i = 0; i < (1 << k); ++i) {
        if (eu != -1 and nice[i ^ eu]) ans += dp[0][i];
    }
    ans %= mod;
    ans = (ans + mod) % mod;
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
		auto start = chrono::steady_clock::now();
        int n = rnd(100000, 100000), k = rnd(10, 10);
        vector<ii> edg;
        vector<int> p(n); iota(all(p), 0);// shuffle(all(p), rng);
        vector<vector<int>> g(n);
        for (int i = 1; i < n; ++i) {
            int j = i-1;
            edg.pb({p[i], p[j]});
            g[p[i]].pb(p[j]), g[p[j]].pb(p[i]);
        }
        vector<int> a(n), b(k);
        for (auto& x : a) x = rnd(0, (1<<30)-1);
		for (auto& x : b) x = rnd(0, (1<<30)-1);
		sort(all(b)), b.erase(unique(all(b)), end(b));
		k = sz(b);
		auto get_time = [&]() {
			auto curr = chrono::steady_clock::now();
			return int32_t(chrono::duration_cast<chrono::milliseconds>(curr - start).count());
		};
        int my = solve(n, k, g, a, b); //ans = correct(n, k, g, a, b);
		cout << "time spent: " << get_time() << endl;
		cout << my << endl;
        //if (my != ans) {
        //    cout << "Wrong answer on test " << t << endl;
        //    cout << n << " " << k << endl;
        //    for (auto [x, y] : edg) cout << x + 1 << " " << y + 1 << endl;
        //    for (auto x : a) cout << x << " ";
        //    cout << endl;
        //    for (auto x : b) cout << x << " ";
        //    cout << endl;
        //    cout << "Solve: " << my << endl;
        //    cout << "Brute: " << ans << endl;
        //    exit(0);
        //}
        //cout << ans << endl;
        //cout << "Accepted on test " << t++ << endl;
    }
#endif
}
