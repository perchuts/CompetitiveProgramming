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

inline void add(int& x, int y) {
    x += y;
    if (x >= mod) x -= mod;
}

void solve() {
    int n; cin >> n;
    int lim = sqrt(n)+1;
	const int L = 2 * lim + 2;
    vector<int> dp(L*(lim+1), 0), id(n+2*lim+10);
    int ans = 0, c = lim+1;
    dp[0] = dp[1] = 1;
    for (int i = 0; i < n + 2 * lim + 10; ++i) id[i] = (i < L ? i : id[i-L]);
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j < lim; ++j) {
            int ni = i + 2 * j;
            int k = dp[id[i]*c+j] * j % mod;
            add(dp[id[ni]*c+j], dp[id[i]*c+j]);
            add(dp[id[ni-1]*c+j-1], k);
            add(dp[id[ni+1]*c+j], k), add(dp[id[ni+1]*c+j], k);
            add(dp[id[ni+3]*c+j+1], k);
        }
        if ((i^n^1)&1) add(ans, dp[id[i]*c]);
        for (int j = 0; j < lim; ++j) dp[id[i]*c+j] = 0;
    }
    add(ans, dp[id[n]*c]);
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
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
