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
    int n, m; cin >> n >> m;
    int lim1 = sqrt(n);
    vector dp1(n+1, vector(n+1, 0LL));
    dp1[0][0] = 1;
    for (int val = 1; val <= lim1; ++val) {
        vector ndp(n+1, vector(n+1, 0LL));
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= i; ++j) {
                for (int k = 0; k <= min({m, i/val, j}); ++k) {
                    ndp[i][j] = (ndp[i][j] + dp1[i-k*val][j-k]) % mod;
                }
            }
        }
        swap(dp1, ndp);
    }
    int lim2 = n / (lim1+1);
    vector dp2(n+1, vector(lim2+1, 0LL));
    dp2[0][0] = 1;
    for (int val = lim1+1; val <= n; ++val) {
        for (int i = 0; i <= n; ++i) {
            for (
        }
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
