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

void solve() {
    int n, q; cin >> n >> q;
    vector<int> seg(4*n), qt_mx(4*n), lz(4*n);
    auto push = [&] (int i, int l, int r) {
        seg[i] += lz[i];
        if (l != r) lz[2*i] += lz[i], lz[2*i+1] += lz[i];
        lz[i] = 0;
    };
    auto init = [&] (auto&& self, int i, int l, int r) {
        qt_mx[i] = r-l+1;
        if (l == r) return;
        int md = (l+r)/2;
        self(self, 2*i, l, md), self(self, 2*i+1, md+1, r);
    };
    init(init, 1, 0, n-1);
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int y, int k) -> void {
        push(i, l, r);
        if (r < x or y < l) return;
        if (x <= l and r <= y) {
            lz[i] += k;
            push(i, l, r);
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md, x, y, k);
        self(self, 2*i+1, md+1, r, x, y, k);
        if (seg[2*i] > seg[2*i+1]) seg[i] = seg[2*i], qt_mx[i] = qt_mx[2*i];
        else if (seg[2*i+1] > seg[2*i]) seg[i] = seg[2*i+1], qt_mx[i] = qt_mx[2*i+1];
        else seg[i] = seg[2*i], qt_mx[i] = qt_mx[2*i] + qt_mx[2*i+1];
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> ii {
        push(i, l, r);
        if (r < x or y < l) return {0, 0};
        if (x <= l and r <= y) return {seg[i], qt_mx[i]};
        int md = (l+r)/2;
        auto [x1, x2] = self(self, 2*i, l, md, x, y);
        auto [y1, y2] = self(self, 2*i+1, md+1, r, x, y);
        if (x1 > y1) return {x1, x2};
        else if (y1 > x1) return {y1, y2};
        return {x1, x2+y2};
    };
    // fim, comeco
    vector<set<ii>> ranges(61);
    auto limpa = [&] (int x, int l, int r) {
        auto it = ranges[x].lower_bound({l, 0});
        bool tem_esq = 0, tem_dir = 0;
        while (it != end(ranges[x])) {
            auto [rx, lx] = *it;
            it = next(it);
            if (r < lx) break;
            // entao temos lx <= r, temos intersecao pois l <= rx!!
            //cout << "matando " << x << " " << lx << " " << rx << endl;
            ranges[x].erase({rx, lx});
            upd(upd, 1, 0, n-1, lx, rx, -1);
            if (lx < l) {
                ranges[x].insert({l-1, lx});
                tem_esq = 1;
                //cout << "vivendo " << x << " " <<  lx << " " << l-1 << endl;
                upd(upd, 1, 0, n-1, lx, l-1, 1);
            } 
            if (r < rx) {
                ranges[x].insert({rx, r+1});
                tem_dir = 1;
                //cout << "vivendo " << x << " " << r+1 << " " << rx << endl;
                upd(upd, 1, 0, n-1, r+1, rx, 1);
            }
        }
        return pair(tem_esq, tem_dir);
    };
    auto adiciona = [&] (int x, int l, int r) {
        auto [tem_esq, tem_dir] = limpa(x, l, r);
        upd(upd, 1, 0, n-1, l, r, 1);
        //cout << "vivendo " << x << " " << l << " " << r << endl;
        if (tem_esq and tem_dir) {
            auto it = ranges[x].lower_bound({l, 0});
            auto [r2, l2] = *it;
            it = prev(it); 
            auto [r1, l1] = *it;
            ranges[x].erase({r1, l1});
            ranges[x].erase({r2, l2});
            ranges[x].insert({r2, l1});
        } else if (tem_esq) {
            auto it = ranges[x].lower_bound({l, 0});
            it = prev(it); 
            auto [r1, l1] = *it;
            ranges[x].erase({r1, l1});
            ranges[x].insert({r, l1});
        } else if (tem_dir) {
            auto it = ranges[x].lower_bound({l, 0});
            auto [r2, l2] = *it;
            ranges[x].erase({r2, l2});
            ranges[x].insert({r2, l});
        } else {
            ranges[x].insert({r, l});
        }
    };
    while (q--) {
        int op, l, r; cin >> op >> l >> r;
        --l, --r;
        if (op == 1) {
            int x; cin >> x;
            adiciona(x, l, r);
        } else if (op == 2) {
            int x; cin >> x;
            limpa(x, l, r);
        } else {
            auto [a, b] = query(query, 1, 0, n-1, l, r);
            cout << a << " " << b << endl;
        }
        //cout << "status: ";
        //for (int i = 0; i < n; ++i) {
        //    cout << query(query, 1, 0, n-1, i, i).first << " ";
        //}
        //cout << endl;
        //auto [aa, aaa] = query(query, 1, 0, n-1, 2, 3);
        //cout << "biggie: " << aa << " " << aaa << endl;
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
