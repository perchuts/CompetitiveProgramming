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
    int N = 1e6 + 10;
    vector<int> a(n), tipo(n), seg(4*N), qt(4*N);
    vector<multiset<int>> mt(3);
    auto upd = [&] (auto&& self, int i, int l, int r, int pos, int x, int y) -> void {
        if (l == r) {
            seg[i] += x;
            qt[i] += y;
            return;
        }
        int md = (l+r)/2;
        if (pos <= md) self(self, 2*i, l, md, pos, x, y);
        else self(self, 2*i+1, md+1, r, pos, x, y);
        seg[i] = seg[2*i] + seg[2*i+1];
        qt[i] = qt[2*i] + qt[2*i+1];
    };
    auto query = [&] (auto&& self, int i, int l, int r, int k) -> int {
                          if (k == 0) return 0LL;
        if (l == r) {
            assert(k <= qt[i]);
            return k * l;
        }
        int md = (l+r)/2;
        if (k <= qt[2*i+1]) return self(self, 2*i+1, md+1, r, k);
        return self(self, 2*i, l, md, k-qt[2*i+1]) + seg[2*i+1];
    };
    int Z = 1000000;
    for (int i = 0; i < n; ++i) cin >> a[i] >> tipo[i], mt[tipo[i]].insert(a[i]), upd(upd, 1, 1, Z, a[i], a[i], 1);
    while (q--) {
        int pos, na, nt; cin >> pos >> na >> nt;
        --pos;
        upd(upd, 1, 1, Z, a[pos], -a[pos], -1);
        mt[tipo[pos]].erase(mt[tipo[pos]].find(a[pos]));
        tipo[pos] = nt;
        a[pos] = na;
        upd(upd, 1, 1, Z, a[pos], a[pos], 1);
        mt[tipo[pos]].insert(a[pos]);
        if (mt[2].empty()) {
            cout << seg[1] << endl;
            continue;
        }
        if (mt[1].empty()) {
            cout << 2 * seg[1] - (*begin(mt[2])) << endl;
            continue;
        }
        if (*begin(mt[2]) > *prev(end(mt[1]))) {
            cout << query(query, 1, 1, Z, sz(mt[2])-1) + (*prev(end(mt[1]))) + seg[1] << endl;
        } else {
            cout << query(query, 1, 1, Z, sz(mt[2])) + seg[1] << endl;
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
