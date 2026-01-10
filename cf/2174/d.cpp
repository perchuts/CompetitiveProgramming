#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
	using ord_set = tree<T, null_type, less<T>, rb_tree_tag,
	tree_order_statistics_node_update>;
	
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

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
    vector<iii> edg(m);
    for (auto& [w, u, v] : edg) cin >> u >> v >> w, --u, --v;
    vector<int> par(n), lvl(n); iota(all(par), 0);
    auto findp = [&] (auto&& self, int u) -> int {
        return par[u] = (par[u] == u ? u : self(self, par[u]));
    };
    sort(all(edg));
    {
        auto unite = [&] (int u, int v) {
            u = findp(findp, u), v = findp(findp, v);
            if (u == v) return false;
            if (lvl[u] < lvl[v]) swap(u, v);
            par[v] = u;
            if (lvl[u] == lvl[v]) lvl[u]++;
            return true;
        };
        int foi = 0, tot = 0;
        for (int i = 0; i < n-1; ++i) {
            auto [w, u, v] = edg[i];
            tot += w;
            foi += unite(u, v);
        }
        if (foi != n-1) {
            cout << tot << endl;
            return;
        }
    }
    if (m == n-1) {
        cout << -1 << endl;
        return;
    }
    iota(all(par), 0), lvl = vector<int>(n, 1);
    vector<int> skate;
    vector<ord_set<int>> sexo(n);
    for (int i = 0; i < m; ++i) {
        auto [w, u, v] = edg[i];
        skate.pb(m*w+i);
        sexo[u].insert(m*w+i);
        sexo[v].insert(m*w+i);
    }
    int ans = 1e18;
    bool ok = false;
    // deixar esse node sozinho
    vector<array<int, 2>> child(2*n-1);
    vector<int> rotulo(n), w_tree(n); rotulo = par;
    auto queries = edg;
    int h = 0;
    auto search = [&] (int comp) {
        int l = 0, r = 2e9, opt = r, want = n - lvl[comp];
        {
            int eu = sexo[comp].order_of_key((r+1)*m);
            int tudo = lower_bound(all(skate), ((r+1)*m)) - begin(skate);
            if (tudo - eu < want) return;
        }
        ok = true;
        while (l <= r) {
            int md = l + (r-l+1)/2;
            int eu = sexo[comp].order_of_key((md+1)*m);
            int tudo = lower_bound(all(skate), ((md+1)*m)) - begin(skate);
            int tot = tudo - eu;
            if (tot <= want) opt = md, l = md+1;
            else r = md-1;
        }
        int eu = sexo[comp].order_of_key((opt+1)*m);
            int tudo = lower_bound(all(skate), ((opt+1)*m)) - begin(skate);
        int add = (want - (tudo-eu)) * (opt+1);
        queries.pb({opt, inf + h-1, add + w_tree[comp]});
        // preciso agora somar tudo do sexo[comp] ateh val...
    };
    for (int i = 0; i < n; ++i) h++, search(i);
    for (int i = 0; i < n-1; ++i) {
        auto [w, u, v] = edg[i];
        u = findp(findp, u), v = findp(findp, v);
        int nr = h++;
        if (sz(sexo[u]) < sz(sexo[v])) swap(u, v);
        child[nr][0] = rotulo[u], child[nr][1] = rotulo[v];
        for (auto z : sexo[v]) sexo[u].insert(z);
        par[v] = u, lvl[u] += lvl[v];
        w_tree[u] += w_tree[v] + w;
        rotulo[u] = nr;
        if (i != n-2) search(u);
    }
    sort(all(queries));
    vector<int> ini(2*n-1), fim(2*n-1), pai(2*n-1), jump(2*n-1), height(2*n-1);
    int t = 0;
    auto dfs = [&] (auto&& self, int u) -> void {
        //cout << u << ": ";
        ini[u] = ++t;
        if (u >= n) {
            int a = child[u][0], b = child[u][1];
            height[a] = height[b] = height[u] + 1;
            pai[a] = pai[b] = u;
            jump[a] = jump[u], jump[b] = b;
            //cout << a << ' ' << b << endl;
            self(self, a), self(self, b);
        } //else cout << "leaf" << endl;
        fim[u] = t;
    };
    auto is_anc = [&] (int u, int v) {
        return (ini[u] <= ini[v] and fim[v] <= fim[u]);
    };
    auto lca = [&] (int u, int v) {
        if (lvl[u] < lvl[v]) swap(u, v);
        //cout << "lca de " << u << ' ' << v << " = ";
        if (is_anc(v, u)) return v;
        while (!is_anc(u, v) and !is_anc(v, u)) {
            if (v != jump[v] and !is_anc(jump[v], u)) v = jump[v];
            else if (u != jump[u] and !is_anc(jump[u], v)) u = jump[u];
            else {
                assert(u == jump[u] or v == jump[v]);
                if (u == jump[u]) u = pai[u];
                else v = pai[v];
            }
        }
        return (height[u] < height[v] ? u : v);
    };
    int root = h-1; jump[root] = pai[root] = root;
    dfs(dfs, root);
    int N = t + 5;
    vector<int> seg(4*N);
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int k) -> void {
        if (l == r) {
            seg[i] += k;
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x, k);
        else self(self, 2*i+1, md+1, r, x, k);
        seg[i] = seg[2*i] + seg[2*i+1];
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> int {
        if (r < x or y < l) return 0LL;
        if (x <= l and r <= y) return seg[i];
        int md = (l+r)/2;
        return self(self, 2*i, l, md, x, y) + self(self, 2*i+1, md+1, r, x, y);
    };
    int ss = 0;
    for (auto [a, b, c] : queries) {
        if (b >= inf) {
            b -= inf;
            assert(b != root);
            if (b == 9) {
                //cout << ini[b] << ' ' << fim[b] << endl;
                //cout << "a query deu: " <<  query(query, 1, 0, N-1, ini[b], fim[b])  << endl;
            }
            ckmin(ans, ss - query(query, 1, 0, N-1, ini[b], fim[b]) + c);
        } else {
            ss += a;
            //cout << "adding " << a << " to " << b << ' ' << c << endl;
            upd(upd, 1, 0, N-1, ini[b], a);
            upd(upd, 1, 0, N-1, ini[c], a);
            int l = lca(b, c);
            //cout << "adding " << -a << " to " << ini[l] << endl;
            upd(upd, 1, 0, N-1, ini[l], -a);
        }
    }
    cout << (ok ? ans : -1) << endl;
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


