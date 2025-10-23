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
    int n, a, b, c, d; cin >> n >> a >> b >> c >> d;
    vector<int> dp(n+1), fat(n+1, 1), ifat(n+1);
    for (int i = 1; i <= n; ++i) fat[i] = fat[i-1] * i % mod;
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    ifat[n] = fexp(fat[n], mod-2);
    for (int i = n-1; ~i; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
    vector<vector<int>> pre(b+1, vector<int>(d+1));
    for (int i = a; i <= b; ++i) {
        pre[i][1] = 1;
        for (int j = 2; j <= d and i * j <= n; ++j) {
            pre[i][j] = pre[i][j-1] * ifat[i*(j-1)] % mod * fat[i*j] % mod;
            pre[i][j] = pre[i][j] * fat[j-1] % mod * ifat[j] % mod;
            pre[i][j] = pre[i][j] * ifat[i] % mod;
        }
    }
    // ncr[k][i*j] * fat[i*j] * ifat[j] * (ifat[i]^j)
    auto choose = [&] (int a, int b) { return fat[a] * ifat[b] % mod * ifat[a-b] % mod; };
    dp[0] = 1;
    for (int i = a; i <= b; ++i) {
        auto ndp = dp;
        for (int j = c; j <= d; ++j) {
            for (int k = i * j; k <= n; ++k) {
                ndp[k] = (ndp[k] + dp[k - i*j] * choose(k, i*j) % mod * pre[i][j]) % mod;
            }
        }
        swap(dp, ndp);
    }
    cout << dp[n] << endl;
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
