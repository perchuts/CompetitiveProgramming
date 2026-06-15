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
const int mod = 999999893;
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
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e & 1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    int a, b;
    if (n == 1){
        cout << 0 << endl;
        return;
     }
    if (n % 2 == 0) {
        a = fexp(2, (n-2)/2);
        b = fexp(2, n/2)-1;
    } else {
        a = fexp(2, (n-1)/2);
        b = fexp(2, (n-1)/2)-1;
    }
    int z = (2*a*a-b*b) % mod; z = (z + mod) % mod;
    int ans = fexp(z, mod-2) * b % mod;
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
