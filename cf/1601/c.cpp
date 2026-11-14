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
    vector<int> lz(4*n+4);
    vector<ii> seg(4*n+4);
    auto push = [&] (int i, int l, int r) {
        if (lz[i] == 0) return;
        seg[i].first += lz[i];
        if (l != r) lz[2*i] += lz[i], lz[2*i+1] += lz[i];
        lz[i] = 0;
    };
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
        seg[i] = min(seg[2*i], seg[2*i+1]);
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> ii {
        push(i, l, r);
        if (l <= x and y <= r) return seg[i];
        if (y < l or r < x) return pair(inf, -1);
        int md = (l+r)/2;
        return min(self(self, 2*i, l, md, x, y), self(self, 2*i+1, md+1, r, x, y));
    };
    vector<int> a(n), b(m);
    for (auto& x : a) cin >> x;
    vector<int> ord(n); iota(all(ord), 0);
    sort(all(ord), [&] (int x, int y) { return a[x] < a[y]; });
    for (auto& x : b) cin >> x;
    sort(all(b));
    vector<int> bit(n+1);
    auto I = [&] (int x) {
        while (x <= n) bit[x]++, x += x & (-x);
    };
    auto Q = [&] (int x) {
        int resp = 0;
        while (x) resp += bit[x], x -= x & (-x);
        return resp;
    };
    int ptr = 0, lst = 0, ans = 0;
    for (int l = n-1, r = n-1; ~r; l = r) {
        while (~r and a[ord[l]] == a[ord[r]]) r--;
        for (int i = l; i > r; --i) ans += Q(ord[i]);
        for (int i = l; i > r; --i) I(ord[i]+1);
    }
    // initially, we start with -infinity
    for (int i = 1; i <= n; ++i) upd(upd, 1, 0, n, i, n, 1);
    for (int l = 0, r = 0; r != m; l = r) {
        while (r != m and b[l] == b[r]) r++;
        int old = ptr;
        while (ptr != n and a[ord[ptr]] <= b[l]) upd(upd, 1, 0, n, ord[ptr++]+1, n, -1);
        while (old != n and a[ord[old]] < b[l]) upd(upd, 1, 0, n, 0, ord[old++], 1);
        auto [opt, pos] = query(query, 1, 0, n, lst, n);
        while (old != ptr) upd(upd, 1, 0, n, 0, ord[old++], 1);
        ans += opt * (r-l);
        lst = pos;
    }
    cout << ans << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
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
