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

vector<int> solve(int n, int q, vector<ii> edg, vector<ii> qu) {
    vector<vector<int>> g(n+1);
    for (auto [u, v] : edg) g[u].pb(v), g[v].pb(u);
    vector<int> mx(n+1, -1), dir(n+1), h(n+1);
    const int LG = 18;
    vector<vector<int>> bl(n+1, vector<int>(LG));
    vector<int> pai(n+1);
    vector<int> ini(n+1), fim(n+1);
    int T = 0;
    auto pre = [&] (auto&& self, int u, int p) -> void {
        bl[u][0] = pai[u] = p;
        h[u] = 1 + h[p];
        ini[u] = ++T;
        for (int i = 1; i < LG; ++i) bl[u][i] = bl[bl[u][i-1]][i-1];
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
            if (ckmax(mx[u], max(mx[v], v))) dir[u] = v;
        }
        fim[u] = T;
    };
    pre(pre, 1, 0);
    auto lca = [&] (int u, int v) {
        if (h[u] < h[v]) swap(u, v);
        for (int i = LG-1; ~i; --i) {
            if (h[bl[u][i]] >= h[v]) u = bl[u][i];
        }
        if (u == v) return u;
        for (int i = LG-1; ~i; --i) {
            if (bl[u][i] != bl[v][i]) u = bl[u][i], v = bl[v][i];
        }
        return bl[u][0];
    };
    auto is_anc = [&] (int u, int v) {
        return ini[u] <= ini[v] and fim[v] <= fim[u];
    };
    vector<int> ans(q);
    vector<vector<ii>> queries(n+1);
    for (int i = 0; i < q; ++i) {
        auto [u, v] = qu[i];
        int l = lca(u, v);
        ans[i] += h[u] - h[l];
        if (l != v) queries[v].pb({l, i});
    }
    vector<vector<ii>> g2(n+1);
    for (int i = 1; i <= n; ++i) {
        for (auto j : g[i]) {
            if (pai[j] == i) g2[i].pb({j, 1});
        }
    }
    for (int i = 1; i <= n; ++i) {
		if (mx[i] == -1) continue;
        if (i == 1 or mx[pai[i]] != mx[i]) {
            int cur = i;
            while (cur != mx[i]) {
                cur = dir[cur];
                g2[i].pb({cur, 1 + h[mx[i]] - h[cur]});
            }
        }
    }
    vector<int> jump(n+1, 5*n);
    jump[1] = 0;
    priority_queue<ii, vector<ii>, greater<>> pq;
    pq.push({0, 1});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (jump[u] != d) continue;
        for (auto [v, w] : g2[u]) {
            if (ckmin(jump[v], d + w)) pq.push({jump[v], v});
        }
    }
    vector<ii> cortes;
    vector<int> eh_ruim(n+1);
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        bool mark = 0;
        if (u == 1 or mx[pai[u]] != mx[u]) cortes.pb({h[u], u}), mark = 1, eh_ruim[u] = 1;
        for (auto [anc, id_q] : queries[u]) {
            int j = lower_bound(all(cortes), pair(h[anc], -n)) - begin(cortes);
            if (j == sz(cortes)) {
                ans[id_q] += min(h[mx[u]] - h[u] + 1, h[u] - h[anc]);
                //cout << "c1" << endl;
            } else if (eh_ruim[anc]) {
                //cout << "c2" << endl;
                ans[id_q] += jump[u] - jump[anc];
            } else {
                //cout << "c3" << endl;
                auto [alt_w, w] = cortes[j];
                // quer dizer que de anc ateh o w nao tem ngm
                int opcao1 = alt_w - h[anc] + jump[u] - jump[w];
                //cout << mx[anc] << " " << w << endl;
                int opcao2 = (is_anc(mx[anc], w) ? 1 + jump[u] - jump[w] : h[mx[anc]] - (alt_w-1) + 1 + jump[u] - jump[w] + 1);
                //cout << opcao1 << " " << opcao2 << endl;
                ans[id_q] += min(opcao1, opcao2);
            }
        }
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
        }
        if (mark) cortes.pop_back();
    };
    dfs(dfs, 1, 0);
    return ans;
}

vector<int> brute(int n, int q, vector<ii> edg, vector<ii> qu) {
    vector<vector<int>> adj(n+1, vector<int>(n+1, 10*n));
    vector<vector<int>> g(n+1);
    for (auto [u, v] : edg) adj[u][v] = adj[v][u] = 1, g[u].pb(v), g[v].pb(u);
    auto dfs = [&] (auto&& self, int u, int p) -> int {
        int mx = 0;
        for (auto v : g[u]) {
            if (v == p) continue;
            ckmax(mx, self(self, v, u));
        }
        if (mx) adj[u][mx] = 1;
        return max(mx, u);
    };
    dfs(dfs, 1, 1);
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                ckmin(adj[i][j], adj[i][k] + adj[k][j]);
            }
        }
    }
    vector<int> ans;
    for (auto [u, v] : qu) ans.pb(adj[u][v]);
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    int n, q; cin >> n;
    vector<ii> edg(n-1);
    for (auto& [u, v] : edg) cin >> u >> v;
    cin >> q;
    vector<ii> qu(q);
    for (auto& [u, v] : qu) cin >> u >> v;
    auto ans = solve(n, q, edg, qu);
    for (auto x : ans) cout << x << " ";
    cout << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 30), q = 1;
        vector<int> p(n); iota(all(p), 1); shuffle(all(p), rng);
        vector<ii> edg;
        vector<ii> qu(q);
        for (int i = 1; i < n; ++i) edg.pb({p[i], p[rnd(0, i-1)]});
        for (auto& [u, v] : qu) u = rnd(1, n-1), v = rnd(u+1, n);
        auto my = solve(n, q, edg, qu);
        auto ans = brute(n, q, edg, qu);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto [u, v] : edg) cout << u << " " << v << endl;
            cout << q << endl;
            for (auto [u, v] : qu) cout << u << " " << v << endl;
            cout << "Solve: ";
            for (auto x : my) cout << x << " ";
            cout << endl;
            cout << "Brute: ";
            for (auto x : ans) cout << x << " ";
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
