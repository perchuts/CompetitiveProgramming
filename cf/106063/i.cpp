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
    int n, m; cin >> n >> m;
    vector<__int128> a(n+1), b(m+1);
    for (int i = 1; i <= n; ++i) {
        int z; cin >> z;
        a[i] = z;
    }
    for (int i = 1; i <= m; ++i) {
        int z; cin >> z;
        b[i] = z;
    }
    vector<__int128> s1(n+2), s2(n+2);
    for (int i = n; i >= 1; --i) s1[i] = s1[i+1] + a[i], s2[i] = s2[i+1] + s1[i];
    __int128 ans = 0;
    for (__int128 i = 1; i <= m; ++i) {
        __int128 cc = 0;
        for (__int128 j = 1; j <= n; j += i) {
            cc += s2[j];
            if (j + i - 1 <= n) cc -= s1[j+i-1] * (i-1) + s2[j+i-1];
        }
        ans += cc * b[i];
    }
    vector<int> digits;
    if (ans == 0) {
        cout << 0 << endl;
        exit(0);
    }
    while (ans != 0) digits.pb(ans%10), ans /= 10;
    reverse(all(digits));
    for (auto x : digits) cout << x;
    cout << endl;
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
