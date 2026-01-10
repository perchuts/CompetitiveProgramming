#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
#define gato

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
int val[250], prox[3];
vector<int> solve(int n, string c, vector<vector<ii>> g, vector<ii> edg) {
    vector<int> color(n);
    for (int i = 0; i < n; ++i) color[i] = val[c[i]];
    sort(all(c));
    if (c[0] == c.back()) return vector<int>();
    vector<int> rem(n-1), ans, good(n), par(n), tot(n), tin(n), tout(n), cu(n);
for (int i = 0; i < n; ++i) cu[i] = (color[i] + sz(g[i])) % 3;
    vector<array<int, 3>> subt(n);
    auto solve = [&] (auto&& self2, int src) -> void {
        int qt = 0;
        vector<int> comp;
        int tt = 0;
        auto dfs = [&] (auto&& self, int u, int p) -> void {
            comp.pb(u);
            subt[u][0] = subt[u][1] = subt[u][2] = 0;
            subt[u][color[u]] = 1;
            tin[u] = ++tt;
            for (auto [v, id] : g[u]) {
                if (rem[id] or v == p) continue;
                if (color[u] != color[v]) good[qt++] = id;
                par[v] = u;
                self(self, v, u);
                subt[u][0] += subt[v][0];
                subt[u][1] += subt[v][1];
                subt[u][2] += subt[v][2];
            }
            tot[u] = subt[u][0]+subt[u][1]+subt[u][2];
            tout[u] = tt;
        };
        par[src] = src;
        dfs(dfs, src, src);
        if (tot[src] == 1) return;
        int choice = -1;
        cout << "src = " << src + 1 << endl;
        cout << "colors: ";
        for (int i = 0; i < n; ++i) cout << color[i] << " ";
        cout << endl;
        for (int i = 0; i < qt; ++i) {
            int id = good[i];
            auto [u, v] = edg[id];
            if (par[v] == u) swap(u, v);
            array<int, 3> ns;
            int nt = tot[src] - tot[u];
            ns[0] = subt[src][0] - subt[u][0], ns[1] = subt[src][1] - subt[u][1], ns[2] = subt[src][2] - subt[u][2];
            cout << u + 1 << " " << v + 1 << endl;
            for (int j = 0; j < 3; ++j) cout << subt[u][j] << " ";
            cout << endl;
            for (int j = 0; j < 3; ++j) cout << ns[j] << " ";
            cout << endl;
            if (tot[u] != 1 and subt[u][(color[u]+1)%3] == tot[u]-1) {
                cout << "fail 1" << endl;
                continue;
            }
            if (nt != 1 and ns[(color[v]+1)%3] == nt-1) {
                cout << "fail 2" << endl;
                continue;
            }
            bool bad = 0;
            if (tot[u] != 1) {
                bool ok = 1;
                for (auto x : comp) {
                    if (tin[u] <= tin[x] and tout[x] <= tout[u]) ok &= (cu[x] == cu[u]);
                }
                bad |= ok;
            }
            if (nt != 1) {
                bool ok = 1;
                for (auto x : comp) {
                    if (!(tin[u] <= tin[x] and tout[x] <= tout[u])) ok &= (cu[x] == cu[v]);
                }
                bad |= ok;
            }
            if (bad) {
                cout << "fail 3" << endl;
                continue;
            }
            choice = id;
            break;
        }
        assert(choice != -1);
        rem[choice] = 1;
        ans.pb(choice);
        auto [u, v] = edg[choice];
        cout << "removing " << u + 1 << ' ' << v + 1 << endl;
        color[u] = (color[u] + 1) % 3;
        color[v] = (color[v] + 1) % 3;
        self2(self2, u);
        self2(self2, v);
    };
    solve(solve, 0);
    return ans;
}

int32_t main() {_
    val['R'] = 0, val['G'] = 1, val['B'] = 2;
    //prox[0]  = 1, prox[1]  = 2, prox[2]  = 0;
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
    int n; cin >> n;
    vector<vector<ii>> g(n);
    string c; cin >> c;
    vector<ii> edg(n-1);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        edg[i] = {u, v};
        g[u].pb({v, i}), g[v].pb({u, i});
    }
        auto ans = solve(n, c, g, edg);
        if (ans.empty()) cout << "No" << endl;
        else {
            cout << "Yes" << endl;
            for (auto x : ans) cout << x + 1 << " ";
            cout << endl;
        }
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 6);
        string c(n, 'R');
        string z = "RGB";
        for (auto& x : c) x = z[rnd(0, 2)];
        string d = c;
        sort(all(d));
        if (d[0] == d.back()) continue;
        vector<vector<ii>> g(n);
        vector<ii> edg;
        for (int i = 1; i < n; ++i) {
            int j = rnd(0, i-1);
            edg.pb({i, j});
            g[i].pb({j, i-1});
            g[j].pb({i, i-1});
        }
        vector<int> zz(n);
        for (int i = 0; i < n; ++i) zz[i] = (sz(g[i]) + val[c[i]]) % 3;
        sort(all(zz));
        if (zz[0] == zz.back()) continue;
        cout << n << endl;
        cout << c << endl;
        for (auto [x, y] : edg) cout << x + 1 << ' ' << y + 1 << endl;
        cout << flush;
        auto my = solve(n, c, g, edg);
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
