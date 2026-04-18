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
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        char c; cin >> c;
        a[i] = (c == '1');
    }
    for (int i = 0; i < n; ++i) {
        char c; cin >> c;
        b[i] = (c == '1');
    }
    int m; cin >> m;
    map<ii, int> id_e;
    vector<vector<int>> g(n), gi(n);
    vector<int> vis(n), comp(n);
    stack<int> S;
    for (int i = 0; i < m; ++i) {
        int x, y; cin >> x >> y; --x, --y;
        id_e[{x, y}] = i;
        g[x].pb(y), gi[y].pb(x);
    }
    auto dfs = [&] (auto&& self, int k) -> void {
        vis[k] = 1;
        for (int i = 0; i < (int) g[k].size(); i++)
            if (!vis[g[k][i]]) self(self, g[k][i]);

        S.push(k);
    };
    auto scc = [&] (auto&& self, int k, int c) -> void {
        vis[k] = 1;
        comp[k] = c;
        for (int i = 0; i < (int) gi[k].size(); i++)
            if (!vis[gi[k][i]]) self(self, gi[k][i], c);
    };
    auto kosaraju = [&] () {
        for (int i = 0; i < n; i++) vis[i] = 0;
        for (int i = 0; i < n; i++) if (!vis[i]) dfs(dfs, i);

        for (int i = 0; i < n; i++) vis[i] = 0;
        while (S.size()) {
            int u = S.top();
            S.pop();
            if (!vis[u]) scc(scc, u, u);
        }
    };
    kosaraju();
    vector<vector<int>> comps(n);
    vector<vector<int>> gc(n), gcr(n);
    for (int i = 0; i < n; ++i) {
        for (auto j : g[i]) {
            if (comp[i] != comp[j]) gc[comp[i]].pb(comp[j]), gcr[comp[j]].pb(comp[i]);
        }
        comps[comp[i]].pb(i);
    }
    vector<int> deg(n), good(n);
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (comp[i] != i) continue;
        for (auto x : comps[i]) good[i] |= a[x];
        sort(all(gc[i]));
        gc[i].erase(unique(all(gc[i])), end(gc[i]));
        sort(all(gcr[i]));
        gcr[i].erase(unique(all(gcr[i])), end(gcr[i]));
        deg[i] = sz(gcr[i]);
        if (deg[i] == 0) q.push(i);
        vis[i] = 0;
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v : gc[u]) {
            deg[v]--;
            good[v] |= good[u];
            if (deg[v] == 0) q.push(v);
        }
    }
    vector<int> ans;
    vector<int> arrumei(n);
    auto dfs3 = [&] (auto&& self, int u) -> void {
        assert(a[u] == 1);
        arrumei[u] = 1;
        for (auto v : g[u]) {
            if (arrumei[v]) continue;
            if (a[v] == 0) ans.pb(id_e[{u, v}]), a[v] = 1;
            if (comp[v] != comp[u]) continue;
            self(self, v);
        }
    };
    auto dfs4 = [&] (auto&& self, int u) -> void {
        assert(a[u] == 1);
        arrumei[u] = 1;
        for (auto v : g[u]) {
            if (comp[u] != comp[v]) continue;
            if (arrumei[v]) continue;
            self(self, v);
            if (b[v] == 0) ans.pb(id_e[{u, v}]), a[v] ^= 1;
        }
    };
    auto dfs2 = [&] (auto&& self, int u, int chamou = -1) -> void {
        int um = -1;
        for (auto x : comps[u]) {
            if (a[x] == 1) um = x;
        }
        if (um == -1) return;
        vis[u] = 1;
        // todos da minha componente (e de SCCs vizinhas) sao 1!
        dfs3(dfs3, um);
        for (auto x : gc[u]) {
            // recursivamente tenta resolver la pra frente
            if (!vis[x]) self(self, x, u);
        }
        // corrigir componentes vizinhas
        for (auto x : comps[u]) {
            for (auto y : g[x]) {
                if (comp[x] != comp[y] and b[y] != a[y]) {
                    assert(a[y] == 1);
                    a[y] ^= 1;
                    ans.pb(id_e[{x, y}]);
                }
            }
        }
        // finalizar a minha propria componente
        int ini = -1; um = -1;
        int loop = -1;
        for (auto x : comps[u]) {
            arrumei[x] = 0;
            if (b[x] == 1) um = x;
            for (auto y : gi[x]) {
                if (chamou == -1) {
                    if (comp[y] != comp[x] and good[comp[y]]) ini = x;
                } else {
                    if (comp[y] == chamou) ini = x;
                }
                if (x == y) loop = x;
            }
        }
        if (loop != -1) ini = loop;
        // o L supremo foi feito!
        if (ini == -1 and um == -1) return;
        // me arrumar!
        if (ini == -1) ini = um;
        dfs4(dfs4, ini);
        if (loop != -1 and a[ini] != b[ini]) {
            assert(a[ini]);
            ans.pb(id_e[{ini, ini}]);
            a[ini] ^= 1;
        }
    };
    for (int i = 0; i < n; ++i) if (!vis[i]) dfs2(dfs2, i);
    for (int i = 0; i < n; ++i) {
        if (a[i] != b[i]) {
            cout << -1 << endl;
            return;
        }
    }
    assert(sz(ans) <= 2*n);
    cout << ans.size() << endl;
    for (auto x : ans) cout << x + 1 << " ";
    cout << endl;
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
