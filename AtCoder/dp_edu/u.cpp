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
    int n; cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (auto& x : a) for (auto& y : x) cin >> y;
    vector<int> cost(1<<n);
    for (int i = 1; i < (1 << n); ++i) {
        for (int x = 0; x < n; ++x) for (int y = x + 1; y < n; ++y) {
            if (i >> x & 1) {
                if (i >> y & 1) {
                    cost[i] += a[x][y];
                }
            }
        }
    }
    vector<int> dp(1<<n);
    for (int i = 1; i < (1 << n); ++i) {
        dp[i] = cost[i];
        for (int s = (i-1)&i; s; s = (s-1)&i) {
            ckmax(dp[i], dp[i-s] + cost[s]);
        }
    }
    cout << dp.back() << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
