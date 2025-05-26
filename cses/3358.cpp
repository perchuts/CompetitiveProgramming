#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
//#define gato

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 1e9+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve(int n, int m, vector<ii>& edg){
    vector<vector<ii>> g1(n+2);
    vector<int> dp(n+2), deg(n+2);
    vector<ii> tr(n+2);
    int src = n, sink = n+1;
    for (int i = 0; i < n; ++i) {
        g1[i].pb({src, -1});
        g1[sink].pb({i, -1});
        deg[src]++, deg[i]++;
    }
    int xkao = 0;
    for (auto& [u, v] : edg) g1[v].pb({u, xkao++}), deg[u]++;
    queue<int> q;
    q.push(sink);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto [v, ide] : g1[u]) {
            --deg[v];
            if (ckmax(dp[v], dp[u]+1)) tr[v] = {u, ide};
            if (deg[v] == 0) q.push(v);
        }
    }
    vector<int> path, use(m), use_v(n), vis(2*n+2);
    int cur = src;
    while (cur != sink) {
        auto [cur2, ide] = tr[cur];
        if (ide != -1) use[ide] = 1;
        cur = cur2, path.pb(cur);
        if (cur < n) use_v[cur] = 1;
    }
    path.pop_back();
	for (auto x : path) cout << x + 1 << ' ';
	cout << endl;
	cout.flush();
    vector<vector<ii>> g(2*n+2);
    for (int i = 0; i < m; ++i) {
        auto [u, v] = edg[i];
        if (!use[i]) g[u+n].pb({v, n+i});
        else g[v].pb({u+n, n+i});
    }
    src = 2*n, sink = 2*n+1;
    for (int i = 0; i < n; ++i) {
        if (use_v[i]) g[i+n].pb({i, i});
        else g[i].pb({i+n, i});
        if (i == path[0]) g[i].pb({src, -1});
        else g[src].pb({i, -1});
        if (i == path.back()) g[sink].pb({i+n, -1});
        else g[i+n].pb({sink, -1});
    }
    vector<int> dist(2*n+2, inf);
    vector<ii> tr2(2*n+2);
    priority_queue<ii, vector<ii>, greater<>> pq;
    dist[src] = 0;
    pq.push({0, src});
	// preciso de uma modelagem onde todos os custos sao nao negativos
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
		cout << d << ' ' << u << endl;
		cout.flush();
        vis[u] = 1;
        for (auto [v, w] : g[u]) {
            int id = w;
            if (w < 0 or w >= n) w = 0;
            else w = (use_v[(u<n?u:u-n)] ? 1 : -1);
            if (ckmin(dist[v], d+w)) pq.push({dist[v], v}), tr2[v] = {u, id};
        }
    }
    int consigo = sz(path) - dist[sink];
    if (consigo != n) {
        cout << "NO" << endl;
        return;
    }
    cur = sink;
    while (cur != src) { 
        auto [cur2, id] = tr2[cur];
        if (id >= n) use[id-n] ^= 1;
        cur = cur2;
    }
    vector<int> f(n, -1), invf(n, -1);
    for (int i = 0; i < m; ++i) {
        auto [u, v] = edg[i];
        if (use[i]) {
            assert(f[u] == -1);
            f[u] = v;
            invf[v] = u;
        }
    }
    vector<vector<int>> paths(2);
    int x = 0;
    for (int i = 0; i < n; ++i) {
        if (invf[i] == -1) {
            int cur = i;
            while (cur != -1) paths[x].pb(cur), cur = f[cur];
            x++;
        }
    }
    cout << "YES" << endl; 
    for (int i = 0; i < 2; ++i) {
        cout << sz(paths[i]) << ' ';
        for (auto x : paths[i]) cout << x + 1 << ' ';
        cout << endl;
    }
}

int32_t main(){_
#ifndef gato
    int n, m; cin >> n >> m;
    vector<ii> edg(m);
    for (auto& [x, y] : edg) cin >> x >> y, --x, -- y;
    solve(n, m, edg);
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 6);
        vector<ii> edg;
        vector<vector<int>> foi(n, vector<int>(n));
        for (int i = 1; i < n; ++i) edg.pb({rnd(0, i-1), i});
        for (auto [x, y] : edg) foi[x][y] = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (foi[i][j]) continue;
                int k = rnd(0, 3);
                if (k == 3) {
                    edg.pb({i, j});
                }
            }
        }
        cout << n << ' ' << sz(edg) << endl;
        for (auto [x, y] : edg) cout << x+1 << ' ' << y+1 << endl;
        cout.flush();
        solve(n, sz(edg), edg);
    }
#endif
}
