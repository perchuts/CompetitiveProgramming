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
    int l, r; cin >> l >> r;
    int ans = (r-l+1)*(r-l)/2;
    int t = 0;
    for (int i = max(2LL, l); i <= r; ++i) {
        for (int j = 2*i; j <= r; j += i) t++;
    }
    vector<int> dp(r+1);
    for (int i = 1; i <= r; ++i) {
        for (int j = i; j <= r; j += i) {
            if (l <= j and j <= r) dp[i]++;
        }
    }
    for (int i = r; i >= 1; --i) {
        dp[i] = dp[i] * (dp[i]-1) / 2;
        for (int j = 2 * i; j <= r; j += i) dp[i] -= dp[j];
    }
    t += dp[1];
    ans -= t;
    cout << 2*ans << endl;
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
