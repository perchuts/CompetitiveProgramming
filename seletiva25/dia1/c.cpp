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
    int n, q; cin >> n >> q;
    vector<int> a(n), c(n);
    for (auto& x : c) cin >> x;
    for (auto& x : a) cin >> x;
    // seg de soma, setar range pra zero, encher range, andar pra frente a partir de um ponto
    struct node {
        int sum, tot_cap;
        node (int a, int b) {
            sum = a, tot_cap = b;
        }
        node(){}
    };
    vector<int> lz(4*n);
    vector<node> seg(4*n);
    // lz = -1: esvazia tudo
    // lz = 1: enche tudo
    // preciso setar um bicho tambem! -> fazer enquanto to andando
    auto push = [&] (int i, int l, int r) {
        if (lz[i] == -1) {
            seg[i].sum = 0;
            if (l != r) lz[2*i] = lz[2*i+1] = lz[i];
        }
        if (lz[i] == 1) {
            seg[i].sum = seg[i].tot_cap;
            if (l != r) lz[2*i] = lz[2*i+1] = lz[i];
        }
        lz[i] = 0;
    };
    auto build = [&] (auto&& self, int i, int l, int r) -> void {
        if (l == r) {
            seg[i] = node(a[l], c[l]);
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md), self(self, 2*i+1, md+1, r);
        seg[i] = node(seg[2*i].sum+seg[2*i+1].sum, seg[2*i].tot_cap + seg[2*i+1].tot_cap);
    };
    build(build, 1, 0, n-1);
    auto add = [&] (auto&& self, int i, int l, int r, int x, int& qt) -> void {
        push(i, l, r);
        if (r < x or qt == 0) return;
        if (l == r) {
            int aa = c[l] - seg[i].sum;
            seg[i].sum += min(aa, qt);
            qt -= min(qt, aa);
            return;
        }
        int md = (l+r) / 2;
        if (x <= l) {
            int tenho = seg[i].tot_cap - seg[i].sum;
            if (qt >= tenho) {
                lz[i] = 1;
                push(i, l, r);
                qt -= tenho;
            } else {
                self(self, 2*i, l, md, x, qt);
                self(self, 2*i+1, md+1, r, x, qt);
            }
        } else {
            self(self, 2*i, l, md, x, qt);
            self(self, 2*i+1, md+1, r, x, qt);
        }
        push(2*i, l, md), push(2*i+1, md+1, r);
        seg[i].sum = seg[2*i].sum + seg[2*i+1].sum;
    };
    auto rem = [&] (auto&& self, int i, int l, int r, int x, int& qt) -> void {
        push(i, l, r);
        if (r < x or qt == 0) return;
        if (l == r) {
            int aa = seg[i].sum;
            seg[i].sum = max(0LL, aa - qt);
            qt -= min(qt, aa);
            return;
        }
        int md = (l+r) / 2;
        if (x <= l) {
            int tenho = seg[i].sum;
            if (qt >= tenho) {
                lz[i] = -1;
                push(i, l, r);
                qt -= tenho;
            } else {
                self(self, 2*i, l, md, x, qt);
                self(self, 2*i+1, md+1, r, x, qt);
            }
        } else {
            self(self, 2*i, l, md, x, qt);
            self(self, 2*i+1, md+1, r, x, qt);
        }
        push(2*i, l, md), push(2*i+1, md+1, r);
        seg[i].sum = seg[2*i].sum + seg[2*i+1].sum;
    };
    while (q--) {
        int i, x; cin >> i >> x; --i;
        if (x == 0) continue;
        if (x < 0) {
            x *= -1;
            rem(rem, 1, 0, n-1, i, x);
        } else {
            add(add, 1, 0, n-1, i, x);
        }
    }
    auto go = [&] (auto&& self, int i, int l, int r) -> void {
        push(i, l, r);
        if (l == r) {
            cout << seg[i].sum << " ";
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md);
        self(self, 2*i+1, md+1, r);
    };
    go(go, 1, 0, n-1);
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
