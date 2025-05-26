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

int dp[2][10000][5];
void solve(){
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    int shift = 4000;
    dp[0][shift][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = -shift; j <= shift; ++j) {
            int eu = i&1;
            for (int k = 0; k <= 4; ++k) {
                dp[eu][j+shift][k] = dp[eu^1][j+shift][k];
                if (k and -shift <= j - a[i-1] and j - a[i-1] <= shift) dp[eu][j+shift][k] += dp[eu^1][j-a[i-1]+shift][k-1];
            }
        }
    }
    int q; cin >> q;
    while (q--) {
        int x; cin >> x;
        cout << dp[n&1][x+shift][4] << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
