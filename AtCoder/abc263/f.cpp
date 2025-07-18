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
    vector<vector<int>> award((1<<n), vector<int>(n+1)), dp = award;
    for (auto& x : award) for (int i = 1; i <= n; ++i) cin >> x[i];
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < (1 << n); j += (1 << i)) { 
            int mxl = 0, mxr = 0;
            for (int k = j; k < j + (1 << i); ++k) {
                if (k < j + (1 << (i-1))) ckmax(mxl, dp[k][i-1]);
                else ckmax(mxr, dp[k][i-1]);
            }
            for (int k = j; k < j + (1 << i); ++k) {
                if (k < j + (1 << (i-1))) dp[k][i] = dp[k][i-1] + mxr - award[k][i-1] + award[k][i];
                else dp[k][i] = dp[k][i-1] + mxl - award[k][i-1] + award[k][i];
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < (1 << n); ++i) ckmax(ans, dp[i][n]);
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
