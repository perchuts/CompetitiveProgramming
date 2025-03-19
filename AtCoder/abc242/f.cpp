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
    int n, m, b, w; cin >> n >> m >> b >> w;
    vector dp(n+1, vector(m+1, vector(max(b, w)+1, 0LL)));
    dp[0][0][0] = 1;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
        for (int k = 1; k <= max(b, w); ++k) {
            // posso colocar em um lugar ja existente e nao mudar nada
            dp[i][j][k] = (dp[i][j][k-1] * (i*j - (k-1))) % mod;
            // criar nova linha, manter coluna!
            dp[i][j][k] = (dp[i][j][k] + dp[i-1][j][k-1] * i * j) % mod;
            // criar nova coluna, manter linha!
            dp[i][j][k] = (dp[i][j][k] + dp[i][j-1][k-1] * i * j) % mod;
            // criar tudo
            dp[i][j][k] = (dp[i][j][k] + dp[i-1][j-1][k-1] * i * j) % mod;
        }
    }
    int ans = 0;
    vector ncr(100, vector(100, 0LL));
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (j == 0 or j == i) ncr[i][j] = 1;
            else ncr[i][j] = (ncr[i-1][j-1] + ncr[i-1][j]) % mod;
        }
    }
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) for (int k = 1; k <= n; ++k) for (int l = 1; l <= m; ++l) {
        int cur = dp[i][j][b] * dp[k][l][w] % mod * ncr[n][i] % mod * ncr[m][j] % mod * ncr[n-i][k] % mod * ncr[m-j][l] % mod;
        ans = (ans + cur) % mod;
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
