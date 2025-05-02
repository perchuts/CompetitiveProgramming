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
    vector<vector<ii>> best(n+k+5, vector<ii>(2, make_pair(1e18, 0)));
    int S = 0;
    vector<int> v(n), c(n);
    for (int i = 0; i < n; ++i) cin >> c[i] >> v[i], S += v[i];
    v.pb(0); c.pb(n+1);
    n++;
    vector<int> pref(n+1);
    best[1][0] = {0, 0};
    vector<int> dp(k+1);
    for (int i = 1; i <= n; ++i) {
		pref[i] = pref[i-1] + v[i-1];
        for (int j = 0; j <= min(i-1, k); ++j) {
            dp[j] = 1e18;
            for (int w = 0; w < 2; ++w) if (best[i-j][w].second != c[i-1]) ckmin(dp[j], best[i-j][w].first + pref[i-1]);
        }
        for (int j = 0; j <= min(i-1, k); ++j) {
            dp[j] -= pref[i];
            if (dp[j] < best[i-j+1][1].first) {
                auto& [v0, c0] = best[i-j+1][0];
                auto& [v1, c1] = best[i-j+1][1];
                assert(c0 != c1 or !c0);
                if (c0 == c[i-1]) ckmin(v0, dp[j]);
                else if (c1 == c[i-1]) {
                    ckmin(v1, dp[j]);
                    if (v1 < v0) swap(best[i-j+1][0], best[i-j+1][1]);
                } else if (dp[j] <= v0) {
                    best[i-j+1][1] = {v0, c0};
                    best[i-j+1][0] = {dp[j], c[i-1]};
                } else best[i-j+1][1] = {dp[j], c[i-1]};
            }
            dp[j] += pref[i];
        }
    }
    cout << (dp.back() < 1e15 ? S-dp.back() : -1) << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
