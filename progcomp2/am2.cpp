#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
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

vector<int> solve(int n, vector<int> p, vector<ii> qry) {
    vector<ii> intr;
    map<ii, int> get;
    vector<vector<int>> g;
    vector<array<int, 2>> seeg(4*n);
    vector<int> onde(n);
    for (int i = 0; i < n; ++i) onde[p[i]] = i;
    auto buuild = [&] (auto&& self, int i, int l, int r) -> void {
        if (l == r) {
            seeg[i][0] = seeg[i][1] = onde[l];
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md), self(self, 2*i+1, md+1, r);
        seeg[i][0] = min(seeg[2*i][0], seeg[2*i+1][0]);
        seeg[i][1] = max(seeg[2*i][1], seeg[2*i+1][1]);
    };
    auto buuild2 = [&] (auto&& self, int i, int l, int r) -> void {
        int id = sz(intr);
        intr.pb({l, r});
        get[{l, r}] = id;
        g.pb({});
        if (l == r) return;
        int md = (l+r)/2;
        self(self, 2*i, l, md), self(self, 2*i+1, md+1, r);
        auto esq = get[{l, md}], dir = get[{md+1, r}]; 
        g[id].pb(esq), g[id].pb(dir);
    };
    auto queryy = [&] (auto&& self, int i, int l, int r, int x, int y) -> array<int, 2> {
        if (r < x or y < l) return {n, 0};
        if (x <= l and r <= y) return seeg[i];
        int md = (l+r)/2;
        auto esq = self(self, 2*i, l, md, x, y);
        auto dir = self(self, 2*i+1, md+1, r, x, y);
        return {min(esq[0], dir[0]), max(esq[1], dir[1])};
    };
    auto add_edge = [&] (auto&& self, int i, int l, int r, int x, int y, int u) -> void {
        if (r < x or y < l) return;
        if (x <= l and r <= y) {
            g[u].pb(get[{l, r}]);
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md, x, y, u);
        self(self, 2*i+1, md+1, r, x, y, u);
    };
    buuild(buuild, 1, 0, n-1), buuild2(buuild2, 1, 0, n-2);
    for (int i = 0; i < n-1; ++i) {
        int x1 = p[i], x2 = p[i+1];
        if (x1 > x2) swap(x1, x2);
        auto z = queryy(queryy, 1, 0, n-1, x1, x2);
        add_edge(add_edge, 1, 0, n-2, z[0], z[1]-1, get[{i, i}]);
    }
    // agr roda o kosaraju ai
    int N = sz(g);
    vector<vector<int>> gi(N);
    vector<int> vis(N), comp(N);
    stack<int> S;
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
        for (int i = 0; i < N; i++) {
            vis[i] = 0;
            for (auto j : g[i]) gi[j].pb(i);
        }
        for (int i = 0; i < N; i++) if (!vis[i]) dfs(dfs, i);
        
        for (int i = 0; i < N; i++) vis[i] = 0;
        while (S.size()) {
            int u = S.top();
            S.pop();
            if (!vis[u]) scc(scc, u, u);
        }
    };
    kosaraju();
    // componentes estao certas!
    vector<vector<int>> g2(N), gi2(N);
    vector<array<int, 2>> tams(N, {n, 0});
    for (int i = 0; i < N; ++i) {
        ckmax(tams[comp[i]][1], intr[i].second);
        ckmin(tams[comp[i]][0], intr[i].first);
        for (auto j : g[i]) {
            if (comp[i] != comp[j]) g2[comp[i]].pb(comp[j]), gi2[comp[j]].pb(comp[i]);
        }
    }
    vector<int> deg(N); 
    queue<int> qu;
    for (int i = 0; i < N; ++i) {
        if (comp[i] != i) continue;
        sort(all(g2[i]));
        g2[i].erase(unique(all(g2[i])), end(g2[i]));
        sort(all(gi2[i]));
        gi2[i].erase(unique(all(gi2[i])), end(gi2[i]));
        deg[i] = sz(g2[i]);
        if (deg[i] == 0) qu.push(i);
    }
    while (!qu.empty()) {
        int u = qu.front(); qu.pop();
        for (auto v : gi2[u]) {
            deg[v]--;
            ckmin(tams[v][0], tams[u][0]);
            ckmax(tams[v][1], tams[u][1]);
            if (deg[v] == 0) qu.push(v);
        }
    }
    vector<array<int, 2>> v;
    for (int i = 0; i < N; ++i) {
        if (comp[i] == i) v.pb(tams[i]);
    }
    sort(all(v)), v.erase(unique(all(v)), end(v));
    for (auto& x : v) x[1]++;
    int q = sz(qry);
    vector<int> ans(q);
    vector<vector<int>> queries(n);
    for (int i = 0; i < q; ++i) queries[qry[i].first].pb(i);
    
    vector<int> seg2(4*n), lz2(4*n);

    auto push2 = [&] (int i, int l, int r) {
        seg2[i] += (r-l+1) * lz2[i];
        if (l != r) lz2[2*i] += lz2[i], lz2[2*i+1] += lz2[i];
        lz2[i] = 0;
    };

    auto upd = [&] (auto&& self, int i, int l, int r, int x, int y, int k) -> void {
        push2(i, l, r);
        if (r < x or y < l) return;
        if (x <= l and r <= y) {
            lz2[i] += k;
            push2(i, l, r);
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md, x, y, k), self(self, 2*i+1, md+1, r, x, y, k);
        seg2[i] = seg2[2*i] + seg2[2*i+1];
    };

    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> int {
        push2(i, l, r);
        if (r < x or y < l) return 0LL;
        if (x <= l and r <= y) return seg2[i];
        int md = (l+r)/2;
        return self(self, 2*i, l, md, x, y) + self(self, 2*i+1, md+1, r, x, y);
    };

    vector<vector<ii>> lz(4*n);

    struct node {
        int mn, fmn, mn2, fmn2; 
        node() { fmn = fmn2 = 0; }
        node (int x) {
            mn = x, fmn = 1, mn2 = inf, fmn2 = 0;
        }
    };

    vector<node> seg(4*n);
    auto merge = [&] (node a, node b) {
        node c;
        if (a.mn2 == b.mn2 and b.mn2 == inf and a.mn == b.mn) {
            c = a;
            c.fmn += b.fmn;
            return c;
        }
        if (a.mn == b.mn) {
            c = a;
            c.fmn += b.fmn;
            c.mn2 = min(a.mn2, b.mn2), c.fmn2 = 0;
            if (a.mn2 == c.mn2) c.fmn2 += a.fmn2;
            if (b.mn2 == c.mn2) c.fmn2 += b.fmn2;
            return c;
        }
        if (a.mn > b.mn) swap(a, b);
        c.mn = a.mn, c.fmn = a.fmn;
        c.mn2 = min(b.mn, a.mn2);
        if (a.mn2 == c.mn2) c.fmn2 += a.fmn2;
        if (b.mn == c.mn2) c.fmn2 += b.fmn;
        return c;
    };

    auto push = [&] (int i, int l, int r) {
        for (auto [aa, bb] : lz[i]) {
            if (seg[i].mn <= aa) seg[i].mn = bb;
            if (l != r) lz[2*i].pb({aa, bb}), lz[2*i+1].pb({aa, bb});
        }
        lz[i].clear();
    };

    auto upd_ckmin = [&] (auto&& self, int i, int l, int r, int x, int y, int bound, int val) -> void {
        push(i, l, r);
        if (r < x or y < l) return;
        if (bound < seg[i].mn2 and x <= l and r <= y) {
            int prv = seg[i].mn;
            lz[i].pb({bound, val});
            push(i, l, r);
            //cerr << "after ckmin: " << "mn = " << seg[i].mn << " " << seg[i].fmn << " mn2 = " << seg[i].mn2 << " " << seg[i].fmn2 << endl;
            //cerr << "adding " << -seg[i].fmn << " to " << x+1 << ' ' << prv << endl;
            upd(upd, 1, 0, n-1, x+1, prv, -seg[i].fmn);
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md, x), self(self, 2*i+1, md+1, r, x);
        seg[i] = merge(seg[2*i], seg[2*i+1]);
    };
    
    auto upd_point = [&] (auto&& self, int i, int l, int r, int x, int k) -> void {
        push(i, l, r);
        if (r < x or x < l) return;
        if (l == r) {
            //cerr << "performing point update in " << l << ": " << "mn = " << seg[i].mn << " " << seg[i].fmn << " mn2 = " << seg[i].mn2 << " " << seg[i].fmn2 << endl;
            //cerr << "adding -1 to " << l << ' ' << seg[i].mn << endl;
            upd(upd, 1, 0, n-1, l, seg[i].mn, -1);
            seg[i] = node(k);
            //cerr << "adding 1 to " << l << ' ' << seg[i].mn << endl;
            upd(upd, 1, 0, n-1, l, seg[i].mn, 1);
            //cerr << "after point update: mn = " << seg[i].mn << " " << seg[i].fmn << " mn2 = " << seg[i].mn2 << " " << seg[i].fmn2 << endl;
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md, x, k);
        self(self, 2*i+1, md+1, r, x, k);
        seg[i] = merge(seg[2*i], seg[2*i+1]);
    };

    auto build2 = [&] (auto&& self, int i, int l, int r) -> void {
        if (l == r) {
            seg2[i] = 1;
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md), self(self, 2*i+1, md+1, r);
        seg2[i] = r-l+1;
    };

    auto build = [&] (auto&& self, int i, int l, int r) -> void {
        if (l == r) {
            seg[i] = node(l);
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md), self(self, 2*i+1, md+1, r);
        seg[i] = merge(seg[2*i], seg[2*i+1]);
    };

    // insira os intervalos em ordem de inicio
    // quero guardar em uma estrutura qual é o menor ponto de inicio que um dado i consegue alcancar, se forcarmos i para ser o ultimo elemento do intervalo
    // inserindo [l, r]: para todo i \in [r, n), se l <= val[i] <= r, faça val[i] = l-1, e incremente resp[i] em 1.
    // query: simplesmente retorne resp[l] + ... + resp[r] (depois de inserir intervalos comecando em l, l+1, ..., n-1).
    // como caralhos vou conseguir fazer isso? kkkkkkkkkk
    // ok, acho que sei como matar a condicao l <= val[i]: insira os intervalos em ordem decrescente de fim, e va updatando os intervalinhos de fim.
    // isso eh equivalente ao que estamos fazendo.
    // depois, faca val[l] = l (e resp[l] = 1).
    // tem muito a vibe da segtree beats, mas agora nao eh ckmin, eh algo estranho:
    // if (seg[i].mn <= K) update to K' < K.
    // e como fica o tag da lazy nesse caso? tenho vontade de soh dar um push back e ir atualizando um por um
    vector<int> big(n, -1);
    for (auto [l, r] : v) ckmax(big[l], r);

    build(build, 1, 0, n-1), build2(build2, 1, 0, n-1);

    for (int i = n-1; ~i; --i) {
        if (big[i] != -1) {
            // todo mundo que tiver valor >= big[i] vai ganhar eu, e vou updatar pra i-1.
        }
        for (auto j : queries[i]) {
            int r = qry[j].second;
            ans[j] = query(query, 1, 0, n-1, i, r);
        }
    }
    return ans;
}

vector<int> brute(int n, vector<int> p, vector<ii> qry) {
    vector<int> ans;
    for (auto [l, r] : qry) {
        int tot = 0;
        for (int x = l; x <= r; ++x) {
            for (int y = x; y <= r; ++y) {
                int mn = n, mx = 0;
                for (int k = x; k <= y; ++k) ckmax(mx, p[k]), ckmin(mn, p[k]);
                tot += (mx == mn + (y-x));
            }
        }
        ans.pb(tot);
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int n; cin >> n;
    vector<int> p(n);
    for (auto& x : p) cin >> x, --x;
    int q; cin >> q;
    vector<ii> qry(q);
    for (auto& [l, r] : qry) cin >> l >> r, --l, --r;
    auto ans = solve(n, p, qry);
    for (auto x : ans) cout << x << endl;
#else
    int t = 1;
    while (false) {
        int n = rnd(1, 5), q = 1;
        vector<int> p(n); iota(all(p), 0); shuffle(all(p), rng);
        vector<ii> qry(q);
        for (auto& [l, r] : qry) l = rnd(0, n-1), r = rnd(l, n-1);
        auto my = solve(n, p, qry);
        auto ans = brute(n, p, qry);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : p) cout << x + 1 << ' ';
            cout << endl;
            cout << q << endl;
            for (auto [l, r] : qry) cout << l + 1 << ' ' << r+1 << endl;
            cout << "Solve:" << ' ';
            for (auto x : my) cout << x << ' ';
            cout << endl;
            cout << "Brute:" << ' ';
            for (auto x : ans) cout << x << ' ';
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
    t = 5;
    while (t--) {
        int n = rnd(5, 8), q = 1;
        vector<int> p(n); iota(all(p), 0); shuffle(all(p), rng);
        vector<ii> qry(q);
        for (auto& [l, r] : qry) l = rnd(0, n-1), r = rnd(l, n-1);
        cout << n << endl;
        for (auto x : p) cout << x + 1 << ' ';
        cout << endl;
        cout << q << endl;
        for (auto [l, r] : qry) cout << l + 1 << ' ' << r + 1 << endl;
        cout << "intervals found: " << endl;
        auto my = solve(n, p, qry);
    }
#endif
}
