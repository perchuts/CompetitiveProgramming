#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

vector<int> solve(int n, int q, vector<iii> qq) {
    // need to support these operations:
    // 1. update v[i] to k
    // 2. ckmin(v[i], c) for i in [1, c]
    // 3. retrieve number of elements changed by operation two, and what were its previous values.
    // will use 3. to do operations in another segment tree that will keep the actual answer.
    // okay, smells like segment tree beats. seems like i want to use that [max, freq_max], [second_max, freq_second_max] technique
    // if max <= c: go away
    // if sm < c: update max to c, push lazily the update downards
    // if sm = -1 (all elements equal) do same as last case
    // else: (sm >= c): go downards recursively.

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

    vector<int> lz(4*n, n);

    struct node {
        int mx, fmx, mx2, fmx2; 
        node() { fmx = fmx2 = 0; }
        node (int x) {
            mx = x, fmx = 1, mx2 = -1, fmx2 = 0;
        }
    };

    vector<node> seg(4*n);
    auto merge = [&] (node a, node b) {
        node c;
        if (a.mx2 == b.mx2 and b.mx2 == -1 and a.mx == b.mx) {
            c = a;
            c.fmx += b.fmx;
            return c;
        }
        if (a.mx == b.mx) {
            c = a;
            c.fmx += b.fmx;
            c.mx2 = max(a.mx2, b.mx2), c.fmx2 = 0;
            if (a.mx2 == c.mx2) c.fmx2 += a.fmx2;
            if (b.mx2 == c.mx2) c.fmx2 += b.fmx2;
            return c;
        }
        if (a.mx < b.mx) swap(a, b);
        c.mx = a.mx, c.fmx = a.fmx;
        c.mx2 = max(b.mx, a.mx2);
        if (a.mx2 == c.mx2) c.fmx2 += a.fmx2;
        if (b.mx == c.mx2) c.fmx2 += b.fmx;
        return c;
    };

    auto push = [&] (int i, int l, int r) {
        if (seg[i].mx > lz[i]) seg[i].mx = lz[i];
        if (l != r) ckmin(lz[2*i], lz[i]), ckmin(lz[2*i+1], lz[i]);
        lz[i] = n;
    };

    auto upd_ckmin = [&] (auto&& self, int i, int l, int r, int x) -> void {
        push(i, l, r);
        if (l > x) return;
        if (seg[i].mx <= x) return;
        if (seg[i].mx2 < x and r <= x) {
            //cerr << "performing ckmin in " << l << ' ' << r << " (x = " << x << "): " << "mx = " << seg[i].mx << " " << seg[i].fmx << " mx2 = " << seg[i].mx2 << " " << seg[i].fmx2 << endl;
            int prv = seg[i].mx;
            ckmin(lz[i], x);
            push(i, l, r);
            //cerr << "after ckmin: " << "mx = " << seg[i].mx << " " << seg[i].fmx << " mx2 = " << seg[i].mx2 << " " << seg[i].fmx2 << endl;
            //cerr << "adding " << -seg[i].fmx << " to " << x+1 << ' ' << prv << endl;
            upd(upd, 1, 0, n-1, x+1, prv, -seg[i].fmx);
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
            //cerr << "performing point update in " << l << ": " << "mx = " << seg[i].mx << " " << seg[i].fmx << " mx2 = " << seg[i].mx2 << " " << seg[i].fmx2 << endl;
            //cerr << "adding -1 to " << l << ' ' << seg[i].mx << endl;
            upd(upd, 1, 0, n-1, l, seg[i].mx, -1);
            seg[i] = node(k);
            //cerr << "adding 1 to " << l << ' ' << seg[i].mx << endl;
            upd(upd, 1, 0, n-1, l, seg[i].mx, 1);
            //cerr << "after point update: mx = " << seg[i].mx << " " << seg[i].fmx << " mx2 = " << seg[i].mx2 << " " << seg[i].fmx2 << endl;
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

    build(build, 1, 0, n-1), build2(build2, 1, 0, n-1);

    vector<int> ans;
    for (auto [p, a, b] : qq) {
        if (p == 1) {
            int c = a, g = b;
            upd_ckmin(upd_ckmin, 1, 0, n-1, c-1);
            // now point update!
            upd_point(upd_point, 1, 0, n-1, c, g);
            // for i < c: v[i] = min(v[i], c)
            // v[c] = g
        } else {
            int l = a, r = b;
            ans.pb(query(query, 1, 0, n-1, l, r));
        }
    }
    return ans;
}

vector<int> brute(int n, int q, vector<iii> qq) {
    vector<int> A(n), ans; iota(all(A), 0);
    for (auto [p, a, b] : qq) {
        if (p == 1) {
            for (int i = 0; i < a; ++i) ckmin(A[i], a-1);
            A[a] = b;
        } else {
            int tot = 0;
            for (int i = 0; i <= b; ++i) {
                tot += max(0LL, min(A[i], b) - max(i, a) + 1);

            }
            ans.pb(tot);
        }
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int n, q; cin >> n >> q;
    vector<iii> qq(q);
    for (auto& [x, y, z] : qq) cin >> x >> y >> z, --y, --z;
    auto ans = solve(n, q, qq);
    for (auto x : ans) cout << x << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 100), q = rnd(1, 1000);
        vector<iii> qq(q);
        for (auto& [x, y, z] : qq) {
            x = rnd(1, 2);
            y = rnd(0, n-1), z = rnd(y, n-1);
        }
        auto my = solve(n, q, qq);
        auto ans = brute(n, q, qq);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << q << endl;
            for (auto [x, y, z] : qq) cout << x << ' ' << y+1 << ' ' << z+1 << endl;
            cout << "Solve: ";
            for (auto x : my) cout << x << ' ';
            cout << endl;
            cout << "Brute: ";
            for (auto x : ans) cout << x << ' ';
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
