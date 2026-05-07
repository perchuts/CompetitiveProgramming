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
    int n, e, t; cin >> n >> e >> t;
    vector<int> a(n+2);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    vector<int> dp(n+1);
    vector<ii> seg(4*n+4, {1e18, 1e18});
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int k) -> void {
        if (l == r) {
            seg[i] = {k - 2*a[l+1] - a[l], k + t - a[l]};
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x, k);
        else self(self, 2*i+1, md+1, r, x, k);
        seg[i].first = min(seg[2*i].first, seg[2*i+1].first);
        seg[i].second = min(seg[2*i].second, seg[2*i+1].second);
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> ii {
        if (r < x or y < l) return {1e18, 1e18};
        if (x <= l and r <= y) return seg[i];
        int md = (l+r)/2;
        auto [l1, l2] = self(self, 2*i, l, md, x, y);
        auto [r1, r2] = self(self, 2*i+1, md+1, r, x, y);
        return {min(l1, r1), min(l2, r2)};
    };
    upd(upd, 1, 0, n, 0, 0);
    int ptr = 0;
    for (int i = 1; i <= n; ++i) {
        dp[i] = 1e18;
        while (2*(a[i]-a[ptr+1]) >= t) ptr++;
        if (ptr) {
            auto [t1, t2] = query(query, 1, 0, n, 0, ptr-1);
            ckmin(dp[i], t1 + 3*a[i]);
        }
        if (ptr < i) {
            auto [t1, t2] = query(query, 1, 0, n, ptr, i-1);
            ckmin(dp[i], t2 + a[i]);
        }
        upd(upd, 1, 0, n, i, dp[i]);
    }
    cout << dp[n] + e - a[n] << endl;
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
