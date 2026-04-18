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
// Wavelet Tree
//
// Usa O(sigma + n log(sigma)) de memoria,
// onde sigma = MAXN - MINN
// Depois do build, o v fica ordenado
// count(i, j, x, y) retorna o numero de elementos de
// v[i, j) que pertencem a [x, y]
// kth(i, j, k) retorna o elemento que estaria
// na poscicao k-1 de v[i, j), se ele fosse ordenado
// sum(i, j, x, y) retorna a soma dos elementos de
// v[i, j) que pertencem a [x, y]
// sumk(i, j, k) retorna a soma dos k-esimos menores
// elementos de v[i, j) (sum(i, j, 1) retorna o menor)
//
// Complexidades:
// build - O(n log(sigma))
// count - O(log(sigma))
// kth   - O(log(sigma))
// sum   - O(log(sigma))
// sumk  - O(log(sigma))

vector<int> esq[4*maxn];
vector<ll> pref[4*maxn];

struct wavelet {
    vector<int> v;
    int n;
    int minv, maxv;
    void build(int b, int e, int p, int l, int r) {
        int m = (l+r)/2; esq[p].push_back(0); pref[p].push_back(0);
        for (int i = b; i < e; i++) {
            esq[p].push_back(esq[p].back()+(v[i]<=m));
            pref[p].push_back(pref[p].back()+v[i]);
        }
        if (l == r) return;
        int m2 = stable_partition(begin(v)+b, begin(v)+e, [=](int i){return i <= m;}) - begin(v);
        build(b, m2, 2*p, l, m), build(m2, e, 2*p+1, m+1, r);
    }
    void build() {
        build(0, n, 1, minv, maxv);
    }
    wavelet(int n_, vector<int> v_, int minv_, int maxv_) {
        v = v_;
        n = n_;
        minv = minv_;
        maxv = maxv_;
        for (int i = 0; i < 4*maxv-minv; ++i) esq[i].clear(), pref[i].clear();
        build();
    };
    int count(int i, int j, int x, int y, int p, int l, int r) {
        if (y < l or r < x) return 0;
        if (x <= l and r <= y) return j-i;
        int m = (l+r)/2, ei = esq[p][i], ej = esq[p][j];
        return count(ei, ej, x, y, 2*p, l, m)+count(i-ei, j-ej, x, y, 2*p+1, m+1, r);
    }
    int count(int i, int j, int x, int y) {
        return count(i, j, x, y, 1, minv, maxv);
    }
    ll sum(int i, int j, int x, int y, int p, int l, int r) {
        if (y < l or r < x) return 0;
        if (x <= l and r <= y) return pref[p][j]-pref[p][i];
        int m = (l+r)/2, ei = esq[p][i], ej = esq[p][j];
        return sum(ei, ej, x, y, 2*p, l, m) + sum(i-ei, j-ej, x, y, 2*p+1, m+1, r);
    }
    ll sum(int i, int j, int x, int y) {
        return sum(i, j, x, y, 1, minv, maxv);
    }
};


ll solve_slow(int n, vector<int> p, vector<vector<int>> g) {
    vector<int> onde(n);
    for (int i = 0; i < n; ++i) onde[p[i]] = i;
    vector<int> seg(4*n+8);
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int q) -> void {
        if (l == r) {
            seg[i] = (q == 0 ? l : inf);
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x, q);
        else self(self, 2*i+1, md+1, r, x, q);
        seg[i] = min(seg[2*i], seg[2*i+1]);
    };
    auto build = [&] (auto&& self, int i, int l, int r) -> void {
        if (l == r) {
            seg[i] = l;
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md);
        self(self, 2*i+1, md+1, r);
        seg[i] = l;
    };
    vector<int> mex(n), prox_mex(n), replace_mex(n);
    vector<ll> sum_prox(n), sum(n);
    int T = 0;
    vector<int> l(n), r(n);
    auto dfs = [&] (auto&& self, int u, int par) -> void {
        l[u] = ++T;
        upd(upd, 1, 0, n+1, p[u], 1);
        mex[u] = seg[1];
        upd(upd, 1, 0, n+1, mex[u], 1), upd(upd, 1, 0, n+1, p[u], 0);
        replace_mex[u] = seg[1];
        upd(upd, 1, 0, n+1, p[u], 1);
        prox_mex[u] = seg[1];
        upd(upd, 1, 0, n+1, mex[u], 0);
        sum[u] = mex[u], sum_prox[u] = prox_mex[u];
        for (auto v : g[u]) {
            if (v == par) continue;
            self(self, v, u);
            sum[u] += sum[v];
            sum_prox[u] += sum_prox[v];
        }
        upd(upd, 1, 0, n+1, p[u], 0);
        r[u] = T;
    };
    build(build, 1, 0, n+1);
    dfs(dfs, 0, 0);
    ll base = accumulate(all(mex), 0LL), ans = base;
    vector<int> v1(n+1), v2(n+1);
    for (int i = 0; i < n; ++i) v1[l[i]] = mex[i], v2[l[i]] = prox_mex[i];
    wavelet wm2(n+1, v2, 0, n+3);
    vector<ll> score(n);
    for (int i = 0; i < n; ++i) {
        if (p[i] < mex[i]) continue;
        if (l[onde[mex[i]]] < l[i] or r[i] < l[onde[mex[i]]]) {
            //cout << "i: " << i << " caso1 " << endl;
            score[i] = base - sum[i] + sum_prox[i] - prox_mex[i] + replace_mex[i];
            //cout << sum_prox[i] << ' ' << prox_mex[i] << endl;
            if (l[i] != r[i]) {
                ll qt = wm2.count(l[i]+1, r[i]+1, p[i]+1, n+2);
                ll ss = wm2.sum(l[i]+1, r[i]+1, p[i]+1, n+2);
                score[i] += p[i] * qt - ss;
            } 
            // array v
            // process query(v, l, r, X): sum v[j] s.t. l <= j <= r, v[j] >= X, qtd of such j
            // do query(prox_mex, l[i]+1, r[i], p[i])
            ckmax(ans, score[i]);
        }
        else {
            //cout << "i: " << i << " caso2 " << endl;
            int j = onde[mex[i]];
            score[i] = base - (sum[i] - sum[j]) + (sum_prox[i] - sum_prox[j] - prox_mex[i] + replace_mex[i]);
            //cout << score << endl;
            // array v
            // process query(v, l, r, X): sum v[j] s.t. l <= j <= r, v[j] >= X, qtd of such j
            // do query(prox_mex, l[i]+1, r[i], p[i]) 
            {
                ll qt = wm2.count(l[i]+1, r[i]+1, p[i]+1, n+2);
                ll ss = wm2.sum(l[i]+1, r[i]+1, p[i]+1, n+2);
                score[i] += p[i] * qt - ss;
            }
            // do query(prox_mex, l[j], r[j], p[i]) 
            {
                ll qt = wm2.count(l[j], r[j]+1, p[i]+1, n+2);
                ll ss = wm2.sum(l[j], r[j]+1, p[i]+1, n+2);
                score[i] -= p[i] * qt - ss;
            }
            // do query(mex, l[j], r[j], p[i])

            //for (int k = 0; k < n; ++k) {
            //    if (l[i] < l[k] and l[k] <= r[i]) {
            //        if (l[j] <= l[k] and l[k] <= r[j]) 
            //            if (mex[k] > p[i]) score += p[i] - mex[k];
            //    }
            //}
        }
        //cout << ans << " " << i << endl;
    }
    wavelet wm(n+1, v1, 0, n+3);
    for (int i = 0; i < n; ++i) {
        if (p[i] < mex[i]) continue;
        if (l[onde[mex[i]]] < l[i] or r[i] < l[onde[mex[i]]]) {
        }
        else {
            {
                int j = onde[mex[i]];
                ll qt = wm.count(l[j], r[j]+1, p[i]+1, n+2);
                ll ss = wm.sum(l[j], r[j]+1, p[i]+1, n+2);
                score[i] += p[i] * qt - ss;
            }
            ckmax(ans, score[i]);
        }
    }
    // p[i] > mex[i] and replace_mex[i] is inside i's subtree
    // j = onde[replace_mex[i]]
    // base - (sum[i] - sum[j]) + (sum_prox[i] - sum_prox[j] - prox_mex[i] + replace_mex[i]) - \sum(mex[k] + p[i]), k inside j subtree and mex[k] > p[i]
    return ans;
}

int brute(int n, vector<int> p, vector<vector<int>> g) {
    int ans = 0;
    auto calc = [&] (vector<int> f) {
        vector<int> aux(n+10), m(n);
        auto dfs = [&] (auto&& self, int u, int par) -> void {
            aux[p[u]]++;
            while (aux[m[u]]) m[u]++;
            for (auto v : g[u]) {
                if (v == par) continue;
                self(self, v, u);
            }
            aux[p[u]]--;
        };
        dfs(dfs, 0, 0);
        return m;
    };
    auto mex = calc(p);
    ans = accumulate(all(mex), 0LL);
    for (int i = 0; i < n; ++i) {
        int temp = p[i]; 
        p[i] = mex[i]; 
        auto z = calc(p);
        ckmax(ans, accumulate(all(z), 0LL));
        p[i] = temp;
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> p(n); vector<vector<int>> g(n);
        for (auto& x : p) cin >> x;
        for (int i = 0; i < n-1; ++i) {
            int u, v; cin >> u >> v; --u, --v;
            g[u].pb(v), g[v].pb(u);
        }
        cout << solve_slow(n, p, g) << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(1e5, 2e5);
        vector<int> p(n); iota(all(p), 0); shuffle(all(p), rng);
        auto rotulo = p; shuffle(all(rotulo), rng);
        vector<ii> edg;
        vector<vector<int>> g(n);
        for (int i = 1; i < n; ++i) {
            int u = rotulo[i], v = rotulo[rnd(0, i-1)];
            g[u].pb(v), g[v].pb(u);
            edg.pb({u, v});
        }
        auto my = solve_slow(n, p, g);
        auto ans = solve_slow(n, p, g);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : p) cout << x << " ";
            cout << endl;
            for (auto [u, v] : edg) cout << u+1 << " " << v+1 << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
