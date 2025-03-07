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

void solve(){
    int n, m, K; cin >> n >> m >> K;
    vector<int> w(n);
    int sum = 0;
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    for (auto& x : w) cin >> x, sum += x;
    vector dp(n+1, vector(m+1, vector<int>(K+1, 0LL)));
    vector<int> fat(200, 1), ifat(200);
    for (int i = 1; i < 200; ++i) fat[i] = i * fat[i-1] % mod;
    ifat[199] = fexp(fat[199], mod-2);
    for (int i = 198; ~i; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
    dp[0][0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int k = 0; k <= K; ++k) {
                // me ignore!
                dp[i][j][k] = dp[i-1][j][k];
                if (min(j, k) == 0) continue;
                int W = w[i-1];
                for (int usar = 1; usar <= k; ++usar) {
                    int ways = fat[k] * ifat[usar] % mod * ifat[k-usar] % mod * W % mod;
                    dp[i][j][k] = (dp[i][j][k] + ways * dp[i-1][j-1][k-usar]) % mod;
                    W = W * w[i-1] % mod;
                }
            }
        }
    }
    int S = 1;
    for (int i = 1; i <= K; ++i) S = S * sum % mod;
    cout << dp[n][m][K] * fexp(S, mod-2) % mod << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
