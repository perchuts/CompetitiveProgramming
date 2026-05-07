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
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e & 1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    int n, l, r; cin >> n >> l >> r;
    vector<int> a(n);
    for (auto& x : a) cin >> x, --x;
    sort(all(a)); reverse(all(a));
    vector<int> b, qt;
    for (int lx = 0, rx = 0; lx < n; lx = rx) {
        while (rx != n and a[lx] == a[rx]) ++rx;
        b.pb(a[lx]), qt.pb(rx-lx);
    }
    vector dp(n+1, vector<ll>(n+1));
    vector<int> fat(n+1, 1), ifat(n+1);
    for (int i = 1; i <= n; ++i) fat[i] = i * fat[i-1] % mod;
    ifat[n] = fexp(fat[n], mod-2);
    for (int i = n-1; ~i; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
    int foi = qt[0];
    dp[1][1] = 1;
    for (int k = 1; k < sz(b); ++k) {
        vector ndp(n+1, vector<ll>(n+1));
        int Q = qt[k];
        for (int i = 1; i <= l; ++i) {
            for (int j = 1; j <= r; ++j) {
                // posso escolher nada, um, ou ambos
                // escolher nada
                if (foi >= 2) {
                    ndp[i][j] = (ndp[i][j] + dp[i][j] * fat[foi-2+Q] % mod * ifat[foi-2] % mod * ifat[Q]) % mod;
                }
                // escolher um
                ndp[i][j] = (ndp[i][j] + dp[i-1][j] * fat[foi-1+Q-1] % mod * ifat[foi-1] % mod * ifat[Q-1]) % mod;
                ndp[i][j] = (ndp[i][j] + dp[i][j-1] * fat[foi-1+Q-1] % mod * ifat[foi-1] % mod * ifat[Q-1]) % mod;
                if (i and j and Q >= 2) {
                    ndp[i][j] = (ndp[i][j] + dp[i-1][j-1] * fat[foi+Q-2] % mod * ifat[foi] % mod * ifat[Q-2]) % mod;
                }
                //cout << ndp[i][j] << " \n"[j == r];
            }
        }
        //cout << endl;
        swap(dp, ndp);
        foi += Q;
    }
    cout << dp[l][r] << endl;
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
