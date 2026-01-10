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
    // eh so pegar o valor maximo ponto a ponto neh
    vector<vector<int>> seg(4*n, vector<int>(4));
    vector<int> c = {1, -1};
    auto upd = [&] (auto&& self, int i, int l, int r, int k, int x, int y) -> void {
        if (l == r) {
            for (int j = 0; j < 4; ++j) {
                seg[i][j] = c[(j>1)] * x + c[j%2] * y;
            }
            return;
        }
        int md = (l+r)/2;
        if (k <= md) self(self, 2*i, l, md, k, x, y);
        else self(self, 2*i+1, md+1, r, k, x, y);
        for (int j = 0; j < 4; ++j) seg[i][j] = max(seg[2*i][j], seg[2*i+1][j]);
    };
    for (int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        upd(upd, 1, 0, n-1, i, x, y);
    }
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y, array<int, 4> z) -> int {
        if (r < x or y < l) return 0LL;
        if (x <= l and r <= y) {
            int opt = 0;
            for (int j = 0; j < 4; ++j) ckmax(opt, seg[i][j] - z[j]);
            return opt;
        }
        int md = (l+r)/2;
        return max(self(self, 2*i, l, md, x, y, z), self(self, 2*i+1, md+1, r, x, y, z));
    };
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int i, x, y; cin >> i >> x >> y;
            upd(upd, 1, 0, n-1, i-1, x, y);
        } else {
            int l, r, x, y; cin >> l >> r >> x >> y;
            array<int, 4> z;
            for (int j = 0; j < 4; ++j) z[j] = c[(j>1)] * x + c[j%2] * y;
            cout << query(query, 1, 0, n-1, l-1, r-1, z) << endl;
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
