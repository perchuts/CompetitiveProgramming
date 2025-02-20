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
    int n, m; cin >> n >> m;
    vector dp(n+1, vector(n+1, 0LL)), tr = dp, ncr = dp;
    vector<int> pot(n+1, 1);
    for (int i = 0; i <= n; ++i) for (int j = 0; j <= i; ++j) {
        if (i == j or j == 0) ncr[i][j] = 1;
        else ncr[i][j] = (ncr[i-1][j] + ncr[i-1][j-1]) % m;
    }
    for (int i = 1; i <= n; ++i) pot[i] = 2 * pot[i-1] % m;
    dp[1][1] = 1;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) {
        if (j == 1) tr[i][j] = (pot[i]+m-1)%m;
        else tr[i][j] = tr[i][j-1] * pot[j-1] % m * (pot[i]+m-1) % m;
    }
    // dp[i][j] = numero de grafos com i vertices e tem j vertices com distancia maxima
    // dp[i][j] = dp[i-j][k] * fodase
    dp[1][1] = 1;
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j < i; ++j) {
            for (int k = 1; j + k <= i; ++k) {
                dp[i][j] = (dp[i][j] + dp[i-j][k] * tr[k][j] % m) % m;
            }
            if (i == n) {
                cout << dp[i][j] << endl;
                exit(0);
            }
            dp[i][j] = dp[i][j] * ncr[i-1][j] % m; 
        }
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
