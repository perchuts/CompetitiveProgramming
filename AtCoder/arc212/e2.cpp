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

int brute(int n, vector<int> p) {
    // if pi is max amongst its neighbors, we are done!
    vector<int> pp(n+2);
    for (int i = 1; i <= n; ++i) pp[i] = p[i-1];

    vector dp(n+2, vector(n+2, 0LL)), ncr = dp;
    for (int i = 0; i <= n; ++i) for (int j = 0; j <= i; ++j) {
        if (i == j or j == 0) ncr[i][j] = 1;
        else ncr[i][j] = (ncr[i-1][j] + ncr[i-1][j-1]) % mod;
    }
    for (int i = 0; i <= n; ++i) {
        if (i <= n) dp[i][i+1] = 1;
    }
    auto get = [&] (int a, int b) {
        if (min(a, b) < 0) return 1LL;
        return ncr[a][b];
    };
    int ans = 1;
    // dp[l][r] where 1 <= l < r <= n
    // so preciso saber o valor de dp[0][onde[N]], dp[onde[N]][n+1]
    // T(L, R) = .
    for (int l = n+1; ~l; --l) {
        for (int r = l+2; r <= n+1; ++r) {
            for (int k = l+1; k < r; ++k) {
                if (pp[k] < max(pp[l], pp[r])) {
                    int ways = dp[l][k] * dp[k][r] % mod * get(r-l-2, k-l-1) % mod;
                    dp[l][r] = (dp[l][r] + ways) % mod;
                }
            }
        }
    }
    int l = 0, r = n+1;
    for (int k = 1; k <= n; ++k) {
        if (pp[k] == n) {
            int ways = dp[l][k] * dp[k][r] % mod * get(r-l-2, k-l-1) % mod;
			return ways;
        }
    }
	return -1;
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
