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
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    struct node {
        int pref, suf, tot, opt, tot_pos;
        int pref_out, suf_out, opt_out;
    };
    auto merge = [&] (node a, node b) {
        node c;
        c.tot = a.tot + b.tot;
        c.tot_pos = a.tot_pos + b.tot_pos;
        if (a.tot + b.pref >= a.pref) {
            c.pref = a.tot + b.pref;
            c.pref_out = b.pref_out;
        } else {
            c.pref = a.pref;
            c.pref_out = a.pref_out + b.tot_pos;
        }
        if (a.suf + b.tot >= b.suf) {
            c.suf = a.suf + b.tot;
            c.suf_out = a.suf_out;
        } else {
            c.suf = b.suf;
            c.suf_out = a.tot_pos + b.suf_out;
        }
        int m = max({a.opt, b.opt, a.suf+b.pref});
        c.opt = m;
        if (m == a.opt) {
            c.opt_out = a.opt_out + b.tot_pos;
        } else if (m == b.opt) {
            c.opt_out = a.tot_pos + b.opt_out;
        } else {
            c.opt_out = a.suf_out + b.pref_out;
        }
        return c;
    };
    vector<node> seg(4*n);
    auto build = [&] (auto&& self, int i, int l, int r) -> void {
        if (l == r) {
            if (a[l] == 0) {
                seg[i].tot = -1;
                seg[i].pref_out = seg[i].opt_out = seg[i].suf_out = seg[i].tot_pos = seg[i].pref = seg[i].suf = seg[i].opt = 0;
            } else {
                seg[i].tot = seg[i].tot_pos = seg[i].pref = seg[i].suf = seg[i].opt = a[l];
                seg[i].pref_out = seg[i].opt_out = seg[i].suf_out = 0;
            }
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md), self(self, 2*i+1, md+1, r);
        seg[i] = merge(seg[2*i], seg[2*i+1]);
    };
    auto upd = [&] (auto&& self, int i, int l, int r, int x) -> void {
        if (l == r) {
            if (a[l] == 0) {
                seg[i].tot = -1;
                seg[i].pref_out = seg[i].opt_out = seg[i].suf_out = seg[i].tot_pos = seg[i].pref = seg[i].suf = seg[i].opt = 0;
            } else {
                seg[i].tot = seg[i].tot_pos = seg[i].pref = seg[i].suf = seg[i].opt = a[l];
                seg[i].pref_out = seg[i].opt_out = seg[i].suf_out = 0;
            }
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x);
        else self(self, 2*i+1, md+1, r, x);
        seg[i] = merge(seg[2*i], seg[2*i+1]);
    };
    build(build, 1, 0, n-1);
    while (q--) {
        int i, v; cin >> i >> v;
        --i;
        a[i] = v;
        upd(upd, 1, 0, n-1, i);
        int score = seg[1].opt_out + seg[1].tot_pos - seg[1].opt_out - seg[1].opt;
        cout << score << endl;
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
