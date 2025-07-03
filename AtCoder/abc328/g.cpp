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

//int dp[1<<22][23];
int dp[1<<22], cost[22][22][22];

void solve(){
    int n, c; cin >> n >> c;
    vector<int> a(n), b(n);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            for (int k = 0; k+j-i < n; ++k) {
                if (i == j) {
                    cost[i][j][k] = abs(a[i]-b[k]);
                } else {
                    cost[i][j][k] = cost[i][j-1][k] + abs(a[j] - b[k+j-i]);
                }
            }
        }
    }
    for (int i = 1; i < (1 << n); ++i) {
        dp[i] = 1e18;
        for (int j = 0; j < n; ++j) {
            int bits = __builtin_popcount(i);
            if (i >> j & 1) {
                int m = i;
                for (int k = j; k < n; ++k) {
                    if (!(i >> k & 1)) break;
                    m -= (1 << k), bits--;
                    ckmin(dp[i], dp[m] + c + cost[j][k][bits]);
                }
            }
        }
    }
    cout << dp[(1<<n)-1]-c << endl;
    //for (int i = 1; i < (1<<n); ++i) {
    //    int agr = __builtin_popcount(i)-1;
    //    dp[i][n] = 1e18;
    //    for (int j = 0; j < n; ++j) {
    //        if (i >> j & 1) {
    //            dp[i][j] = dp[i-(1<<j)][n] + c + abs(a[j]-b[agr]);
    //            if (j and (i>>(j-1)&1)) ckmin(dp[i][j], dp[i-(1<<j)][j-1] + abs(a[j]-b[agr]));
    //            ckmin(dp[i][n], dp[i][j]);
    //        }
    //    }
    //}
    //cout << dp.back().back()-c << endl;
    
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
