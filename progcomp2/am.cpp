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
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    struct node {
        int mx, s;
        node () {
            mx = s = 0;
        }
        node (int x) {
            mx = s = x;
        }
    }nulo;
    vector<node> seg(4*n);
    auto build = [&] (auto&& self, int i, int l, int r) -> void {
        if (l == r) {
            seg[i] = node(a[l]);
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md), self(self, 2*i+1, md+1, r);
        seg[i].mx = max(seg[2*i].mx, seg[2*i+1].mx);
        seg[i].s = seg[2*i].s + seg[2*i+1].s;
    };
    build(build, 1, 0, n-1);
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> int {
        if (r < x or y < l) return 0LL;
        if (x <= l and r <= y) return seg[i].s;
        int md = (l+r)/2;
        return self(self, 2*i, l, md, x, y) + self(self, 2*i+1, md+1, r, x, y);
    };
    auto upd_mod = [&] (auto&& self, int i, int l, int r, int x, int y, int k) -> void {
        if (r < x or y < l or seg[i].mx < k) return;
        if (l == r){
            seg[i] = node(seg[i].s % k);
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md, x, y, k), self(self, 2*i+1, md+1, r, x, y, k);
        seg[i].s = seg[2*i].s + seg[2*i+1].s;
        seg[i].mx = max(seg[2*i].mx, seg[2*i+1].mx);
    };
    auto upd_point = [&] (auto&& self, int i, int l, int r, int x, int k) -> void {
        if (l == r){
            seg[i] = node(k);
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x, k);
        else self(self, 2*i+1, md+1, r, x, k);
        seg[i].s = seg[2*i].s + seg[2*i+1].s;
        seg[i].mx = max(seg[2*i].mx, seg[2*i+1].mx);
    };
    while (m--) {
        int op; cin >> op;
        if (op == 1) {
            int l, r; cin >> l >> r; --l, --r;
            cout << query(query, 1, 0, n-1, l, r) << endl;
        } else if (op == 2) {
            int l, r, x; cin >> l >> r >> x; --l, --r;
            upd_mod(upd_mod, 1, 0, n-1, l, r, x);
        } else {
            int l, x; cin >> l >> x; --l;
            upd_point(upd_point, 1, 0, n-1, l, x);
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
