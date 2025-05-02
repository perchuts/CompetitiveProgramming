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
    int n, x; cin >> n >> x;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    int ans = x;
    for (int k = 1; k <= n; ++k) {
        vector dp(k+1, vector(k+1, -inf*inf));
        dp[0][0] = 0;
        for (auto val : a) {
            vector ndp = dp;
            int eu = val%k;
            for (int j = 0; j < k; ++j) {
                int nmod = (j-eu+k)%k;
                for (int i = 1; i <= k; ++i) {
                    ckmax(ndp[i][j], val+dp[i-1][nmod]);
                }
            }
            swap(dp, ndp);
        }
        if (dp[k][x%k] > 0) ckmin(ans, (x-dp[k][x%k])/k);
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
