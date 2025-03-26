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
    vector<int> gain(n), c(m), gain2(n+1);
    for (auto& x : gain) cin >> x;
    for (int i = 0; i < m; ++i) cin >> c[i] >> gain2[c[i]];
    vector<int> dp(n+1, -1e18);
    dp[0] = 0;
    for (int i = 0; i < n; ++i) {
        vector<int> ndp(n+1, -1e18);
        for (int j = 1; j <= n; ++j) ndp[j] = dp[j-1] + gain[i] + gain2[j];
        for (int j = 0; j <= n; ++j) ckmax(ndp[0], dp[j]);
        swap(dp, ndp);
    }
    cout << *max_element(all(dp)) << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
