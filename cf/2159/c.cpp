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
    int n; cin >> n;
    vector<int> a(n+1);
    for (auto& x : a) cin >> x;
    // a[x] != 0, a[x] != -1 implies a[a[x]] = x.
    vector<int> livres(n+1, 1), foi(n+1);
    for (int i = 1; i < n; ++i) {
        if (a[i] > n) {
            cout << 0 << endl;
            return;
        }
        if (a[i] != -1) livres[i] = 0;
        if (a[i] > 0) livres[a[i]] = 0, foi[a[i]]++;
        if (a[i] > 0 and a[a[i]] != -1 and a[a[i]] != i) {
            cout << 0 << endl;
            return;
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (foi[i] > 1) {
            cout << 0 << endl;
            return;
        }
    }
    // but n must pair with someone!!
    int qtd = 0;
    for (int i = 1; i <= n; ++i) qtd += livres[i];
    // iterate over the number of pairs.
    // the rest can either go with themselves or pair with zero
    // corner case: if livres[n] = 1, i must treat separately the case when n is paired with someone and the case when n is paired with itself
    vector<int> fat(n+1, 1), ifat(n+1), pw(n+1, 1), ipw(n+1);
    for (int i = 1; i <= n; ++i) fat[i] = fat[i-1] * i % mod, pw[i] = pw[i-1] * 2 % mod;
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e & 1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    ifat[n] = fexp(fat[n], mod-2);
    ipw[n] = fexp(pw[n], mod-2);
    for (int i = n-1; ~i; --i) ifat[i] = (i + 1) * ifat[i+1] % mod, ipw[i] = 2 * ipw[i+1] % mod;
    auto ncr = [&] (int a, int b) {
        if (b < 0 or a < b) return 0LL;
        return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
    };
    if (livres[n] == 0) {
        int ans = 0;
        for (int pairs = 0; pairs <= qtd/2; ++pairs) {
            int ways = ncr(qtd, 2 * pairs);
            // pair 2i with 2i+1
            ways = ways * fat[2 * pairs] % mod;
            ways = ways * ipw[pairs] % mod;
            ways = ways * ifat[pairs] % mod;
            ways = ways * pw[qtd - 2 * pairs] % mod;
            ans = (ans + ways) % mod;
        }
        cout << ans << endl;
        return;
    }
    int ans = 0;
    // pairing n with himself
    for (int pairs = 0; pairs <= (qtd-1)/2; ++pairs) {
        int ways = ncr(qtd-1, 2 * pairs);
        // pair 2i with 2i+1
        ways = ways * fat[2 * pairs] % mod;
        ways = ways * ipw[pairs] % mod;
        ways = ways * ifat[pairs] % mod;
        ways = ways * pw[qtd - 1 - 2 * pairs] % mod;
        ans = (ans + ways) % mod;
    }
    // pairing n with someone
    for (int pairs = 1; pairs <= qtd/2; ++pairs) {
        int ways = ncr(qtd-1, 2 * pairs - 1);
        // pair 2i with 2i+1
        ways = ways * fat[2 * pairs] % mod;
        ways = ways * ipw[pairs] % mod;
        ways = ways * ifat[pairs] % mod;
        ways = ways * pw[qtd - 2 * pairs] % mod;
        ans = (ans + ways) % mod;
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
