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
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    vector<int> p(n); iota(all(p), 1);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        ckmax(p[u], v);
    }
    for (int i = 0; i < n-1; ++i) {
        g[i].pb(p[i]);
        g[p[i]].pb(i);
    }
    int ans = 0;
    vector<int> h(n), lista;
    vector<map<int, int>> mp(n);
    auto dfs = [&] (auto&& self, int u, int p) -> int {
        h[u] = 1 + h[p];
        lista.pb(h[u]);
        int subt = 1;
        for (auto v : g[u]) {
            if (v == p) continue;
            int sv = self(self, v, u);
            if (sz(mp[v]) > sz(mp[u])) swap(mp[u], mp[v]);
            // tira o LCA
            ans -= h[u] * subt * sv;
            subt += sv;
        }
        mp[u][h[u]]++;
        for (auto v : g[u]) {
            if (v == p) continue;
            for (auto [x, y] : mp[v]) ans += mp[u][x] * y * (x - h[u]), mp[u][x] += y;
        }
        return subt;
    };
    dfs(dfs, n-1, n-1);
    sort(rbegin(lista), rend(lista));
    // agora falta o caso onde os vertices tem a mesma altura
    for (int i = 0; i < n; ++i) ans += i * lista[i];
    cout << ans << endl;
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
