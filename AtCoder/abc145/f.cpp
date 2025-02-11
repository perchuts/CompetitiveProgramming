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
    int n, k; cin >> n >> k;
    vector<int> h(n+1);
    for (int i = 1; i <= n; ++i) cin >> h[i];
    vector dp(n+1, vector(k+1, vector(2, inf*inf)));
    dp[0][0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= min(i, k); ++j) {
            if (j) {
                // usar drogas
                for (int w = i-1; j >= i-w and w >= 0; --w) ckmin(dp[i][j][1], dp[w][j-(i-w)][0]);
            }
            // nao usar drogas
            for (int w = i-1; j >= i-w-1 and w >= 0; --w) {
                ckmin(dp[i][j][0], dp[w][j-(i-w-1)][0] + max(0LL, h[i]-h[w]));
            }
        }
    }
    int ans = inf*inf;
    for (int i = 0; i <= k; ++i) ckmin(ans, min(dp[n][i][0], dp[n][i][1]));
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
