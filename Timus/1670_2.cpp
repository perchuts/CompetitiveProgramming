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
    int n; cin >> n;
    vector<int> p(n);
    for (auto& x : p) cin >> x, --x;
    string ans;
    vector<int> esq(n), dir(n), nice(n);
    vector<ii> penis;
    penis.pb({n, -1});
    for (int i = 0; i < n; ++i) {
        while (penis.back().first < p[i]) penis.pop_back();
        esq[p[i]] = penis.back().second;
        penis.pb({p[i], i});
    }
    penis = {{-1, n}};
    for (int i = n-1; ~i; --i) {
        while (penis.back().first > p[i]) penis.pop_back();
        dir[p[i]] = penis.back().second;
        penis.pb({p[i], i});
    }
    for (int i = 1; i < n; ++i) {
        if (p[i-1] < p[i]) nice[i] = nice[i-1];
        else nice[i] = i;
    }
    struct node {
        int prim = inf, ult = -1;
        int ok = inf;
    };
    vector<node> seg(4*n);
    vector<int> atv(n);
    auto merge = [&] (node& a, node& b) {
        node c;
        c.prim = min(a.prim, b.prim);
        c.ult = max(a.ult, b.ult);
        c.ok = min({a.ok, b.ok, (b.ult == 1 + a.prim ? a.prim : inf)});
        return c;
    };
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int t) -> void {
        if (l == r) {
            seg[i].prim = (t ? esq[l] : inf);
            seg[i].ult  = (t ? dir[l] : -1);
            atv[l] = t;
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x, t);
        else self(self, 2*i+1, md+1, r, x, t);
        seg[i] = merge(seg[2*i], seg[2*i+1]);
    };
    auto build = [&] (auto&& self, int i, int l, int r) -> void {
        if (l == r) {
            seg[i].ult = dir[l];
            seg[i].prim = esq[l];
            atv[l] = 1;
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md), self(self, 2*i+1, md+1, r);
        seg[i] = merge(seg[2*i], seg[2*i+1]);
		cout << l << " " << r << " " << seg[i].ok << endl;
    };
    build(build, 1, 0, n-1);
    vector<array<int, 4>> t;
    for (int i = 0; i < n; ++i) cout << esq[i] << " " << dir[i] << endl;
    auto solve = [&] (auto&& self, int l, int r, int lx, int rx) -> bool {
        //cout << l << " " << r << ": ";
        //for (int i = 0; i < n; ++i) cout << atv[i];
        //cout << endl;
        if (nice[r] <= l) {
            t.push_back({lx, rx, -1, -1});
            for (int i = l; i <= r; ++i) upd(upd, 1, 0, n-1, p[i], 0);
            return true;
        }
        int pos = seg[1].ok;
        if (pos == inf) return 0;
        if (pos-l <= r-pos) {
            int f1, f2;
            int mn = n;
            for (int i = l; i <= pos; ++i) upd(upd, 1, 0, n-1, p[i], 0), ckmin(mn, p[i]);
            bool ok = self(self, pos+1, r, lx, mn-1);
            f1 = sz(t)-1;
            if (!ok) return 0;
            for (int i = l; i <= pos; ++i) upd(upd, 1, 0, n-1, p[i], 1);
            ok &= self(self, l, pos, mn, rx);
            f2 = sz(t)-1;
            t.pb({lx, rx, f1, f2});
            for (int i = l; i <= pos; ++i) upd(upd, 1, 0, n-1, p[i], 0);
            if (!ok) return 0;
            return true;
        } 
        int f1, f2;
        int mx = 0;
        for (int i = pos+1; i <= r; ++i) upd(upd, 1, 0, n-1, p[i], 0), ckmax(mx, p[i]);
        bool ok = self(self, l, pos, mx+1, rx);
        f1 = sz(t)-1;
        if (!ok) return 0;
        for (int i = pos+1; i <= r; ++i) upd(upd, 1, 0, n-1, p[i], 1);
        ok &= self(self, pos+1, r, lx, mx);
        f2 = sz(t)-1;
        for (int i = pos+1; i <= r; ++i) upd(upd, 1, 0, n-1, p[i], 0);
        if (!ok) return 0;
        t.pb({lx, rx, f2, f1});
        return true;
    };
    if (!solve(solve, 0, n-1, 0, n-1)) {
        cout << "IMPOSSIBLE" << endl;
        exit(0);
    }
    auto dfs = [&] (auto&& self, int i) -> void {
        int l = t[i][0], r = t[i][1], f1 = t[i][2], f2 = t[i][3];
        cout << l << " " << r << " " << f1 << " " << f2 << endl;
        if (l != 0 or r != n-1) ans += '(';
        if (f1 == -1) {
            for (int j = l; j <= r; ++j) {
                if (j != l) ans += ',';
                ans += to_string(j+1);
            }
        } else {
            self(self, f1);
            ans += '*';
            self(self, f2);
        }
        if (l != 0 or r != n-1) ans += ')';
    };
    dfs(dfs, sz(t)-1);
    cout << ans << endl;
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
