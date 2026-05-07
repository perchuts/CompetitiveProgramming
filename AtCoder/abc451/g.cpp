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
    int n, m, k; cin >> n >> m >> k;
    vector<vector<ii>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w; --u, --v;
        g[v].pb({u, w}), g[u].pb({v, w});
    }
    vector<int> lvl(n, -1), z(n), bichos, base(30);
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        for (auto [v,w] : g[u]) {
            if (lvl[v] == -1) {
                z[v] = z[u] ^ w;
                lvl[v] = 1 + lvl[u];
                self(self, v, u);
            } else bichos.pb(z[u] ^ z[v] ^ w);
        }
    };
    lvl[0] = 0, dfs(dfs, 0, 0);
    for (auto x : bichos) {
        for (int i = 29; ~i; --i) {
            if (x >> i & 1) {
                if (base[i] == 0) {
                    base[i] = x;
                    break;
                }
                x ^= base[i];
            }
        }
    }
    vector<vector<int>> tr = {{0, 0}}; vector<int> cnt = {0};

    int h = 1, ans = 0;

    for (int i = 0; i < n; ++i) for (int j = 29; ~j; --j) if (z[i] >> j & 1) z[i] ^= base[j];
    for (int i = 0; i < n; ++i) {
        int cur = 0, x = z[i] ^ k;
        for (int j = 29; ~j; --j) {
            if (k >> j & 1) ans += cnt[tr[cur][(x>>j&1)^1]];
            cur = tr[cur][x>>j&1];
            if (!cur) break;
        }
        if (cur) ans += cnt[cur];
        cur = 0;
        for (int j = 29; ~j; --j) {
            if (tr[cur][z[i]>>j&1] == 0) tr[cur][z[i]>>j&1] = h++, tr.pb({0, 0}), cnt.pb(0);
            cur = tr[cur][z[i]>>j&1];
            cnt[cur]++;
        }
    }
    cout << ans << endl;
    // quantos caras da forma p[u] ^ p[v] ^ bicho <= k existem

}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
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
