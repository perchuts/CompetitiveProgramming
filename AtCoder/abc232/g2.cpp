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
    vector<int> a(n), b(n), col, row;
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x, x = (m - x) % m;
    vector<ii> pt(4*n);
    for (int i = 0; i < n; ++i) {
        pt[i] = {a[i], b[i]};
        pt[i+n] = {a[i]+m, b[i]};
        pt[i+2*n] = {a[i], b[i]+m};
        pt[i+3*n] = {a[i]+m, b[i]+m};
    }
    for (auto [x, y] : pt) {
        row.pb(x);
        col.pb(y);
    }
    sort(all(row)); row.erase(unique(all(row)), end(row));
    sort(all(col)); col.erase(unique(all(col)), end(col));
    vector<int> ord(4*n); sort(all(ord), [&] (int i, int j) { return pt[i] < pt[j]; });
    vector<vector<ii>> g(4*n);
    vector<ii> seg(16*n, pair(-inf, -inf));
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int k) -> void {
        if (l == r) {
            ckmax(seg[i], pair(x, k));
            return;
        }
        int md = (l + r) / 2;
        if (x <= md) self(self, 2*i, l, md, x, k);
        else self(self, 2*i+1, md+1, r, x, k);
        seg[i] = max(seg[2*i], seg[2*i+1]);
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> ii {
        if (r < x or y < l) return pair(-inf, -inf);
        if (x <= l and r <= y) return seg[i];
        int md = (l + r) / 2;
        return max(self(self, 2*i, l, md, x, y), self(self, 2*i+1, md+1, r, x, y));
    };
    seg = vector<ii>(16*n, pair(-inf, -inf));
    for (int l = 0, r = 0; l != 4 * n; l = r) {
        while (r != 4*n and pt[ord[r]].first == pt[ord[l]].first) {
            // calcula opt a esquerda e a direita do cara
            int i = lower_bound(all(col), pt[ord[r]].second) - begin(col);
            auto esq = query(query, 1, 0, 4*n-1, 0, i);
            auto dir = query(query, 1, 0, 4*n-1, i, 4*n-1);
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
