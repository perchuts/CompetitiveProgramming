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
    int x, y; cin >> x >> y;
    int ans = abs(x-y);
    for (int k = 0; x < 2*y; x *= 2, k++) {
        int falta = abs(x-y), penis = falta;
        for (int j = 0; j < k; ++j, falta /= 2) {}
        vector<vector<int>> dp(k+1, vector<int>(2, 2e18));
        dp[k][1] = falta+1, dp[k][0] = falta;
        for (int j = k-1; ~j; --j) {
            if (penis>>j&1) {
                dp[j][1] = dp[j+1][1];
                dp[j][0] = dp[j+1][0]+1;
                ckmin(dp[j][0], dp[j][1]+1);
            } else {
                dp[j][1] = dp[j+1][1]+1;
                dp[j][0] = dp[j+1][0];
                ckmin(dp[j][1], dp[j][0]+1);
            }
        }
        ckmin(ans, dp[0][0]+k);
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

