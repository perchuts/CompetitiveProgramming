#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cerr.tie(NULL);
#define int ll
//#define gato

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

int f[1<<18], popc[1<<18], hat[1<<18][19][19], ans[1<<18][19][19];

int brute_force(int n, int m, int k, vector<array<int, 4>> edg) {
	for (int i = 0; i < (1 << n); ++i) for (int j = 0; j <= n; ++j) for (int w = 0; w <= n; ++w) hat[i][j][w] = ans[i][j][w] = 0;
    vector<vector<array<int, 2>>> adj(n, vector<array<int, 2>>(n, {1, 1}));
    for (auto [x, y, a, b] : edg) adj[x][y] = adj[y][x] = {a, b};
    for (int i = 0; i < (1<<n); ++i) {
        f[i] = 1;
        for (int j = 0; j < n; ++j) {
            if (!(i >> j & 1)) continue;
            for (int w = j + 1; w < n; ++w) f[i] = f[i] * adj[j][w][(i >> w & 1) ^ 1] % mod;
        }
    }
    auto fexp = [&] (int b, int e) {
        int rsp = 1;
        while (e) {
            if (e&1) rsp = rsp * b % mod;
            b = b * b % mod, e /= 2;
        }
        return rsp;
    };
    vector<int> inv(n+1);
    for (int i = 1; i <= n; ++i) inv[i] = fexp(i, mod-2);
    for (int j = n; ~j; --j) {
        for (int qty = 0; qty <= n; ++qty) {
            for (int i = 0; i < (1 << n); ++i) {
                if (j == n) {
                    if (popc[i] == qty) hat[i][qty][n] = f[i];
                    else hat[i][qty][n] = 0;
                } else {
                    hat[i][qty][j] = hat[i][qty][j+1];
                    if (i >> j & 1) hat[i][qty][j] = (hat[i][qty][j] + hat[i-(1<<j)][qty][j+1]) % mod;
                }
            }
        }
    }
    for (int i = 0; i < (1<<n); ++i) {
        ans[i][0][n] = 1;
        for (int j = 1; j <= n; ++j) {
            for (int w = 1; w <= j; ++w) { 
                ans[i][j][n] = (ans[i][j][n] + (k * w - j + w + mod) * hat[i][w][0] % mod * ans[i][j-w][n]) % mod;
            }
            ans[i][j][n] = ans[i][j][n] * inv[j] % mod;
        }
    }
    for (int qty = 0; qty <= n; ++qty) {
        for (int j = n-1; ~j; --j) {
            for (int i = 0; i < (1<<n); ++i) {
                ans[i][qty][j] = ans[i][qty][j+1];
                if (i >> j & 1) ans[i][qty][j] = (ans[i][qty][j] + mod - ans[i-(1<<j)][qty][j+1]) % mod;
            }
        }
    }
    return ans[(1<<n)-1][n][0];
}

int solve_edi(int n, int m, int k, vector<array<int, 4>> edg) {
	//cerr << n << ' ' << m << ' ' << k << endl;
	//for (auto a : edg) cerr << a[0] << ' ' << a[1] << ' ' << a[2] << ' ' << a[3] << endl;
    if (n == 0) return 1;
    if (k == 1) return (m ? 0 : 1);
    vector<vector<iii>> g(n);
    for (auto x : edg) g[x[0]].pb({x[1], x[2], x[3]}), g[x[1]].pb({x[0], x[2], x[3]});
    for (int i = 0; i < n; ++i) {
        if (g[i].empty()) {
			//cerr << "empty rule " << i << endl;
            for (auto& x : edg) {
                if (x[0] > i) x[0]--;
                if (x[1] > i) x[1]--;
            }
            return k * solve_edi(n-1, m, k, edg) % mod;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (sz(g[i]) == 1) {
			//cerr << "deg 1 rule " << i << endl;
            int id = -1;
            for (int j = 0; j < m; ++j) {
                if (edg[j][0] == i or edg[j][1] == i) id = j;
            }
            assert(id != -1);
            edg.erase(begin(edg) + id);
            auto [v, a, b] = g[i][0];
            for (auto& x : edg) {
                if (x[0] > i) x[0]--;
                if (x[1] > i) x[1]--;
            }
            return (a + (k-1) * b % mod) * solve_edi(n-1, m-1, k, edg) % mod;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (sz(g[i]) == 2) {
			//cerr << "deg 2 rule " << i << endl;
            int id = -1, id2 = -1;
            for (int j = 0; j < m; ++j) {
                if (edg[j][0] == i or edg[j][1] == i) {
                    if (id == -1) id = j;
                    else id2 = j;
                }
            }
            assert(id2 != -1);
            assert(id != -1);
            edg.erase(begin(edg) + id2);
            edg.erase(begin(edg) + id);
            auto [v, av, bv] = g[i][0];
            auto [w, aw, bw] = g[i][1];
            int aa = (av * aw + (k-1) * bv % mod * bw) % mod;
            int bb = ((k-2) * bv % mod * bw + bv * aw + av * bw) % mod;
            int check = 0;
            for (auto& x : edg) {
                if ((x[0] == v and x[1] == w) or (x[0] == w and x[1] == v)) x[2] = x[2] * aa % mod, x[3] = x[3] * bb % mod, check = 1;
            }
            if (!check) edg.push_back({v, w, aa, bb});
            for (auto& x : edg) {
                if (x[0] > i) x[0]--;
                if (x[1] > i) x[1]--;
                assert(x[0] != x[1]);
            }
            return solve_edi(n-1, sz(edg), k, edg);
        }
    }
    int found = -1;
    for (int j = 0; j < m; ++j) {
        if (sz(g[edg[j][0]]) == 3 and sz(g[edg[j][1]]) == 3) found = j;
    }
    if (found != -1) {
        // delete or contract
        auto [u, v, aa, bb] = edg[found];
		//cerr << "two deg 3 rule: " << u << ' ' << v << endl;
        auto ee = edg; ee.erase(begin(ee) + found);
		//cerr << "erasing: " << endl;
        int del = solve_edi(n, m-1, k, ee);
		//cerr << "end erasing" << endl;
        vector<array<int, 3>> caras;
        vector<array<int, 4>> ne;
        for (auto e : ee) {
            if (e[0] != u and e[1] != u and e[0] != v and e[1] != v) {
                if (e[0] >= u) e[0]--;
                if (e[0] >= v) e[0]--;
                if (e[1] >= u) e[1]--;
                if (e[1] >= v) e[1]--;
                ne.pb(e);
            } else {
                if (e[0] == u or e[0] == v) caras.pb({e[1], e[2], e[3]});
                else caras.pb({e[0], e[2], e[3]});
             }
        }
        for (auto& x : caras) {
            if (x[0] >= u) x[0]--;
            if (x[0] >= v) x[0]--;
        }
        sort(all(caras));
        for (int l = 0, r = 0; l < sz(caras); l = r) {
            int a = 1, b = 1;
            while (r != sz(caras) and caras[l][0] == caras[r][0]) a = a * caras[r][1] % mod, b = b * caras[r++][2] % mod;
            assert(caras[l][0] < n-2);
            ne.pb({n-2, caras[l][0], a, b});
        }
		//cerr << "contracting: " << endl;
        int contr = solve_edi(n-1, sz(ne), k, ne);
		//cerr << "end contracting" << endl;
		//cerr << "del: " << del << " contr: " << contr << endl;
        return (bb*del+(aa-bb+mod)*contr) % mod;
    }
    int ret = brute_force(n, m, k, edg);
	//cerr << "brute force found " << ret << endl;
	return ret;
}

int sol(int n, int m, int k, vector<ii> edg) {
    vector<vector<int>> dp(1<<n, vector<int>(n+1));
    dp[0][0] = 1;
    vector<int> pode(1<<n);
    vector<vector<int>> adj(n, vector<int>(n));
    for (auto [x, y] : edg) adj[x][y] = adj[y][x] = 1;
    for (int i = 0; i < (1 << n); ++i) {
        pode[i] = 1;
        for (int j = 0; j < n; ++j) {
            for (int w = j + 1; w < n; ++w) {
                if ((i >> j & 1) and (i >> w & 1)) pode[i] &= (adj[j][w] == 0);
            }
        }
    }
    for (int i = 1; i < (1<<n); ++i) {
        for (int qtd = 1; qtd <= n; ++qtd) {
            for (int j = i; j; j = (j-1)&i) {
                dp[i][qtd] = (dp[i][qtd] + dp[i-j][qtd-1] * pode[j]) % mod;
            }
        }
    }
    auto fexp = [&] (int b, int e) {
        int rsp = 1;
        while (e) {
            if (e&1) rsp = rsp * b % mod; 
            e /= 2, b = b * b % mod;
        }
        return rsp;
    };
    vector<int> inv(n+1);
    for (int i = 1; i <= n; ++i) inv[i] = fexp(i, mod-2);
    int rsp = 0;
    auto ncr = [&] (int x) {
        int c = 1;
        for (int i = 1; i <= x; ++i) {
            c = c * (k-i+1) % mod;
            c = c * inv[i] % mod;
        }
        return c;
    };
    for (int i = 1; i <= min(n, k); ++i) rsp = (rsp + dp.back()[i] * ncr(i)) % mod;
    return rsp;
}

int32_t main() {_
    for (int i = 0; i < (1 << 18); ++i) popc[i] = __builtin_popcount(i);
#ifndef gato
    int n, m, k; cin >> n >> m >> k;
    vector<ii> edg(m);
    vector<array<int, 4>> real_edg;
    for (auto& [x, y] : edg) cin >> x >> y, --x, --y, real_edg.pb({x, y, 0, 1});
    cout << brute_force(n, m, k, real_edg) << endl;
    //cout << solve_edi(n, m, k, real_edg) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 10), m = rnd(0, min(30LL, n*(n-1)/2)), k = rnd(1, 1e9);
        vector<ii> edg;
        vector<vector<int>> adj(n, vector<int>(n));
        vector<array<int, 4>> sexo;
        for (int i = 0; i < m; ++i) {
            int x = rnd(0, n-2), y = rnd(x+1, n-1);
            while (adj[x][y]) x = rnd(0, n-2), y = rnd(x+1, n-1);
            adj[x][y] = 1;
            edg.pb({x, y});
            sexo.pb({x, y, 0, 1});
        }
        int my = brute_force(n, m, k, sexo);
        int res = sol(n, m, k, edg);
        if (my != res) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << m << ' ' << k << endl;
            for (auto [x, y] : edg) cout << x+1 << ' ' << y+1 << endl;
            cout << "Your output: " << my << endl;
            cout << "Correct solution: " << res << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
