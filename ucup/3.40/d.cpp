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
    int k, m; cin >> k >> m;
    ++k;
    vector<int> fat(k+1, 1), f(k+1), ifat(k+1);
    for (int i = 1; i <= k; ++i) fat[i] = i * fat[i-1] % m;
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % m;
            b = b * b % mod, e /= 2;
        }
        return ans;
    };
    ifat[k] = fexp(fat[k], mod-2);
    for (int i = k-1; ~i; --i) ifat[i] = (i+1) * ifat[i+1] % m;
    int inv2 = (m+1)/2;
    for (int n = 1; n < k; ++n) {
        int ans = (inv2) * n % m * (n+1) % m;
        ans = ans * fat[n] % m;
        // n! - ncr(n-j, i) i! (n-i)!
        // -n! + (n-j)!/(n-j-i)!
        for (int i = 1; i < n; ++i) {
            f[i] = (f[i] + fat[n-1] * ifat[n-i-1]) % m;
        }
        cout << "n = " << n << endl;
        for (int i = 1; i <= n; ++i) {
            ans = (ans - fat[n] * (n+1-i) + f[i]) % m;
            ans = (ans + m) % m;
            cout << "f[" << i << "] = " << f[i] << ' ';
        }
        cout << ans << endl; 
    }
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
