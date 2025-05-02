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
    int n, k; cin >> n >> k;
    vector<array<int, 3>> v(n);
    for (int i = 0; i < n; ++i) for (int j = 0; j < 3; ++j) cin >> v[i][j];
    auto solve = [&] (int lambda) {
        vector<ii> dp(8, make_pair(-1e18, 0));    
        dp[0] = {0, 0};
        for (auto arr : v) {
            vector<ii> ndp = dp;
            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 3; ++j) {
                    int cost = dp[i^(1<<j)].first + arr[j] - ((i>>j&1) ? lambda : 0);
                    int use = dp[i^(1<<j)].second + (i>>j&1);
                    if (ckmax(ndp[i].first, cost) or (ndp[i].first == cost and use < ndp[i].second)) ndp[i] = {cost, use};
                }
            }
            swap(dp, ndp);
        }
        return dp[0];
    };
    int l = 0, r = 3e9, opt = 0;
    while (l <= r) {
        int md = l + (r-l+1)/2;
        auto [___, used] = solve(md);
        if (used <= k) opt = md, r = md-1;
        else l = md+1;
    }
    auto [ganhou, usou] = solve(opt);
    cout << ganhou + opt*usou + (k-usou)*opt << endl;
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) solve();
}

