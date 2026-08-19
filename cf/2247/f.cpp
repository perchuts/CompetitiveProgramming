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
    int n, m; cin >> n >> m;
    vector<string> grid(n);
    for (auto& x : grid) cin >> x;
    vector<vector<int>> good(n, vector<int>(m));
    auto dfs = [&] (auto&& self, int i, int j, int k) -> void {
        good[i][j] |= k;
        if (k == 1) {
            if (i and grid[i-1][j] == '1' and (good[i-1][j]&k) == 0) self(self, i-1, j, k);
            if (j and grid[i][j-1] == '1' and (good[i][j-1]&k) == 0) self(self, i, j-1, k);
        } else {
            if (i != n-1 and grid[i+1][j] == '1' and (good[i+1][j]&k) == 0) self(self, i+1, j, k);
            if (j != m-1 and grid[i][j+1] == '1' and (good[i][j+1]&k) == 0) self(self, i, j+1, k);
        }
    };
    dfs(dfs, n-1, m-1, 1);
    dfs(dfs, 0, 0, 2);
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) if (good[i][j] != 3) good[i][j] = 0;
    vector<int> pot(n+m, 1);
    for (int i = 1; i < n+m; ++i) pot[i] = 2 * pot[i-1] % mod;
    int ans = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (good[i][j] == 0) ans = (ans + ans) % mod;
        }
    }
    ans -= 1;
    auto get = [&] (int i, int j) { return m * i + j; };
    int LG = 1;
    while ((1 << LG) < n * m) LG++;
    vector bl(2, vector(n*m, vector<int>(LG)));
    vector<vector<int>> par(2, vector<int>(n*m)), lvl = par;
    auto lca = [&] (int u, int v, int k) {
        if (lvl[k][u] < lvl[k][v]) swap(u, v);
        for (int i = LG-1; ~i; --i) {
            if (lvl[k][bl[k][u][i]] >= lvl[k][v]) u = bl[k][u][i];
        }
        if (u == v) return u;
        for (int i = LG-1; ~i; --i) {
            if (bl[k][u][i] != bl[k][v][i]) u = bl[k][u][i], v = bl[k][v][i];
        }
        return par[k][u];
    };
    vector<vector<vector<int>>> g(2, vector<vector<int>>(n*m));
    for (int i = n-1; ~i; --i) {
        for (int j = m-1; ~j; --j) {
            if (good[i][j] == 0) continue;
            int u = get(i, j);
            if (i + j == n + m - 2) par[0][u] = u;
            else if (i == n-1 or !good[i+1][j]) par[0][u] = get(i, j+1);
            else if (j == m-1 or !good[i][j+1]) par[0][u] = get(i+1, j);
            else par[0][u] = lca(get(i+1, j), get(i, j+1), 0);
            if (u != par[0][u]) g[0][par[0][u]].pb(u);
            bl[0][u][0] = par[0][u], lvl[0][u] = 1 + lvl[0][par[0][u]];
            //cout << "0: " << u << "->" << par[0][u] << endl;
            for (int k = 1; k < LG; ++k) bl[0][u][k] = bl[0][bl[0][u][k-1]][k-1];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (good[i][j] == 0) continue;
            int u = get(i, j);
            if (i + j == 0) par[1][u] = u;
            else if (i == 0 or !good[i-1][j]) par[1][u] = get(i, j-1);
            else if (j == 0 or !good[i][j-1]) par[1][u] = get(i-1, j);
            else par[1][u] = lca(get(i-1, j), get(i, j-1), 1);
            bl[1][u][0] = par[1][u], lvl[1][u] = 1 + lvl[1][par[1][u]];
            //cout << "1: " << u << "->" << par[1][u] << endl;
            if (u != par[1][u]) g[1][par[1][u]].pb(u);
            for (int k = 1; k < LG; ++k) bl[1][u][k] = bl[1][bl[1][u][k-1]][k-1];
        }
    }
    vector<int> vis(n*m), tin(n*m), tout(n*m);
    int T = 0;
    auto dfs2 = [&] (auto&& self, int u) -> void {
        tin[u] = ++T;
        for (auto v : g[0][u]) self(self, v);
        tout[u] = T;
    };
    dfs2(dfs2, get(n-1, m-1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!good[i][j]) continue;
            int u = get(i, j);
            if (vis[u]) continue;
            int c = 0;
            //cout << "scc: ";
            while (true) {
                int prox = -1;
                vis[u] = 1;
                //cout << "(" << (u/m) << "," << u%m << ") ";
                c++;
                for (auto v : g[1][u]) {
                    if (tin[v] <= tin[u] and tout[u] <= tout[v]) {
                        if (prox == -1 or lvl[0][v] > lvl[0][prox]) prox = v;
                    }
                }
                if (prox == -1) break;
                u = prox;
            }
            //cout << endl;
            ans = (ans + pot[c] + mod - 1) % mod;
        }
    }

    cout << ans << endl;
    //cout << flush;
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
