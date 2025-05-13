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
    int n, t, m, k; cin >> n >> t >> m >> k;
    // m * t presses
    // m * t <= 900
    vector<double> dp(k+1);
    dp[k] = 1.0;
    for (int __ = 1; __ <= t; ++__) {
        vector<double> ndp(k+1);
        ndp[k] = 1;
        for (int i = k-1; i >= 0; --i) {
            vector<vector<double>> temp(min(n, m) + 1, vector<double>(m+1));
            for (int j = 0; j <= min(n, m); ++j) temp[j][0] = dp[i];
            for (int j = min(n, m)-1; ~j; --j) {
                for (int w = 1; w <= m; ++w) {
                    double p = 1.0/(n-j);
                    for (int use = 1; use <= w; ++use) {
                        ckmax(temp[j][w], temp[j+1][w-use] * (1.0-p) + dp[min(k, use+i)] * p);
                    }
                }
            }
            ndp[i] = temp[0][m];
        }
        swap(dp, ndp);
    }
    cout << fixed << setprecision(10) << dp[0] << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

