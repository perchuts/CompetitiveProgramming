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

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve() {
    int l, r; cin >> l >> r;
    vector dp(16, 0LL);
    dp[15] = 1;
    for (int i = 50; ~i; --i) {
        vector ndp(16, 0LL);
        int lv = l>>i&1, rv = r>>i&1;
        for (int m = 0; m < 16; ++m) {
            if (!dp[m]) continue;
            for (int x = 0; x < 2; ++x) {
                int l1 = m & 1, r1 = m >> 1 & 1, l2 = m >> 2 & 1, r2 = m >> 3 & 1;
                if (i <= 2) {
                }
                int nl1, nl2, nr1, nr2; 
                {
                    int want = x;
                    if (l1 and lv and want == 0) want ^= 1;
                    else if (r1 and rv == 0 and want) want ^= 1;
                    if ((want^x) != lv) continue;
                    nl1 = l1 & (want==lv);
                    nr1 = r1 & (want==rv);
                }
                {
                    int want = x^1;
                    if (l2 and lv and want == 0) want ^= 1;
                    else if (r2 and rv == 0 and want) want ^= 1;
                    if ((want^x) != rv) continue;
                    nl2 = l2 & (want==lv);
                    nr2 = r2 & (want==rv);
                }
                ndp[nl1+2*nr1+4*nl2+8*nr2] += dp[m];
            }
        }
        swap(dp, ndp);
    }
    int ans = 0;
    for (auto x : dp) ans += x;
    cout << ans-1 << endl;
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
