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
    int n, z, w; cin >> n >> z >> w;
    n++; 
    vector<int> a(n); a[0] = w;
    for (int i = 1; i < n; ++i) cin >> a[i];
    vector<vector<int>> dp(n+1, vector<int>(2));
    int ans = abs(a.back()-w);
    for (int i = n; i > 1; --i) {
        dp[i][0] = dp[i][1] = abs(a[i-2]-a.back());
        for (int j = i+1; j <= n; ++j) {
            ckmax(dp[i][0], dp[j][1]);
            ckmin(dp[i][1], dp[j][0]);
        }
    }
    cout << max(dp[2][0], ans) << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
