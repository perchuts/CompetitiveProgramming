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
    vector<int> target(n), cost(n);
    for (auto& x : target) cin >> x, --x;
    for (auto& x : cost) cin >> x;
    for (int i = 0; i < n; ++i) target.pb(target[i]), cost.pb(cost[i]);
    vector<int> prox(n+1, 2*n+1), seta(2*n+1);
    for (int i = 2*n; i >= 1; --i) seta[i] = prox[target[i-1]], prox[target[i-1]] = i;
    vector dp(2*n+2, vector(2*n+1, vector(2, inf*2*n)));
    // casos base
    for (int i = 0; i <= 2*n; ++i) dp[i+1][i][0] = dp[i+1][i][1] = 0;
    for (int l = 2*n; l >= 1; --l) {
        for (int r = l; r <= 2*n; ++r) {
            for (int turn = 1; ~turn; --turn) {
                if (turn and target[l-1] == target[r-1]) ckmin(dp[l][r][turn], dp[l+1][r][turn]);
                for (int k = l; k <= r; k = seta[k]) ckmin(dp[l][r][turn], dp[l+1][k][1] + dp[k+1][r][turn] + cost[target[l-1]] + k-l+1);
            }
        }
    }
    int ans = 1e18;
    for (int i = 1; i < n; ++i) ckmin(ans, dp[i][i+n-1][0]);
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
