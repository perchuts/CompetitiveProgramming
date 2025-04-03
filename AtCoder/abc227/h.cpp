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

const int INF = inf;

struct dinitz {
    const bool scaling = false; 
    int lim;
    struct edge {
        int to, cap, rev, flow;
        bool res;
        edge(int to_, int cap_, int rev_, bool res_)
        : to(to_), cap(cap_), rev(rev_), flow(0), res(res_) {}
    };

    vector<vector<edge>> g;
    vector<int> lev, beg;
    ll F;
    dinitz(int n) : g(n), F(0) {}

    void add(int a, int b, int c) {
        g[a].emplace_back(b, c, g[b].size(), false);
        g[b].emplace_back(a, 0, g[a].size()-1, true);
    }
    bool bfs(int s, int t) {
        lev = vector<int>(g.size(), -1); lev[s] = 0;
        beg = vector<int>(g.size(), 0);
        queue<int> q; q.push(s);
        while (q.size()) {
            int u = q.front(); q.pop();
            for (auto& i : g[u]) {
                if (lev[i.to] != -1 or (i.flow == i.cap)) continue;
                if (scaling and i.cap - i.flow < lim) continue;
                lev[i.to] = lev[u] + 1;
                q.push(i.to);
            }
        }
        return lev[t] != -1;
    }
    int dfs(int v, int s, int f = INF) {
        if (!f or v == s) return f;
        for (int& i = beg[v]; i < g[v].size(); i++) {
            auto& e = g[v][i];
            if (lev[e.to] != lev[v] + 1) continue;
            int foi = dfs(e.to, s, min(f, e.cap - e.flow));
            if (!foi) continue;
            e.flow += foi, g[e.to][e.rev].flow -= foi;
            return foi;
        }
        return 0;
    }
    ll max_flow(int s, int t) {
        for (lim = scaling ? (1<<30) : 1; lim; lim /= 2)
            while (bfs(s, t)) while (int ff = dfs(s, t)) F += ff;
        return F;
    }
};

// Euler Path / Euler Cycle
//
// Para declarar: 'euler<true> E(n);' se quiser
// direcionado e com 'n' vertices
// As funcoes retornam um par com um booleano
// indicando se possui o cycle/path que voce pediu,
// e um vector de {vertice, id da aresta para chegar no vertice}
// Se for get_path, na primeira posicao o id vai ser -1
// get_path(src) tenta achar um caminho ou ciclo euleriano
// comecando no vertice 'src'.
// Se achar um ciclo, o primeiro e ultimo vertice serao 'src'.
// Se for um P3, um possiveo retorno seria [0, 1, 2, 0]
// get_cycle() acha um ciclo euleriano se o grafo for euleriano.
// Se for um P3, um possivel retorno seria [0, 1, 2]
// (vertie inicial nao repete)
//
// O(n+m)

template<bool directed=false> struct euler {
    int n;
    vector<vector<pair<int, int>>> g;
    vector<int> used;

    euler(int n_) : n(n_), g(n) {}
    void add(int a, int b) {
        int at = used.size();
        used.push_back(0);
        g[a].emplace_back(b, at);
        if (!directed) g[b].emplace_back(a, at);
    }
    pair<bool, vector<pair<int, int>>> get_path(int src) {
        if (!used.size()) return {true, {}};
        vector<int> beg(n, 0);
        for (int& i : used) i = 0;
        // {{vertice, anterior}, label}
        vector<pair<pair<int, int>, int>> ret, st = {{{src, -1}, -1}};
        while (st.size()) {
            int at = st.back().first.first;
            int& it = beg[at];
            while (it < g[at].size() and used[g[at][it].second]) it++;
            if (it == g[at].size()) {
                if (ret.size() and ret.back().first.second != at)
                    return {false, {}};
                ret.push_back(st.back()), st.pop_back();
            } else {
                st.push_back({{g[at][it].first, at}, g[at][it].second});
                used[g[at][it].second] = 1;
            }
        }
        if (ret.size() != used.size()+1) return {false, {}};
        vector<pair<int, int>> ans;
        for (auto i : ret) ans.emplace_back(i.first.first, i.second);
        reverse(ans.begin(), ans.end());
        return {true, ans};
    }
    pair<bool, vector<pair<int, int>>> get_cycle() {
        if (!used.size()) return {true, {}};
        int src = 0;
        while (!g[src].size()) src++;
        auto ans = get_path(src);
        if (!ans.first or ans.second[0].first != ans.second.back().first)
            return {false, {}};
        ans.second[0].second = ans.second.back().second;
        return ans;
    }
};
void solve(){
    vector<vector<int>> a(3, vector<int>(3));
    for (auto& x : a) for (auto& y : x) cin >> y;
    auto encode = [] (int x, int y) { return 3 * x + y; };
    auto decode = [] (int x) { return make_pair(x/3, x%3); };
    vector<ii> edg;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) { 
            if (i != 2) edg.pb({encode(i, j), encode(i+1, j)});
            if (j != 2) edg.pb({encode(i, j), encode(i, j+1)});
        }
    }
    for (int m = 0; m < (1<<12); ++m) {
        vector<vector<int>> g(9);
        for (int i = 0; i < 12; ++i) {
            if (m >> i & 1) g[edg[i].first].pb(edg[i].second), g[edg[i].second].pb(edg[i].first);
        }
        int cntt = 0;
        vector<int> vis(9);
        auto dfs = [&] (auto&& self, int u) -> void {
            vis[u] = 1;
            cntt++;
            for (auto v : g[u]) {
                if (vis[v]) continue;
                self(self, v);
            }
        };
        dfs(dfs, 0);
        if (cntt != 9) continue;
        vector<vector<int>> b = a;
        for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) b[i][j] *= 2;
        for (int j = 0; j < 12; ++j) {
            if (m >> j & 1) {
                auto [x1, y1] = decode(edg[j].first);
                auto [x2, y2] = decode(edg[j].second);
                b[x1][y1]--;
                b[x2][y2]--;
            }
        }
        dinitz d(11);
        int src = 9, sink = src+1, ok = 1, ss = 0;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                ok &= (b[i][j] >= 0);
                ss += b[i][j];
                if (!ok) break;
                if ((i+j) & 1) d.add(src, encode(i, j), b[i][j]);
                else d.add(encode(i, j), sink, b[i][j]);
            }
        }
        if (!ok) continue;
        for (auto [x, y] : edg) {
            if (x&1) d.add(x, y, inf);
            else d.add(y, x, inf);
        }
        if (ss % 2) break;
        if (d.max_flow(src, sink) == ss/2) {
            euler E(9);
            for (int i = 0; i < 9; ++i) {
                if (i&1) {
                    for (auto e : d.g[i]) if (!e.res) for (int k = 0; k < e.flow; ++k) {
                        E.add(i, e.to);
                    }
                }
            }
            for (int i = 0; i < 12; ++i) {
                auto [x, y] = edg[i];
                if (m >> i & 1) {
                    E.add(x, y);
                }
            }
            auto [bb, v] = E.get_cycle();
            assert(bb);
            int xc = 0, yc = 0;
            for (int i = 1; i < sz(v); ++i) {
                auto [nv, fds] = v[i];
                auto [nx, ny] = decode(nv);
                if (xc-nx == 1) cout << 'U';
                if (xc-nx == -1) cout << 'D';
                if (yc-ny == 1) cout << 'L';
                if (yc-ny == -1) cout << 'R';
                xc = nx, yc = ny;
            }
            cout << endl;
            exit(0);
        }
    }
    cout << "NO" << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
