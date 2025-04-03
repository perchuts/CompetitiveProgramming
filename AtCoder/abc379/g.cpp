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

void solve(){
    int n, m; cin >> n >> m;
    vector<vector<int>> v(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c; cin >> c;
            if (c == '?') v[i][j] = -1;
            else v[i][j] = c - '1';
        }
    }
    if (m > n) {
        vector<vector<int>> v2(m, vector<int>(n));
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) v2[j][i] = v[i][j];
        swap(n, m);
        v = v2;
    }
    assert(m < 15);
    vector<int> pot(m+1, 1);
    for (int i = 1; i <= m; ++i) pot[i] = 3 * pot[i-1];
    vector<int> vals, inv(pot[m], -1);
    for (int i = 0; i < pot[m]; ++i) {
        bool ok = true; 
        for (int j = 1; j < m; ++j) ok &= ((i/pot[j-1]) % 3 != (i/pot[j]) % 3);
        if (ok) inv[i] = sz(vals), vals.pb(i);
    }
    int K = sz(vals);
    vector<int> dp(K), pode(K);
    for (int i = 0; i < K; ++i) {
        int x = vals[i];
        bool ok = true;
        for (int k = 0; k < m; ++k) if (v[0][k] != -1) ok &= ((x/pot[k]) % 3 == v[0][k]);
        if (ok) dp[i] = 1;
    }
    vector<ii> trs;
    auto go = [&] (auto&& self, int id, int tmp, int X) -> void {
        if (id == -1) {
            trs.pb({inv[X], inv[tmp]});
            return;
        }
        int ele = (X/pot[id]) % 3, eu = (tmp/pot[id+1]) % 3;
        for (int k = 0; k < 3; ++k) if (k != ele and k != eu) self(self, id-1, tmp + k * pot[id], X);
    };
    for (auto x : vals) {
        int msb = (x/pot[m-1]) % 3;
        if (msb != 0) go(go, m-2, 0, x);
        if (msb == 2) go(go, m-2, pot[m-1], x);
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < K; ++j) {
            pode[j] = 1;
            for (int k = 0; k < m; ++k) if (v[i][k] != -1) pode[j] &= ((vals[j]/pot[k]) % 3 == v[i][k]);
        }
        vector<int> ndp(K);
        for (auto [x, y] : trs) {
            for (int __ = 0; __ < 2; ++__, swap(x, y)) {
                if (pode[x]) {
                    ndp[x] += dp[y];
                    if (ndp[x] >= mod) ndp[x] -= mod;
                }
            }
        }
        swap(dp, ndp);
    }
    int ans = 0;
    for (auto x : dp) ans = (ans + x) % mod;
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
