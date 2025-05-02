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

void solve(){
    int n, m, l; cin >> n >> m >> l;
    vector<vector<int>> ncr(n+1, vector<int>(n+1));
    vector<int> fat(n+1, 1), ifat(n+1);
    for (int i = 1; i <= n; ++i) fat[i] = i * fat[i-1] % mod;
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            b = b * b % mod, e /= 2;
        }
        return ans;
    };
    ifat[n] = fexp(fat[n], mod-2);
    for (int i = n-1; ~i; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
    for (int i = 0; i <= n; ++i) for (int j = 0; j <= i; ++j) {
        if (j == 0 or j == i) ncr[i][j] = 1;
        else ncr[i][j] = (ncr[i-1][j] + ncr[i-1][j-1]) % mod;
    }
    // quantos vertices ja foram, quantas arestas ja foram, ja usei componente de tamanho L ou nao
    vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(m+1, vector<int>(2, 0)));
    dp[0][0][0] = 1;
    int inv2 = (mod+1)/2;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            // caminho:
            for (int k = 1; k <= min({i, l, j+1}); ++k) {
                int ways = ncr[i-1][k-1] * fat[k] % mod * (k==1?1:inv2) % mod;
                dp[i][j][1] = (dp[i][j][1] + ways * dp[i-k][j-k+1][1]) % mod;
                if (k < l) dp[i][j][0] = (dp[i][j][0] + ways * dp[i-k][j-k+1][0]) % mod;
                else dp[i][j][1] = (dp[i][j][1] + ways * dp[i-k][j-k+1][0]) % mod;
            }
            // ciclo:
            for (int k = 2; k <= min({i, l, j}); ++k) {
                int ways = ncr[i-1][k-1] * (k>3?fat[k-1]*inv2%mod:1) % mod;
                dp[i][j][1] = (dp[i][j][1] + ways * dp[i-k][j-k][1]) % mod;
                if (k < l) dp[i][j][0] = (dp[i][j][0] + ways * dp[i-k][j-k][0]) % mod;
                else dp[i][j][1] = (dp[i][j][1] + ways * dp[i-k][j-k][0]) % mod;
            }
        }
    }
    cout << dp[n][m][1] << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
