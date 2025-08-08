#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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

struct node {
    node *l, *r;
    int pri, cnt;
    ii mn, mx;
    node (int p, int v, int i) {
        pri = p, l = r = NULL;
        mn = mx = {v, i};
        cnt = 1;
    }
};

int get_cnt(node* x) {
    return x ? x->cnt : 0;
}
ii get_mn(node* x) {
    return x ? x->mn : pair(inf, inf);
}
ii get_mx(node* x) {
    return x ? x->mx : pair(-inf, inf);
}

void upd(node* x) {
    if (x) x->cnt = get_cnt(x->l) + get_cnt(x->r) + 1, ckmax(x->mx, max(get_mx(x->l), get_mx(x->r))), ckmin(x->mn, min(get_mn(x->l), get_mn(x->r)));
}

void merge(node* &t, node *l, node *r) {
    if (!l or !r) {
        t = (l ? l : r);
        return;
    }
    if (l->pri > r->pri) {
        merge(l->r, l->r, r), t = l;
    } else {
        merge(r->l, l, r->l), t = r;
    }
    upd(t);
}
// split pseudo-code:
// split(esq, dir, t1, V):
// se t1->val <= V:
// 
// se t1->val > V:
//
void split(node *t, node* &l, node* &r, int key, int add = 0) {
    if (!t) {
        l = r = NULL;
        return;
    }
    int esq = get_cnt(t->l) + add;
    if (key <= esq) {
        split(t->l, l, t->l, key, add), r = t;
    } else {
        split(t->r, t->r, r, key, esq+1), l = t;
    }
    upd(t);
}

void add(node* &t, int onde, int val) {
    node* s = new node(rnd(0, 1e9), val, onde);
    node *t1, *t2;
    split(t, t1, t2, onde);
    merge(t, t1, s);
    merge(t, t, t2);
}

void kill(node* &t, int onde) {
    node *t1, *t2, *fodas;
    split(t, t1, t2, onde-1);
    split(t2, fodas, t2, 1);
    merge(t, t1, t2);
}

array<int, 4> query(node* &t, int l, int r) {
    node *t1, *t2, *t3;
    split(t, t1, t2, r);
    split(t1, t3, t1, l-1);
    ii mn = get_mn(t1), mx = get_mx(t1);
    merge(t1, t3, t1);
    merge(t1, t1, t2);
    return {mn.first, mn.second, mx.first, mx.second};
}

void solve() {
    int n, k; cin >> n >> k;
    vector<int> p(n), pos(n);
    for (auto& x : p) cin >> x, --x;
    for (int i = 0; i < n; ++i) cin >> p[i], pos[p[i]] = i;
    node* root = NULL;
    for (int i = 0; i < n; ++i) add(root, pos[i], i);
    for (int i = 0; i < n; ++i) {
        auto arr = query(root, 1, n);
        int val = arr[1];
        cout << arr[0] << ' ' << arr[1] << ' ' << arr[2] << ' ' << arr[3] << endl;
        if (arr[0] != i) {
            exit(0);
        }
        assert(arr[0] == i);
        int l = 0, r = val, opt = r;
        while (l <= r) {
            int md = l + (r-l+1)/2;
            auto qu = query(root, md+1, val+1);
            if (qu[2] < n and qu[0] >= i + k) r = md-1, opt = md;
            else l = md+1;
        }
        cout << "colocando: " << opt+1 << endl;
        kill(root, val+1);
        add(root, opt, inf);
    }
    cout << endl;
    // solucao facil com treap: mantem p^-1; extrai o minimo. faz busca binaria pra achar quem vai ficar ali no final.
    // suponha q vc tava no R e vai parar no L. oq vc vai fazer eh shiftar p^-1[L, R] ciclicamente 1 vez pra direita.
    // isso eh o mesmo que popar o R (2 splits 1 merge) e pushar o R atras do L (1 split 2 merges)
    // agr seta p^-1[L] pra infinito
    // aprender treap!!


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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
