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
    int n; cin >> n;
    vector<int> a(n), freqA(n+1), fat(n+1, 1), ifat(n+1), inv(n+1);
    for (int i = 1; i <= n; ++i) fat[i] = i * fat[i-1] % mod;
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    ifat.back() = fexp(fat.back(), mod-2);
    for (int i = n-1; ~i; --i) ifat[i] = ifat[i+1] * (i+1) % mod;
    for (auto& x : a) cin >> x, freqA[x]++;
    for (int i = n-1; i; --i) freqA[i] += freqA[i+1];
    vector dp(n+1, vector(n+1, 0LL)), ncr = dp, poti = dp;
    for (int i = 0; i <= n; ++i) for (int j = 0; j <= n; ++j) poti[i][j] = (j == 0 ? 1 : poti[i][j-1] * ifat[i] % mod);
    for (int i = 0; i <= n; ++i) for (int j = 0; j <= i; ++j) {
        if (i == j or j == 0) ncr[i][j] = 1;
        else ncr[i][j] = (ncr[i-1][j] + ncr[i-1][j-1]) % mod;
    }
    dp[0][0] = 1;
    for (int i = n; i; --i) {
        vector ndp = dp;
        for (int j = 1; j <= n; ++j) {
            for (int k = j; k <= freqA[i]; ++k) {
                for (int x = 1; x * i <= k and x <= j; ++x) {
                    int temp = dp[j-x][k-x*i] * ncr[freqA[i] - j + x][x] % mod;
                    int temp2 = ncr[freqA[i] - k + x * i][x*i] % mod * fat[x*i] % mod * poti[i][x] % mod;
                    temp = temp * temp2 % mod;
                    ndp[j][k] = (ndp[j][k] + temp) % mod;
                }
            }
        }
        swap(dp, ndp);
    }
    int ans = 0;
    for (int j = 1; j <= n; ++j) ans = (ans + dp[j][n]) % mod;
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
