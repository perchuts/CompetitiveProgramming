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
const int maxn = 3e5+10;
const int mod = (119<<23)+1;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
int fat[maxn], ifat[maxn];
int ncr(int a, int b) {
    if (min(a, b) < 0 or a < b) return 0;
    return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
}
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    int ans = 1, pode = (n&1);
    for (int i = n/2; ~i; --i, pode += 2) {
        ans = ans * ncr(pode, a[i]) % mod;
        pode -= a[i];
    }
    if (pode > 2) ans = 0;
    for (int i = n/2+1; i < n; ++i) {
        if (a[i]) ans = 0;
    }
    cout << ans << endl;
}

int32_t main() {_
    fat[0] = 1;
    for (int i = 1; i < maxn; ++i) fat[i] = i * fat[i-1] % mod;
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    ifat[maxn-1] = fexp(fat[maxn-1], mod-2);
    for (int i = maxn-2; ~i; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
#ifndef gato
    int t = 1; cin >> t;
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
