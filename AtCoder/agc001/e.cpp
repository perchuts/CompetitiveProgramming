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
    vector<int> a(n), b(n);
    int N = 4050;
    int shift = 2000;
    vector<vector<int>> dp(N+1, vector<int>(N+1));
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
        dp[-a[i]+shift][-b[i]+shift]++;
    }
    auto add = [&] (int& x, int y) {
        x += y;
        if (x >= mod) x -= mod;
    };
    for (int i = -2000; i <= 2000; ++i) {
        for (int j = -2000; j <= 2000; ++j) {
            add(dp[i+1+shift][j+shift], dp[i+shift][j+shift]);
            add(dp[i+shift][j+1+shift], dp[i+shift][j+shift]);
        }
    }
    int ans = 0;
    N *= 2;
    vector<ll> fat(N+1, 1), ifat(N+1);
    for (int i = 1; i <= N; ++i) fat[i] = fat[i-1] * i % mod;
    auto fexp = [&] (ll b, int e) {
        ll resp = 1;
        while (e) {
            if (e&1) resp = resp * b % mod;
            b = b * b % mod, e /= 2;
        }
        return resp;
    };
    ifat[N] = fexp(fat[N], mod-2);
    for (int i = N-1; ~i; --i) ifat[i] = ifat[i+1] * (i+1) % mod;
    auto C = [&] (int a, int b) -> ll {
        return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
    };
    for (int i = 0; i < n; ++i) {
        add(ans, dp[a[i]+shift][b[i]+shift]);
        ll k = C(2*(a[i]+b[i]), 2*a[i]);
        add(ans, mod - k);
    }
    ll ret = ans;
    ret = ret * (mod+1)/2 % mod;
    cout << ret << endl;
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
