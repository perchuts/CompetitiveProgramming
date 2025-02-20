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
    vector<int> t(n), v(n);
    for (auto& x : t) cin >> x;
    for (auto& x : v) cin >> x;
    vector<int> points;
    for (int i = 0; i < n; ++i) for (int j = 0; j < 4*t[i]; ++j) points.pb(i);
    vector<vector<int>> dp(sz(points)+1, vector<int>(410, -1e9));
    dp[0][0] = 0;
    for (int i = 1; i <= sz(points); ++i) for (int j = 0; j <= min(4*v[points[i-1]], (i==sz(points)?0:4*v[points[i]])); ++j) {
        ckmax(dp[i][j], dp[i-1][j] + 2*j);
        if (j) ckmax(dp[i][j], dp[i-1][j-1] + 2*j-1);
        if (j < 400) ckmax(dp[i][j], dp[i-1][j+1]+2*j+1); 
    }
    cout << fixed << setprecision(10) << dp.back()[0]/32.0 << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
