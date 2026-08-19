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
	int n; cin >> n;
    vector<int> color(n);
    for (int i = 0; i < n; ++i) {
        char c; cin >> c;
        color[i] = (c == 'B');
    }
    vector<vector<int>> val(2, vector<int>(n));
    for (auto& x : val) for (auto& y : x) cin >> y;
    // (x, y) -> (teto(x/2)+teto(y/2), chao(x/2)+chao(y/2))
    struct node {
        array<int, 2> qt;
        array<array<int, 4>, 2> sum;
        node () {
            qt = {0};
            sum = {0};
        }
    } nulo;
    vector<node> seg(4*n);
    auto merge = [&] (node a, node b) {
        node c;
        c.qt[0] = a.qt[0] + b.qt[0], c.qt[1] = a.qt[1] + b.qt[1];
        int xx = (a.qt[0]+1)/2 + (a.qt[1]+1)/2, yy = a.qt[0]/2 + b.qt[0]/2;
        for (int i = 0; i < 4; ++i) {
            c.sum[0][i] = a.sum[0][i] + b.sum[0][2 * (a.qt[1]&1) + (a.qt[0]&1)];
            c.sum[1][i] = a.sum[1][i] + b.sum[0][2 * (yy) + xx];
        }
        return c;
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> node {
        if (r < x or y < l) return nulo;
        if (x <= l and r <= y) return seg[i];
        int md = (l+r)/2;
        return merge(self(self, 2*i, l, md, x, y), self(self, 2*i+1, md+1, r, x, y));
    };
    auto upd = [&] (auto&& self, int i, int l, int r, int x) -> void {
        if (l == r) {
            seg[i].qt[color[l]] = 1, seg[i].qt[color[l]^1] = 0;
            seg[i].sum[0] = {val[0][l]};
            seg[i].sum[1] = {val[0][l]};
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x);
        else self(self, 2*i+1, md+1, r, x);
        seg[i] = merge(seg[2*i], seg[2*i+1]);
    };
    auto build = [&] (auto&& self, int i, int l, int r) -> void {
        if (l == r) {
            seg[i].qt[color[l]] = 1, seg[i].qt[color[l]^1] = 0;
            return;
        }
        int md = (l+r)/2;
		self(self, 2*i, l, md), self(self, 2*i+1, md+1, r);
        seg[i] = merge(seg[2*i], seg[2*i+1]);
    };
	build(build, 1, 0, n-1);
	int q; cin >> q;
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int i; cin >> i; --i;
            color[i] ^= 1;
            upd(upd, 1, 0, n-1, i);
        }
        if (op == 2 or op == 3) {
            int i, k; cin >> i >> k; --i;
            val[op-2][i] = k;
            upd(upd, 1, 0, n-1, i);
        }
        if (op == 4) {
            int l, r, t; cin >> l >> r >> t; --l, --r, --t;
            auto res = query(query, 1, 0, n-1, l, r);
            cout << res.sum[t&1][0] << endl;
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
