#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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
    int n, x; cin >> n >> x;
    auto add = [&] (int& a, int b) {
        a += b;
        if (a >= mod) a -= mod;
    };
    vector dp(n+1, vector(1<<(2*x-1), 0)); dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        vector ndp(n+1, vector(1<<(2*x-1), 0));
        for (int j = 0; j <= i; ++j) {
            for (int used = 0; used < (1 << (2*x-1)); ++used) {
                if (2*used < (1<<(2*x-1))) ndp[j][used] = dp[j][2*used];
                if (2*used+1 < (1<<(2*x-1))) add(ndp[j][used], dp[j][2*used+1]);
                for (int usar = 0; usar < 2*x-1 and j; ++usar) {
                    if (i+usar-x+1 < 1 or i+usar-x+1 > n) continue;
                    if (used >> usar & 1) {
                        int novo = used - (1 << usar);
                        if (2*novo < (1<<(2*x-1))) add(ndp[j][used], dp[j-1][2*novo]);
                        if (2*novo+1 < (1<<(2*x-1))) add(ndp[j][used], dp[j-1][2*novo+1]);
                    }
                }
            }
        }
        swap(dp, ndp);
    }
    vector<ll> fat(n+1, 1);
    for (ll i = 1; i <= n; ++i) fat[i] = fat[i-1] * i % mod;
    int ans = 0;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < (1 << (2*x-1)); ++j) {
            ll ways = dp[i][j] * fat[n-i] % mod;
            if (i & 1) ans = (ans + mod - ways) % mod;
            else ans = (ans + ways) % mod;
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
