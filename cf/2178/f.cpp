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
    int n; cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    vector<int> subt(n+1), subt2(n+1);
    vector<int> z;
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        subt[u] = 1;
        subt2[u] = 1;
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
            subt[u] ^= subt[v];
            subt2[u] += subt2[v];
        }
        if (subt2[u] % 2 == 0 and u != 0) {
            z.pb(subt2[u]);
            subt2[u] = 0;
        }
    };
    dfs(dfs, 0, 0);
    if (z.empty()) {
        cout << 1 << endl;
        return;
    }
    int S = n;
    int ans = 0;
    for (auto x : z) S -= x;
    int prod = 1;
    for (auto x : z) {
        x = x * x % mod;
        prod = prod * x % mod;
    }
    auto fexp = [&] (int b, int e) {
        int w = 1;
        while (e) {
            if (e&1) w = w * b % mod;
            b = b * b % mod, e /= 2;
        }
        return w;
    };
    int f = 1;
    for (int i = 1; i < sz(z); ++i) f = f * i % mod;
    for (auto x : z) {
        int iv = fexp(x, mod-2);
        int prod2 = iv * prod % mod;
        ans = (ans + prod2 * S) % mod;
    }
    ans = ans * f % mod;
    cout << ans << endl;
    // quantas arvores existem boas com cnt caras pares
}

void gen(int n, vector<ii> edg) {
    auto normalize = [&] (vector<ii> v) {
        for (auto& [x, y] : v) if (x < y) swap(x, y);
        sort(all(v));
        return v;
    };
    map<vector<ii>, bool> mark;
    map<vector<ii>, bool> good;
    edg = normalize(edg);
    auto go = [&] (auto&& self, vector<ii> cur) -> void {
        cur = normalize(cur);
        if (mark[cur]) return;
        mark[cur] = true;
        vector<vector<int>> g(n);
        vector<vector<int>> bichos(n);
        for (auto [x, y] : edg) g[x].pb(y), g[y].pb(x);
        vector<int> subt(n+1), eh_bom(n+1), tem_white(n+1);
        auto dfs = [&] (auto&& self, int u, int p) -> void {
            subt[u] = 1;
            eh_bom[u] = 1;
            bichos[u].pb(u);
            for (auto v : g[u]) {
                if (v == p) continue;
                self(self, v, u);
                subt[u] ^= subt[v];
                for (auto x : bichos[v]) bichos[u].pb(x);
                tem_white[u] += tem_white[v];
                eh_bom[u] &= eh_bom[v];
            }
            if (tem_white[u] > 1) eh_bom[u] = 0;
            if (subt[u] == 0) tem_white[u] = 1;
            ckmin(tem_white[u], 1);
        };
        dfs(dfs, 0, 0);
        if (eh_bom[0]) good[cur] = true;
        for (int i = 0; i < n-1; ++i) {
            auto [u, v] = edg[i];
            if (sz(bichos[u]) > sz(bichos[v])) swap(u, v);
            if (subt[u] == 0) {
                vector<ii> edg2;
                vector<int> mark(n);
                for (int j = 0; j < n-1; ++j) if (i != j) edg2.pb(edg[j]);
                for (auto x : bichos[u]) mark[x] = 1;
                for (auto x : bichos[u]) {
                    for (int i = 0; i < n; ++i) {
                        if (mark[i] == 0) {
                            if (cur == edg) cout << i << ' ' << x << endl;
                            edg2.pb({i, x});
                            self(self, edg2);
                            edg2.pop_back();
                        }
                    }
                }
            }
        }
    };
    go(go, edg);
    cout << sz(good) << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) solve();
#else
    int t = 1;
    int n = rnd(2, 7);
    vector<int> p(n);
    vector<ii> edg;
    vector<int> ord(n); iota(all(ord), 0); shuffle(all(ord), rng);
    for (int i = 1; i < n; ++i) {
        p[i] = rnd(0, i-1);
    }
    for (int i = 1; i < n; ++i) edg.pb({ord[i], ord[p[i]]});
    edg.clear();
    cin >> t;
    while (t--) {
        cin >> n;
        edg.clear();
        for (int i = 0; i < n-1; ++i) {
            int u, v; cin >> u >> v; --u, --v;
            edg.pb({u, v});
        }
        gen(n, edg);
    }
#endif
}
