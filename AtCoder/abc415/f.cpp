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
    string s; cin >> s;
    struct node {
        int best = 0, suf = 0, pref = 0, tot = 0;
        char pp = '$', ss = '$';
    } nulo;
    vector<node> seg(4*n);
    auto merge = [&] (node a, node b) {
        node c;
        c.pp = a.pp;
        c.ss = b.ss;
        c.pref = a.pref;
        c.suf = b.suf;
        c.best = max(a.best, b.best);
        c.tot = a.tot + b.tot;
        if (a.pref == a.tot and a.ss == b.pp) c.pref = a.tot + b.pref;
        if (b.suf == b.tot and a.ss == b.pp) c.suf = b.tot + a.suf;
        if (a.ss == b.pp) ckmax(c.best, a.suf + b.pref);
        return c;
    };
    auto upd = [&] (auto&& self, int i, int l, int r, int x, char c) -> void {
        if (l == r) {
            seg[i].pp = seg[i].ss = c;
            seg[i].best = seg[i].suf = seg[i].pref = seg[i].tot = 1;
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x, c);
        else self(self, 2*i+1, md+1, r, x, c);
        seg[i] = merge(seg[2*i], seg[2*i+1]);
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> node {
        if (r < x or y < l) return nulo;
        if (x <= l and r <= y) return seg[i];
        int md = (l+r)/2;
        return merge(self(self, 2*i, l, md, x, y), self(self, 2*i+1, md+1, r, x, y));
    };
    for (int i = 0; i < n; ++i) upd(upd, 1, 0, n-1, i, s[i]);
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int i; char c; cin >> i >> c;
            --i;
            upd(upd, 1, 0, n-1, i, c);
        } else {
            int l, r; cin >> l >> r; --l, --r;
            auto ans = query(query, 1, 0, n-1, l, r);
            cout << ans.best << endl;
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
