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
    vector<int> p(n);
    for (auto& x : p) cin >> x, --x;
    vector<ii> qu(q);
    for (auto& [x, y] : qu) cin >> x >> y, --x, --y;
    vector<int> seg(4*n), ans(q, 1);
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int k, bool set = 0) -> void {
        if (l == r) {
            if (!set) ckmax(seg[i], k);
            else seg[i] = k;
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x, k, set);
        else self(self, 2*i+1, md+1, r, x, k, set);
        seg[i] = max(seg[2*i], seg[2*i+1]);
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> int {
        if (r < x or y < l) return 0;
        if (x <= l and r <= y) return seg[i];
        int md = (l+r)/2;
        return max(self(self, 2*i, l, md, x, y), self(self, 2*i+1, md+1, r, x, y));
    };
    auto go = [&] (auto&& self, int l, int r, vector<int> ids) -> void {
        if (l == r) return;
        int md = (l+r)/2;
        vector<int> now, esq, dir;
        for (auto i : ids) {
            auto [lx, rx] = qu[i];
            if (lx <= md and md <= rx) now.pb(i);
            if (rx < md) esq.pb(i);
            if (md < lx) dir.pb(i);
        }
        sort(all(now), [&] (int x, int y) { return qu[x].first > qu[y].first; });
        int j = 0, best = 0;
        for (int i = md; i >= l and j < sz(now); --i) {
            int opt = query(query, 1, 0, n-1, p[i], n-1) + 1;
            ckmax(best, opt);
            upd(upd, 1, 0, n-1, p[i], opt);
            while (j < sz(now) and qu[now[j]].first == i) {
                ckmax(ans[now[j++]], best);
            }
        }
        for (int i = l; i <= md; ++i) upd(upd, 1, 0, n-1, p[i], 0, 1);
        sort(all(now), [&] (int x, int y) { return qu[x].second < qu[y].second; });
        best = j = 0;
        for (int i = md; i <= r; ++i) {
            int opt = query(query, 1, 0, n-1, 0, p[i]) + 1;
            ckmax(best, opt);
            upd(upd, 1, 0, n-1, p[i], opt);
            while (j < sz(now) and qu[now[j]].second == i) ckmax(ans[now[j++]], best);
        }
        for (int i = md; i <= r; ++i) upd(upd, 1, 0, n-1, p[i], 0, 1);
        self(self, l, md, esq);
        self(self, md+1, r, dir);
    };
    vector<int> qq(q); iota(all(qq), 0);
    go(go, 0, n-1, qq);
    vector<int> L(n, n);
    for (int i = n-2; i >= 0; --i) {
        if (p[i] > p[i+1]) L[i] = L[i+1];
        else L[i] = i+1;
    }
    for (int i = 0; i < q; ++i) {
        auto [l, r] = qu[i];
        if (ans[i] == 1) cout << (L[l] <= r ? 2 : 1) << endl;
        else cout << (3 * ans[i]) / 2 << endl;
    }
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
