#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
    vector<int> nice(n), onde(n), atv(n);
    vector<array<int, 2>> lz(4*n);
    for (int i = 0; i < n; ++i) onde[p[i]] = i;
    for (int i = 1; i < n; ++i) nice[i] = (p[i-1] < p[i] ? nice[i-1] : i);
    set<int> exist;
    vector<array<ii, 2>> seg(4*n);
    auto push = [&] (int i, int l, int r) {
        seg[i][0].first += lz[i][0];
        seg[i][1].first += lz[i][1];
        if (l != r) lz[2*i][0] += lz[i][0], lz[2*i+1][0] += lz[i][0], lz[2*i][1] += lz[i][1], lz[2*i+1][1] += lz[i][1];
        lz[i][0] = lz[i][1] = 0;
    };
    auto build = [&] (auto&& self, int i, int l, int r) -> void {
        if (l == r) { seg[i][0].second = seg[i][1].second = l; return; }
        int md = (l+r)/2;
        self(self, 2*i, l, md), self(self, 2*i+1, md+1, r);
        seg[i][0].second = seg[i][1].second = l;
    };
    build(build, 1, 0, n-1);
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int y, int k1, int k2) -> void {
        push(i, l, r);
        if (r < x or y < l) return;
        if (x <= l and r <= y) { lz[i][0] += k1, lz[i][1] += k2, push(i, l, r); return; }
        int md = (l+r)/2;
        self(self, 2*i, l, md, x, y, k1, k2);
        self(self, 2*i+1, md+1, r, x, y, k1, k2);
        seg[i] = min(seg[2*i], seg[2*i+1]);
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> array<ii, 2> {
        push(i, l, r);
        if (r < x or y < l) return {make_pair(inf, inf), make_pair(inf, inf)};
        if (x <= l and r <= y) return seg[i];
        int md = (l+r)/2;
        auto lx = self(self, 2*i, l, md, x, y);
        auto rx = self(self, 2*i+1, md+1, r, x, y);
        return {min(lx[0], rx[0]), min(lx[1], rx[1])};
    };
    auto add = [&] (int i, bool tipo = 1) {
        atv[i] = tipo;
        if (tipo == 0) exist.erase(p[i]);
        auto it = exist.lower_bound(p[i]);
        if (it != begin(exist) and it != end(exist)) {
            int j2 = onde[*it], j1 = onde[*prev(it)];
            upd(upd, 1, 0, n-1, min(j1, j2), max(j1, j2)-1, (tipo ? -1 : 1), 0);
            upd(upd, 1, 0, n-1, min(j1, j2), max(j1, j2)-1, 0, (tipo ? -1 : 1));
        }
        if (it != end(exist)) {
            int j = onde[*it];
            upd(upd, 1, 0, n-1, min(i, j), max(i, j)-1, (tipo ? 1 : -1), 0);
            upd(upd, 1, 0, n-1, min(i, j), max(i, j)-1, 0, (tipo ? 1 : -1));
        }
        if (it != begin(exist)) {
            int j = onde[*prev(it)];
            upd(upd, 1, 0, n-1, min(i, j), max(i, j)-1, (tipo ? 1 : -1), 0);
            upd(upd, 1, 0, n-1, min(i, j), max(i, j)-1, 0, (tipo ? 1 : -1));
        }
        if (tipo) exist.insert(p[i]);
    };
    auto rem = [&] (int i) { add(i, 0); return; };
    for (int i = 0; i < n; ++i) add(i);
    vector<int> tipo;
    vector<array<int, 4>> t;
    auto solve = [&] (auto&& self, int l, int r, int lx, int rx) -> bool {
        cout << l << " " << r << " " << lx << " " << rx << endl;
        for (int i = 0; i < n; ++i) cout << atv[i];
        cout << endl;
        if (nice[r] <= l) {
            t.push_back({lx, rx, -1, -1});
            for (int i = l; i <= r; ++i) rem(i);
            tipo.pb(-1);
            return true;
        }
        if (onde[lx] > onde[rx]) {
            auto [val, pos] = query(query, 1, 0, n-1, l, r-1)[1];
            cout << val << " " << pos << endl;
            if (val>1) return 0;
            if (pos-l <= r-pos) {
                int f1, f2;
                int mn = n;
                for (int i = l; i <= pos; ++i) rem(i), ckmin(mn, p[i]);
                bool ok = self(self, pos+1, r, lx, mn-1);
                f1 = sz(t)-1;
                if (!ok) return 0;
                for (int i = l; i <= pos; ++i) add(i);
                ok &= self(self, l, pos, mn, rx);
                f2 = sz(t)-1;
                tipo.pb(1);
                t.pb({lx, rx, f1, f2});
                for (int i = l; i <= pos; ++i) rem(i);
                if (!ok) return 0;
                return true;
            } 
            int f1, f2;
            int mx = 0;
            for (int i = pos+1; i <= r; ++i) rem(i), ckmax(mx, p[i]);
            bool ok = self(self, l, pos, mx+1, rx);
            f1 = sz(t)-1;
            if (!ok) return 0;
            for (int i = pos+1; i <= r; ++i) add(i);
            ok &= self(self, pos+1, r, lx, mx);
            f2 = sz(t)-1;
            for (int i = pos+1; i <= r; ++i) rem(i);
            if (!ok) return 0;
            tipo.pb(1);
            t.pb({lx, rx, f2, f1});
            return true;
        }
        auto [val, pos] = query(query, 1, 0, n-1, l, r-1)[0];
        if (val>1) return 0;
        if (pos-l <= r-pos) {
            int f1, f2;
            int mx = 0;
            for (int i = l; i <= pos; ++i) rem(i), ckmax(mx, p[i]);
            bool ok = self(self, pos+1, r, mx+1, rx);
            f1 = sz(t)-1;
            if (!ok) return 0;
            for (int i = l; i <= pos; ++i) add(i);
            ok &= self(self, l, pos, lx, mx);
            f2 = sz(t)-1;
            tipo.pb(0);
            t.pb({lx, rx, f2, f1});
            for (int i = l; i <= pos; ++i) rem(i);
            if (!ok) return 0;
            return true;
        } 
        int f1, f2;
        int mn = n;
        for (int i = pos+1; i <= r; ++i) rem(i), ckmin(mn, p[i]);
        bool ok = self(self, l, pos, lx, mn-1);
        f1 = sz(t)-1;
        if (!ok) return 0;
        for (int i = pos+1; i <= r; ++i) add(i);
        ok &= self(self, pos+1, r, mn, rx);
        f2 = sz(t)-1;
        for (int i = pos+1; i <= r; ++i) rem(i);
        if (!ok) return 0;
        tipo.pb(0);
        t.pb({lx, rx, f1, f2});
        return true;
    };
    if (!solve(solve, 0, n-1, 0, n-1)) {
        cout << "IMPOSSIBLE" << endl;
        exit(0);
    }
    auto dfs = [&] (auto&& self, int i) -> void {
        int l = t[i][0], r = t[i][1], f1 = t[i][2], f2 = t[i][3];
        //cout << l << " " << r << " " << f1 << " " << f2 << endl;
        ans += '(';
        if (f1 == -1) {
            for (int j = l; j <= r; ++j) {
                if (j != l) ans += ',';
                ans += to_string(j+1);
            }
        } else {
            self(self, f1);
            if (tipo[i]) ans += '*';
            else ans += ',';
            self(self, f2);
        }
        ans += ')';
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
