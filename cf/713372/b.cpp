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
    vector<int> l(n), r(n), vals, dp(n+1), iv(n+1), contar(n+1, 1);
    for (int i = 0; i < n; ++i) cin >> l[i] >> r[i], vals.pb(l[i]), vals.pb(r[i]);
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    for (int i = 1; i <= n; ++i) iv[i] = fexp(i, mod-2);
    dp[0] = 1;
    sort(all(vals)), vals.erase(unique(all(vals)), end(vals));
    for (int i = 0; i < sz(vals)-1; ++i) {
        for (int j = n-1; ~j; --j) if (l[j] <= vals[i] and vals[i] <= r[j]) dp[j+1] = (dp[j+1] + dp[j]) % mod;
        int li = vals[i], ri = vals[i+1];
        for (int j = 1; j <= n; ++j) contar[j] = contar[j-1] * (ri-li-j) % mod * iv[j] % mod;
        for (int st = n-1; ~st; --st) {
            for (int en = st; en < n; ++en) {
                if (!(l[en] <= li+1 and ri-1 <= r[en])) break;
                dp[en+1] = (dp[en+1] + dp[st] * contar[en-st+1]) % mod;
            }
        }
    }
    if (l.back() <= vals.back() and vals.back() <= r.back()) dp[n] = (dp[n] + dp[n-1]) % mod;
    cout << dp[n] << endl;
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
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
