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
const int maxn = 6e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int pot[maxn], P;

struct node {
    int pr, cnt, hash, rhash, val;
    // lets code an implicit treap right away
    node *l, *r;
    node (int k) {
        l = r = NULL;
                val = k;
        pr = rnd(0, 1e18);
        cnt = 0;
    }
    node (int k, int p) {
        l = r = NULL;
        pr = p;
                val = k;
        cnt = 0;
    }
};

using pnode = node*;

int cnt(pnode t) {
    return (t ? t->cnt : 0);
}

void upd_hash(pnode t) {
        if (!t) return;
        int dir = cnt(t->r), esq = cnt(t->l);
        int hl = (t->l ? t->l->hash : 0);
        int hr = (t->r ? t->r->hash : 0);
        int hlr = (t->l ? t->l->rhash : 0);
        int hrr = (t->r ? t->r->rhash : 0);
        t->hash = (hl + (t->val)*pot[esq] + pot[esq+1]*hr)%mod;
        t->rhash = (hrr + (t->val)*pot[dir] + pot[dir+1]*hlr)%mod;
}

void upd_cnt(pnode t) {
    if (t)
        t->cnt = 1 + cnt(t->l) + cnt(t->r);
}

void upd(pnode t) {
        upd_cnt(t);
        upd_hash(t);
}

void split(pnode t, pnode &l, pnode &r, int k) {
    if (!t) return void(l = r = NULL);
    if (k <= cnt(t->l))
        split(t->l, l, t->l, k), r = t;
    else
        split(t->r, t->r, r, k-1-cnt(t->l)), l = t;

        upd(t);
}

// l eh menor em chave que r (todas as chaves)
void merge(pnode &t, pnode l, pnode r) {
    if (!l or !r) t = l ? l : r;
    else if (l->pr > r->pr) merge(l->r, l->r, r), t = l;
    else merge(r->l, l, r->l), t = r;
    upd(t);
}

void insert(pnode& t, int k, int x) {
    pnode l, r;
    split(t, l, r, k);
    pnode sexo = new node(x);
    merge(l, l, sexo);
    merge(t, l, r);
}

void erase(pnode& t, int l, int r) {
    // erase segment from L to R
    pnode t1, t2, t3;
    assert(r < cnt(t));
    split(t, t1, t2, l);
    split(t2, t2, t3, r-l+1);;
    merge(t, t1, t3);
}

bool query(pnode& t, int l, int r) {
    pnode t1, t2, t3;
    assert(r < cnt(t));
    split(t, t1, t2, l);
    split(t2, t2, t3, r-l+1);
        int ret = ((t2->hash) == (t2->rhash));
    merge(t, t1, t2);
    merge(t, t, t3);
        return ret;
}
void solve() {
        P = rnd(256, mod-1);
        pot[0] = 1;
        for (int i = 1; i < maxn; ++i) pot[i] = P * pot[i-1] % mod;
        int n, q; cin >> n >> q;
        pnode sexo = NULL;
        for (int i = 0; i < n; ++i) {
                char c; cin >> c;
                insert(sexo, i, int(c));
        }
        while (q--) {
                int op; cin >> op;
                if (op == 1) {
                        int l, r; cin >> l >> r; --l, --r;
                        erase(sexo, l, r);
                } else if (op == 2) {
                        char c; int i; cin >> c >> i; --i;
                        insert(sexo, i, int(c));
                } else {
                        int l, r; cin >> l >> r; --l, --r;
                        int ret = query(sexo, l, r);
                        cout << (ret ? "yes" : "no") << endl;
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
