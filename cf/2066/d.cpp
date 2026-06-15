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

int ncr[500][500];

void solve(){
    int n, c, m; cin >> n >> c >> m;
    vector<int> a(m);
    for (auto& x : a) cin >> x, --x;
    vector<int> dp(m+1);
    dp[c] = 1;
    for (int t = 1; t < n; ++t) {
        vector<int> ndp(m+1);
        for (int i = c; i <= m; ++i) {
            for (int j = 0; j <= min(c, m-i); ++j) {
                ndp[i+j] = (ndp[i+j] + dp[i] * ncr[c][j]) % mod;
            }
        }
        swap(dp, ndp);
    }
    cout << dp[m] << endl;
}

int32_t main(){_
    for (int i = 0; i < 500; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (i == 0 or j == i) ncr[i][j] = 1;
            else ncr[i][j] = (ncr[i-1][j] + ncr[i-1][j-1]) % mod;
        }
    }
    int t = 1; cin >> t;
    while(t--) solve();
}
