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
    vector<int> b(n+1);
    for (int i = 1; i <= n; ++i) cin >> b[i];
    // f_0 = sum_{i=0}^28 qt(bit = i) * 2^i
    // 2*(f_1+f0) = sum_{i=0}^28 qt(bit = i)^2 * 2^i
    // f_2 = qt(bit = i)^3  
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    vector<int> ans(n);
    vector<int> fat(n+1, 1), ifat(n+1);
    for (int i = 1; i <= n; ++i) fat[i] = i * fat[i-1] % mod;
    ifat[n] = fexp(fat[n], mod-2);
    for (int i = n-1; ~i; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
    auto ncr = [&] (int a, int b) {
        if (a < b) return 0LL;
        return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
    };
    vector<int> qt(29), pot(29);
         for (int i = 0; i < 29; ++i) pot[i] = (1 << i);
    for (int i = n; i >= 1; --i) {
        for (int j = 0; j < 29; ++j) {
            b[i] = (b[i] - ncr(qt[j], i) * pot[j]) % mod;
            b[i] = (b[i] + mod) % mod;
        }
        for (int j = 0; j < 29; ++j) {
            if (b[i] >> j & 1) {
                qt[j] = i;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 29; ++j) {
            if (i < qt[j]) ans[i] += (1 << j);
        }
    }
    for (auto x : ans) cout << x << " ";
    cout << endl;
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
