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
    int n, ma, mb; cin >> n >> ma >> mb;
    vector<vector<int>> dp(n*10+5, vector<int>(n*10+5, inf));
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        int a, b, c; cin >> a >> b >> c;
        auto ndp = dp;
        for (int j = a; j <= 10 * i; ++j) {
            for (int k = b; k <= 10 * i; ++k) {
                ckmin(ndp[j][k], dp[j-a][k-b] + c);
            }
        }
        swap(dp, ndp);
    }
    int ans = inf;
    for (int i = 1; i <= 10*n; ++i) for (int j = 1; j <= 10*n; ++j) {
        if (ma * j == mb * i) ckmin(ans, dp[i][j]);
    }
    cout << (ans == inf ? -1 : ans) << endl; 
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
