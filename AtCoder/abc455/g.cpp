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
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<int> b(k);
    for (auto& x : b) cin >> x;
    vector<vector<int>> ans(k, vector<int>(2));
    vector<vector<int>> occs(n+1);
    vector<int> id_inside(n);
    for (int i = 0; i < n; ++i) {
        id_inside[i] = sz(occs[a[i]]);
        occs[a[i]].pb(i);
    }
    int WW = 0;
    for (auto K : b) {
        vector<ii> seg(4*n, pair(n, -1));
        auto upd = [&] (auto&& self, int i, int l, int r, int x, int k1, int k2) -> void {
            if (l == r) {
                seg[i] = {k1, k2};
                return;
            }
            int md = (l+r)/2;
            if (x <= md) self(self, 2*i, l, md, x, k1, k2);
            else self(self, 2*i+1, md+1, r, x, k1, k2);
            seg[i].first = min(seg[2*i].first, seg[2*i+1].first);
            seg[i].second = max(seg[2*i].second, seg[2*i+1].second);
        };
        auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> ii {
            if (r < x or y < l) return {n, -1LL};
            if (x <= l and r <= y) return seg[i];
            int md = (l+r)/2;
            auto [l1, l2] = self(self, 2*i, l, md, x, y);
            auto [r1, r2] = self(self, 2*i+1, md+1, r, x, y);
            return {min(l1, r1), max(l2, r2)};
        };
        vector<int> cur_seta(n+1, -1);
        vector<int> go(n), lim(n);
        for (int i = n-1; ~i; --i) {
            int pos = id_inside[i];
            int cp = cur_seta[a[i]];
            if (cp != -1) upd(upd, 1, 0, n-1, cp, n, -1);
            int seta1, seta2;
            if (pos + K >= sz(occs[a[i]])) seta1 = n;
            else seta1 = occs[a[i]][pos+K];
            if (pos + K - 1 >= sz(occs[a[i]])) seta2 = n;
            else seta2 = occs[a[i]][pos+K-1];
            upd(upd, 1, 0, n-1, i, seta1, seta2);
            cur_seta[a[i]] = i;
            int l = i, r = n-1, opt = -1;
            while (l <= r) {
                int md = l + (r-l+1)/2;
                auto [x1, x2] = query(query, 1, 0, n-1, i, md);
                if (x1 != -1 and x1 <= x2) r = md-1;
                else opt = md, l = md+1;
            }
            if (i == 1) {
                auto [x1, x2] = query(query, 1, 0, n-1, i, 3);
                //cout << x1 << " " << x2 << endl;
            }
            if (opt == -1) go[i] = -1;
            else {
                auto [s1, s2] = query(query, 1, 0, n-1, i, opt);
                if (s2 <= opt) go[i] = opt, lim[i] = s1;
                else go[i] = -1;
            }
        }
        int ult = n;
        for (int i = n-1; ~i; --i) {
            if (go[i] == -1) continue;
            ckmin(go[i], ult-1);
            ult = go[i];
        }
        vector<int> ptr_rev(n), steps(n), act(n);
        for (int i = 0; i < n; ++i) {
            if (go[i] != -1) ptr_rev[go[i]] = i;
        }
        //cout << "k = " << K << endl;
        int tot = 0;
        //cout << "go: ";
        //for (int i = 0; i < n; ++i) {
        //    cout << go[i] << ' ';
        //}
        //cout << "lim: ";
        //for (int i = 0; i < n; ++i) {
        //    cout << lim[i] << ' ';
        //}
        //cout << endl;
        //cout << "act(rev): ";
        for (int i = n-1; ~i; --i) {
            if (go[i] == -1) continue;
            if (go[i] == n-1 or go[go[i]+1] == -1) {
                steps[i] = 1;
                act[i] = go[i];
            } else {
                act[i] = act[go[i]+1];
                steps[i] = 1 + steps[go[i]+1];
                while (lim[i] <= act[i]) --steps[i], act[i] = ptr_rev[act[i]]-1;
            }
            //cout << act[i] << " ";
            tot += steps[i];
        }
        ans[WW++][0] = tot;
    }
    for (auto x : ans) {
        for (auto y : x) cout << y << " ";
        cout << endl;
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
