#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+9;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
// Kosaraju
//
// O(n + m)

const int MAX = 1005;
struct kosaraju {
    vector<vector<int>> g, gi;
    vector<int> vis, comp;
    stack<int> S;
    int n;
    kosaraju(int n_) {
        n = n_;
        vis.resize(n_), comp.resize(n_), g.resize(n_), gi.resize(n_);
    }

    void add(int u, int v) {
        g[u].pb(v);
        gi[v].pb(u);
    }

    void dfs(int k) {
        vis[k] = 1;
        for (int i = 0; i < (int) g[k].size(); i++)
            if (!vis[g[k][i]]) dfs(g[k][i]);

        S.push(k);
    }

    void scc(int k, int c) {
        vis[k] = 1;
        comp[k] = c;
        for (int i = 0; i < (int) gi[k].size(); i++)
            if (!vis[gi[k][i]]) scc(gi[k][i], c);
    }

    void calc() {
        for (int i = 0; i < n; i++) vis[i] = 0;
        for (int i = 0; i < n; i++) if (!vis[i]) dfs(i);

        for (int i = 0; i < n; i++) vis[i] = 0;
        while (S.size()) {
            int u = S.top();
            S.pop();
            if (!vis[u]) scc(u, u);
        }
    }

};

vector<int> solve(int n, int m, vector<ii> edg) {
    vector<int> ans(m, -1), deg(n);
    kosaraju orig(n);
    for (auto& [u, v] : edg) orig.add(u, v);
    orig.calc();
    vector<vector<ii>> gg(n), dag(n);
    for (int i = 0; i < m; ++i) {
        auto [u, v] = edg[i];
        if (orig.comp[u] == orig.comp[v]) {
            gg[u].pb({v, i});
        }
        else dag[orig.comp[v]].pb({orig.comp[u], i});
    }
    for (int i = 0; i < n; ++i) {
        for (auto [j, id] : dag[i]) deg[j]++;
    }
    queue<int> qq;
    for (int i = 0; i < n; ++i) {
        if (deg[i] == 0) qq.push(i);
    }
    vector<vector<int>> dp(n, vector<int>(n));
    while (!qq.empty()) {
        auto u = qq.front(); qq.pop();
        dp[u][u] = 1;
        for (auto [v, id] : dag[u]) {
            deg[v]--;
            if (deg[v] == 0) qq.push(v);
            for (int i = 0; i < n; ++i) {
                dp[v][i] += dp[u][i];
                if (dp[v][i] >= mod) dp[v][i] -= mod;
            }
        }
    }
    // agora resolver pra arestas entre scc e pra arestas da mesma scc
    for (int i = 0; i < m; ++i) {
        auto [u, v] = edg[i];
        if (orig.comp[u] != orig.comp[v]) ans[i] = (max(dp[orig.comp[u]][orig.comp[v]], dp[orig.comp[v]][orig.comp[u]]) == 1 ? 1 : 0);
    }
    // vou resolver em O(M) pra todas as arestas saindo de um vertice
    vector<vector<int>> comps(n);
    for (int i = 0; i < n; ++i) comps[orig.comp[i]].pb(i);
    vector<int> idx(n), foi(n), especial(n), qtd(n);
    for (int i = 0; i < n; ++i) {
        int c = orig.comp[i];
        kosaraju kj(comps[c].size());
        //cout << "ans " << i+1 << endl;
        for (int w = 0; w < sz(comps[c]); ++w) idx[comps[c][w]] = w, foi[w] = deg[w] = qtd[w] = especial[w] = 0;
        for (auto j : comps[c]) {
            //cout << j << ' ' << idx[j] << endl;
        }
        for (auto j : comps[c]) {
            if (i != j) {
                for (auto w : gg[j]) {
                    kj.add(idx[j], idx[w.first]);
                    //cout << "add " << idx[j]+1 << ' ' << idx[w.first]+1 << endl;
                }
            } else {
                especial[idx[j]] = 1;
                for (auto w : gg[j]) {
                    especial[idx[w.first]] = 1;
                    if (foi[idx[w.first]]) kj.add(idx[j], idx[w.first]);
                    else foi[idx[w.first]] = 1;
                }
            }
        }
        kj.calc();
        for (int j = 0; j < sz(comps[c]); ++j) {
            for (auto k : kj.g[j]) if (kj.comp[k] != kj.comp[j]) deg[kj.comp[k]] = 1;
            //cout << kj.comp[j] << ' ' << especial[j] << endl;
            qtd[kj.comp[j]] += especial[j];
        }
        //cout << "edges: ";
        for (auto [j, id_e] : gg[i]) {
            j = idx[j];
            //cout << j+1 << ' ' << id_e + 1 << ' ' << deg[kj.comp[j]] << ' ' << qtd[kj.comp[j]] << endl;
            if (deg[kj.comp[j]] == 0 and qtd[kj.comp[j]] == 1) ans[id_e] = 0;
            else ans[id_e] = 1;
        }

    }
    return ans;
}

vector<int> brute(int n, int m, vector<ii> edg) {
    vector<int> ans(m);
    auto get = [n] (vector<ii> edg) {
        vector<int> tipo(n);
        kosaraju kk(n);
        for (auto [u, v] : edg) kk.add(u, v);
        kk.calc();
        for (int i = 0; i < n; ++i) tipo[kk.comp[i]] = 1;
        int tot = 0;
        for (int i = 0; i < n; ++i) tot += tipo[i];
        return tot;
    };
    int tot = get(edg);
    for (int i = 0; i < m; ++i) {
        swap(edg[i].first, edg[i].second); 
        if (get(edg) == tot) ans[i] = 1;
        swap(edg[i].first, edg[i].second);
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    int n, m; cin >> n >> m;
    vector<ii> edg(m);
    for (auto& [u, v] : edg) cin >> u >> v, --u, --v;
    auto ans = solve(n, m, edg);
    for (int i = 0; i < m; ++i) {
        cout << (ans[i] ? "same" : "diff") << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 8);
        //int m = rnd(1, min(3*n, n * (n-1) / 2));
        int m = rnd(1, min(n*(n-1), 10LL));
        map<ii, int> sexo;
        vector<ii> edg(m);
        for (auto& [u, v] : edg) {
            while (true) {
                u = rnd(0, n-1), v = rnd(0, n-1);
                if (u != v and sexo[{u, v}] == 0) {
                    sexo[{u, v}] = 1;
                    break;
                }
            }
        }
        auto my = solve(n, m, edg);
        auto ans = brute(n, m, edg);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << m << endl;
            for (auto [u, v] : edg) cout << u + 1 << ' ' << v + 1 << endl;
            cout << "Answer: ";
            for (auto u : my) cout << (u ? "same" : "diff") << ' ';
            cout << endl;
            cout << "Answer: ";
            for (auto u : ans) cout << (u ? "same" : "diff") << ' ';
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
