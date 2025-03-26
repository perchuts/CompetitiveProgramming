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
    int n, m, k; cin >> n >> m >> k;
    auto w = [&] (int a, int b, int c, int d) {
        if (a > c or b > d) return 0LL;
        if (c > n or d > m) return 0LL;
        int L1 = (c-a+1), L2 = (d-b+1);
        return (L1+1)*(L2+1)*L1*L2/4 % mod;
    };
    int ans = 0, tot_ways = w(1, 1, n, m);
    vector<int> pot(k+1, 1);
    for (int i = 1; i <= k; ++i) pot[i] = pot[i-1] * tot_ways % mod;
    vector dp(n+1, vector(m+1, vector(n+1, vector(m+1, 0LL))));
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
        for (int a = i; a <= n; ++a) for (int b = j; b <= m; ++b) {
            if (i == a and b == j) dp[i][j][a][b] = i*j*(n-i+1)*(m-j+1);
            else {
                dp[i][j][a][b] = (dp[i][j][a-1][b] + dp[i][j][a][b-1] - dp[i][j][a-1][b-1] + mod) % mod;
                if (a > i and b > j) dp[i][j][a][b] = (dp[i][j][a][b] + (n-a+1)*(m-b+1)) % mod;
                else if (a > i) dp[i][j][a][b] = (dp[i][j][a][b] + b*(m-b+1)*(n-a+1)) % mod;
                else dp[i][j][a][b] = (dp[i][j][a][b] + a*(m-b+1)*(n-a+1)) % mod;
            }
        }
    }
    for (int x1 = 1; x1 <= n; ++x1) {
        for (int y1 = 1; y1 <= m; ++y1) {
            for (int x2 = x1; x2 <= n; ++x2) {
                for (int y2 = y1; y2 <= m; ++y2) {
                    int tot = 1, ways = (tot_ways -dp[x1][y1][x2][y2] + mod) % mod, curtot = 0;
                    for (int a = 0; a < k; ++a) {
                        curtot = (curtot + tot * pot[k-1-a]) % mod;
                        tot = tot * ways % mod;
                    }
                    ans = (ans + curtot) % mod;
                }
            }
        }
    }
    auto fexp = [&] (int b, int e) {
        int resp = 1;
        while (e) {
            if (e&1) resp = resp * b % mod;
            e /= 2, b = b * b % mod;
        }
        return resp;
    };
    ans = ans * fexp(pot[k], mod-2) % mod;
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
