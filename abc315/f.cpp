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
    int n; cin >> n;
    vector<ii> pt(n+1);
    for (int i = 1; i <= n; ++i) cin >> pt[i].first >> pt[i].second;
    vector<vector<double>> dp(n+1, vector<double>(30, 1e18));
    dp[1][0] = 0;
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j <= min(29LL, i-2); ++j) {
            for (int take = 0; take <= j; ++take) {
                ckmin(dp[i][j], dp[i-take-1][j-take] + hypot(pt[i].first-pt[i-take-1].first, pt[i].second-pt[i-take-1].second));
            }
        }
    }
    double ans = dp[n][0];
    for (int j = 0; j < 29; ++j) ckmin(ans, dp[n][j+1] + (1 << j));
    cout << fixed << setprecision(10) << ans << endl;

}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
