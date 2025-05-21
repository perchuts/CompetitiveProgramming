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
int ncr[100][100];
int dp[100][100];
int pot[100];
void solve(){
    int n, k; cin >> n >> k;
    int ans = 0, bits = 0, bicho = 0;
    for (int i = 59; ~i; --i) {
        // comecar aqui e dale
        if (1 <= bits) ans = (ans + ncr[i][k-1] * pot[i] + dp[i][k-1]) % mod;
        if (n >> i & 1) {
            if (1 <= bits and bits <= k) {
                ans = (ans + bicho * ncr[i][k-bits] + dp[i][k-bits]) % mod;
                ans %= mod;
            }
            bits++;
            bicho = (bicho + pot[i]) % mod;
        }
    }
    if (bits == k) ans = (ans + bicho) % mod;
    cout << ans << endl;
}

int32_t main(){_
    for (int i = 0; i < 100; ++i) for (int j = 0; j <= i; ++j) {
        if (j == 0 or j == i) ncr[i][j] = 1;
        else ncr[i][j] = (ncr[i-1][j] + ncr[i-1][j-1]) % mod;
    }
    pot[0] = 1;
    for (int i = 1; i <= 60; ++i) {
        pot[i] = (pot[i-1] + pot[i-1]) % mod;
        for (int j = 0; j <= i; ++j) {
            dp[i][j] = dp[i-1][j];
            if (j) {
                dp[i][j] = (dp[i][j] + pot[i-1] * ncr[i-1][j-1] + dp[i-1][j-1]) % mod;
            }
        }
    }
    int t = 1; cin >> t;
    while(t--) solve();
}
