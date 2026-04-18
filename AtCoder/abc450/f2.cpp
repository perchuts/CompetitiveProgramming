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
const int mod = (119<<23)+1;
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
    vector<ii> penis(m);
    vector<int> fim(n), ini(n);
    vector<vector<int>> g(n);
    for (auto& [x, y] : penis) cin >> x >> y, --x, --y, fim[y]++, ini[x]++, g[y].pb(x);
    vector<int> dp(n+1), sdp(n+1), pw(m+1, 1), bit(n+1);
    for (int i = 1; i <= m; ++i) pw[i] = 2 * pw[i-1] % mod;
    auto add = [&] (int x) {
        while (x <= n) bit[x]++, x += x & (-x);
    };
    auto query = [&] (int x) {
        int ans = 0;
        while (x) ans += bit[x], x -= x & (-x);
        return ans;
    };
    int tot = 0, te = 0;
    for (int i = 1; i <= n; ++i) {
        dp[i] = (pw[fim[i-1]]-1)*pw[tot] % mod;
        tot += fim[i-1];
        if (i > 1) fim[i-1] += fim[i-2];
        sort(all(g[i-1]));
        reverse(all(g[i-1]));
        for (int l = 0, r = 0; l != sz(g[i-1]); l = r) {
            while (r != sz(g[i-1]) and g[i-1][l] == g[i-1][r]) r++;
            int bt = te-query(g[i-1][l]);
            int ways = pw[l+bt] * (pw[r-l]-1) % mod * sdp[g[i-1][l]] % mod;
            if (i == 5) cout << bt << " " << ways << " " << r-l << endl;
            dp[i] = (dp[i] + mod - ways) % mod;
        }
        for (auto z : g[i-1]) add(z+1), te++;
        sdp[i] = (sdp[i-1] + dp[i]) % mod;
        cout << dp[i] << " ";
    }
    cout << endl;
    int ans = pw[m];
    vector<int> cnt(n), cnt2(16);
    int zz = 0;
    for (int i = 0; i < (1 << m); ++i) {
        vector<int> ps(n); iota(all(ps), 0);
        bool bunda = 0;
        for (int j = 0; j < m; ++j) {
            if (i >> j & 1) {
                ckmax(ps[penis[j].first], penis[j].second);
            }
        }
        for (int j = 1; j < n; ++j) ckmax(ps[j], ps[j-1]);
        for (int j = 0; j < n; ++j) {
            if (ps[j] == j) {
                cnt[j]++;
                break;
            }
        }

    }
    for (int j = 0; j < n; ++j) cout << cnt[j] << " ";
    cout << endl;
    vector<int> my(n);
    tot = 0;
    for (int i = n-1; i >= 1; --i) {
        tot += ini[i];
        int bad = dp[i] * pw[tot] % mod;
        my[i-1] = bad;
        ans = (ans + mod - bad) % mod;
    }
    for (auto x : my) cout << x << " ";
    cout << endl;
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
