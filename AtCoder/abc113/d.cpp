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
    int h, w, k; cin >> h >> w >> k;
    // dp[linha][onde_estou] = formei todos os trocos ate a linha-esima linha, e estou na coluna onde_estou
    // resposta eh dp[h][k]
    vector<int> fib(w+1, 1);
    for (int i = 2; i <= w; ++i) fib[i] = (fib[i-1] + fib[i-2]) % mod;
    vector<vector<int>> dp(h+1, vector<int>(w+1));
    dp[0][1] = 1;
    for (int i = 1; i <= h; ++i) {
        for (int j = 1; j <= w; ++j) {
            dp[i][j] = (dp[i-1][j] * fib[max(0LL, j-1)] % mod * fib[w-j]) % mod;
            if (j != 1) dp[i][j] = (dp[i][j] + dp[i-1][j-1] * fib[max(j-2, 0LL)] % mod * fib[w-j]) % mod;
            if (j != w) dp[i][j] = (dp[i][j] + dp[i-1][j+1] * fib[max(0LL, j-1)] % mod * fib[max(0LL, w-j-1)]) % mod; 
        }
    }
    cout << dp[h][k] << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
