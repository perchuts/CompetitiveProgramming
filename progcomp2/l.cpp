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

vector<int> solve(int n, int q, vector<int> v, vector<ii> qq) {
    vector<int> ord(n); iota(all(ord), 0); sort(all(ord), [&] (int x, int y) { return v[x] < v[y]; });
    vector<int> pos(n); for (int i = 0; i < n; ++i) pos[ord[i]] = i;
    const int B = 150;
    vector<vector<iii>> qu(n/B+1);
    int Z = 0;
    for (auto [l, r] : qq) {
        qu[l/B].pb({r, l, Z++});
    }
    vector<int> ans(q);
    struct node {
        int mn, mx, opt;
        node() { mn = inf, mx = -inf, opt = inf; }
    } nulo;
    vector<node> seg(4*n, nulo);
    auto merge = [&](node a, node b) {
        node c;
        c.mn = min(a.mn, b.mn);
        c.mx = max(a.mx, b.mx);
        c.opt = min(a.opt, b.opt);
        if (a.mx != inf and b.mx != inf) ckmin(c.opt, b.mn - a.mx);
        return c;
    };
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int k) {
        if (l == r) {
            if (k == 1) {
                seg[i].mn = seg[i].mx = v[ord[l]];
            } else {
                seg[i] = nulo;
            }
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x, k);
        else self(self, 2*i+1, md+1, r, x, k);
        seg[i] = merge(seg[2*i], seg[2*i+1]);
    };
    int lx = 0, rx = 0;
    for (int i = 0; i <= n/B; ++i) {
        sort(all(qu[i]));
        for (auto [r, l, id] : qu[i]) {
            while (rx <= r) upd(upd, 1, 0, n-1, pos[rx++], 1);
            while (r+1 < rx) upd(upd, 1, 0, n-1, pos[--rx], -1);
            while (lx < l) upd(upd, 1, 0, n-1, pos[lx++], -1);
            while (l < lx) upd(upd, 1, 0, n-1, pos[--lx], 1);
            ans[id] = seg[1].opt;
        }
    }
    return ans; 
}

vector<int> brute(int n, int q, vector<int> v, vector<ii> qu) {
    vector<int> ans;
    for (int i = 0; i < q; ++i) {
        int opt = inf;
        for (int l = qu[i].first; l < qu[i].second; ++l) {
            for (int r = l+1; r <= qu[i].second; ++r) {
                ckmin(opt, abs(v[l]-v[r]));
            }
        }
        ans.pb(opt);
    }
    return ans;
}
int32_t main() {_
#ifndef gato
	int n; cin >> n;
	vector<int> v(n);
	for (auto& x : v) cin >> x;
	int q; cin >> q;
	vector<ii> qu(q);
	for (auto& [x, y] : qu) cin >> x >> y, --x, --y;
	auto ans = solve(n, q, v, qu);
	for (auto x : ans) cout << x << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 5);
        vector<int> v(n);
        for (auto& x : v) x = rnd(1, 10);
        int q = rnd(1, 3);
        vector<ii> qu(q);
        for (auto& [x, y] : qu) {
            x = rnd(0, n-2);
            y = rnd(x+1, n-1);
        }
        auto my = solve(n, q, v, qu);
        auto ans = brute(n, q, v, qu);

        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : v) cout << x << ' ';
            cout << endl;
			cout << q << endl;
            for (auto [x, y] : qu) cout << x + 1 << ' ' << y + 1 << endl;
            for (auto x : my) cout << x << ' ';
            cout << endl;
            for (auto x : ans) cout << x << ' ';
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

