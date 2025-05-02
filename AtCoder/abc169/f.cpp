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
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve(){
    int n, s; cin >> n >> s;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<int> dp(s+1);
    dp[0] = 1;
    for (int i = 0; i < n; ++i) {
        vector<int> ndp(s+1);
        for (int j = 0; j <= s; ++j) {
            ndp[j] = 2 * dp[j] % mod;
            if (j >= a[i]) ndp[j] = (ndp[j] + dp[j-a[i]]) % mod;
        }
        swap(dp, ndp);
    }
    cout << dp[s] << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
