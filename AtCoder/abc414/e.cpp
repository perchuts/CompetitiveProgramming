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
    int n; cin >> n;
    // a % b != a
    // fixado b, dah bom <=> a > b
    // n - 1 + n - 2 + n - 3 + ... 1
    // a = kb
    int div = (mod+1)/2;
    int aa = n % mod;
    int ans = aa % mod * (aa-1) % mod * div % mod;
    int lim = 0;
    for (int b = 1; b*b <= n; ++b) {
        int vai = n / b;
        ans = (ans - vai + 1) % mod;
        lim = b;
    }
    for (int times = 2; times*times <= n; ++times) {
        // b * times <= n
        // b <= n / times
        // b * (times+1) > n
        // b > n / (times+1)
        int l = n / (times+1) + 1;
        int r = n / times;
        ckmax(l, lim+1);
        ans = (ans - (times-1) * max(0LL, r-l+1)) % mod;
    }
    ans = (ans + mod) % mod;
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
