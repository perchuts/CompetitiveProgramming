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
    int n, x; cin >> n >> x;
    vector<vector<double>> dp(1<<n, vector<double>(x+1));
    vector<int> s(n), c(n), p(n);
    for (int i = 0; i < n; ++i) cin >> s[i] >> c[i] >> p[i];
    for (int i = 1; i < (1 << n); ++i) {
        for (int j = 1; j <= x; ++j) {
            for (int k = 0; k < n; ++k) {
                if (i >> k & 1) {
                    if (c[k] <= j) ckmax(dp[i][j], (p[k] * (dp[i-(1<<k)][j-c[k]] + s[k]) + (100-p[k]) * (dp[i][j-c[k]])) / 100.0);
                }
            }
            // tenho essa quantia de dinheiro, como vou gastar?
        }
    }
    cout << fixed << setprecision(10) <<  dp.back().back() << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
