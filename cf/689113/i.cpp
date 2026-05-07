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
    int n, q, x; cin >> n >> q >> x;
    vector<int> a(n);
    for (auto& y : a) cin >> y;
    // ideia central: x = p1^e1 + ... + pk ^ ek
    // f[m] = p1^{e1+(m>>0&1)} + ... + pk ^ {ek + (m>>(k-1))&1}
    // flag[m][i] = (a[i] % f[m] == 0)
    // sejam [lm1, rm1], ... [lmtm, rmtm] os intervalos maximais com flag[m][i] = 1, e S a soma dos escolhes dos tams + 1.
    // faça um inc-exc sobre esses valores e o popcount do m.
    // primorial vai ter no maximo 6 primos, entao podemos guardar uma seg por f[m], e atualizar devidamente. a seg guarda a soma dos escolhes.
    // alem disso, deve guardar o prefixo/sufixo maximal = 1.
    // no fim, a solucao fica O((N+Q) log N 2 ^ k)
    // apertadissimo! bem arriscado de fazer isso passar... mas vamos la!
    vector<int> p;
    int cur = x;
    for (int i = 2; i <= x; ++i) {
        if (cur % i == 0) {
            while (cur % i == 0) cur /= i;
            p.pb(i);
        }
    }
    int k = sz(p);
    vector<int> f((1<<k), x);
    struct node {
        int pr = 0, suf = 0, tot = 0, tam = 0;
    } nulo;
    vector<vector<node>> seg(1<<k, vector<node>(4*n));
    auto merge = [&] (node& a_, node& b_) {
        node c;
        c.tam = a_.tam + b_.tam;
        c.pr = (a_.pr == a_.tam ? a_.tam + b_.pr : a_.pr);
        c.suf = (b_.suf == b_.tam ? b_.tam + a_.suf : b_.suf);
        if (a_.suf and b_.pr) c.tot = a_.tot + b_.tot - a_.suf*(a_.suf+1)/2 - b_.pr*(b_.pr+1)/2 + (a_.suf+b_.pr)*(a_.suf+b_.pr+1)/2;
        else c.tot = a_.tot + b_.tot;
        return c;
    };
    auto build = [&] (auto&& self, int i, int l, int r) -> void {
        if (l == r) {
            for (int j = 0; j < (1 << k); ++j) {
                seg[j][i].tam = 1;
                seg[j][i].pr = seg[j][i].suf = seg[j][i].tot = (a[l] % f[j] == 0);
            }
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md), self(self, 2*i+1, md+1, r);
        for (int j = 0; j < (1 << k); ++j) {
            seg[j][i] = merge(seg[j][2*i], seg[j][2*i+1]);
        }
    };
    for (int i = 0; i < (1 << k); ++i) {
        for (int j = 0; j < k; ++j) {
            if (i >> j & 1) f[i] *= p[j];
        }
    }
    vector<node> aux(1<<k);
    int cur_query = -1, id_query = 0;
    auto upd = [&] (auto&& self, int i, int l, int r, int X) -> void {
        if (l == r) {
            for (int j = 0; j < (1 << k); ++j) {
                seg[j][i].tam = 1;
                seg[j][i].pr = seg[j][i].suf = seg[j][i].tot = (a[l] % f[j] == 0);
            }
            return;
        }
        int md = (l+r)/2;
        if (X <= md) self(self, 2*i, l, md, X);
        else self(self, 2*i+1, md+1, r, X);
        for (int j = 0; j < (1 << k); ++j) {
            seg[j][i] = merge(seg[j][2*i], seg[j][2*i+1]);
        }
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x_, int y_) -> void {
        if (r < x_ or y_ < l) return;
        if (x_ <= l and r <= y_) {
            for (int j = 0; j < (1 << k); ++j) {
                if (id_query != cur_query) aux[j] = seg[j][i];
                else aux[j] = merge(aux[j], seg[j][i]);
            }
            id_query = cur_query;
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md, x_, y_);
        self(self, 2*i+1, md+1, r, x_, y_);
    };
    build(build, 1, 0, n-1);
    cout << "primes: ";
    cout << k << endl;
    for (auto y : p) cout << y << " ";
    cout << endl;
    while (q--) {
        id_query++;
        int op; cin >> op;
        if (op == 1) {
            int i, y; cin >> i >> y; --i;
            a[i] = y;
            upd(upd, 1, 0, n-1, i);
        } else {
            int l, r; cin >> l >> r; --l, --r;
            query(query, 1, 0, n-1, l, r);
            int ans = 0;
            for (int i = 0; i < (1 << k); ++i) {
                if (__builtin_popcount(i) % 2) ans -= aux[i].tot;
                else ans += aux[i].tot;
            }
            for (int i = 0; i < (1 << k); ++i) cout << aux[i].tot << ' ';
            cout << endl;
            cout << ans << endl;
        }
    }
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
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
