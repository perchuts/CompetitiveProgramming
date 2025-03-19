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
    int n, m; cin >> n >> m;
    vector<int> a(n+1), b(n+1), mark(n+1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    for (int i = 0; i < m; ++i) {
        int x; cin >> x;
        mark[x] = 1;
    }
    // dp[i][j] = minimum number of items to buy if i vanished with all pos <= i and bought j items in total
    vector<int> dp(n+1, 1e18);
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        vector<int> ndp(n+1, 1e18);
        if (!mark[i]) ndp = dp;
        int mn = b[i];
        for (int j = 1; j <= i; ++j) {
            ckmin(ndp[j], dp[j-1] + mn + a[i]);
            ckmin(mn, b[i-j]);
        }
        swap(dp, ndp);
    }
    cout << (*min_element(all(dp))) << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
