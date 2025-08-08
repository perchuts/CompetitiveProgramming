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
    const int MAX = 1e5;
    vector<vector<int>> divs(MAX+1);
    for (int i = 1; i <= MAX; ++i) for (int j = i; j <= MAX; j += i) divs[j].pb(i);
    int n; cin >> n;
    vector<int> resp(MAX), vis(n), subt(n), a(n), reset(128*n+1);
    vector<ii> sexo(MAX);
    vector<vector<int>> g(n);
    int ans = 0;
    for (auto& x : a) cin >> x;
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    int idr = 0;
    auto pre = [&] (auto&& self, int u, int p) -> int {
        subt[u] = 1;
        for (auto v : g[u]) {
            if (v == p or vis[v]) continue;
            subt[u] += self(self, v, u);
        }
        return subt[u];
    };
    auto fc = [&] (auto&& self, int u, int p, int tt) -> int {
        for (auto v : g[u]) {
            if (v == p or vis[v]) continue;
            if (2 * subt[v] > tt) return self(self, v, u, tt);
        }
        return u;
    };
    auto dfs = [&] (auto&& self, int u, int p, int h, int gg, int tipo) -> void {
        if (tipo == 0) {
            // add
            //cout << u << endl;
            for (auto d : divs[gg]) {
                //cout << "add " << d * (sexo[d].second * h + sexo[d].first) << " to d = " << d << endl;
                resp[d] = (resp[d] + d * (sexo[d].second * h + sexo[d].first)) % mod;
            }
        } else {
            // update
            for (auto d : divs[gg]) {
                reset[idr++] = d;
                sexo[d].second++;
                sexo[d].first += h;
                if (sexo[d].first >= mod) sexo[d].first -= mod;
            }
        }
        for (auto v : g[u]) {
            if (v == p or vis[v]) continue;
            self(self, v, u, h+1, gcd(a[v], gg), tipo);
        }
    };
    auto solve = [&] (auto&& self, int u) -> void {
        idr = 0;
        pre(pre, u, u), u = fc(fc, u, u, subt[u]);
        //cout << "cen = " << u << endl;
        vis[u] = 1;
        for (auto v : g[u]) {
            if (vis[v]) continue;
            dfs(dfs, v, v, 1, gcd(a[v], a[u]), 0);
            dfs(dfs, v, v, 2, gcd(a[v], a[u]), 1);
        }
        //cout << "from cen: " << endl;
        for (int i = 0; i < idr; ++i) {
            //cout << "add " << reset[i] * sexo[reset[i]].first << " to d = " << reset[i] << endl;
            resp[reset[i]] = (resp[reset[i]] + reset[i] * sexo[reset[i]].first) % mod;
            sexo[reset[i]] = {0, 0};
        }
        for (auto v : g[u]) {
            if (vis[v]) continue;
            self(self, v);
        }
    };
    solve(solve, 0);
    vector<int> inv(MAX+1);

    auto fexp = [&] (int b, int e) {
        int rr = 1;
        while (e) {
            if (e&1) rr = rr * b % mod;
            b = b * b % mod, e /= 2;
        }
        return rr;
    };
    for (int i = 1; i <= MAX; ++i) inv[i] = fexp(i, mod-2);
    for (int i = MAX; i >= 1; --i) {
        for (int j = 2 * i; j <= MAX; j += i) {
            int k = resp[j] * inv[j] % mod * i % mod;
            resp[i] = (resp[i] + mod - k) % mod;
        }
        ans = (ans + resp[i]) % mod;
    }
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
