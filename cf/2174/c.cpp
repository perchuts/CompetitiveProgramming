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
    int n, m, p; cin >> n >> m >> p;
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % p;
            e /= 2, b = b * b % p;
        }
        return ans;
    };
    vector<int> pw(n+1, 1), ipw(n+1);
    for (int i = 1; i <= n; ++i) pw[i] = m * pw[i-1] % p;
    ipw[n] = fexp(pw[n], p-2);
    for (int i = n-1; ~i; --i) ipw[i] = m * ipw[i+1] % p;
    int ans = 0;
    for (int j = 0; j <= n / 2; ++j) {
        int lp = j + 1, rp = n - j;
        if (lp <= rp) ans = (ans + ipw[j] * (2*j+1) % p * (rp-lp+1)) % p;
    }
    for (int j = 1; j <= n / 2; ++j) {
        int lp = j, rp = n - j;
        if (lp <= rp) ans = (ans + ipw[j] * (2*j-1) % p * (rp-lp+1)) % p;
    }
    int S = 0;
    for (int i = 1; i <= n; ++i) S = (S + (n - i + 1) * ipw[i/2]) % p;
    ans = (ans + S * S) % p;
    vector<int> sums(n+1);
    sums[1] = 1;
    for (int i = 2; i <= n; ++i) sums[i] = (sums[i-2] + ipw[i/2]) % p;
    ans = (ans + n*p - n) % p;
    for (int i = 2; i <= n; ++i) {
        int ways = (n - i + 1) * ipw[i/2] % p;
        ways = ways * sums[i-2] * 2 % p;
        ways = (ways + (n - i + 1) * ipw[i/2 + i/2] % p) % p;
        ans = (ans - ways + p) % p;
    }
    cout << ans << endl;
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
