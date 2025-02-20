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
    int n, m, r; cin >> n >> m >> r;
    vector<int> v(r);
    for (auto& x : v) cin >> x, --x;
    vector<vector<int>> dist(n, vector<int>(n, 1e18));
    for (int i = 0; i < m; ++i) {
        int u, v, c; cin >> u >> v >> c;
        --u, --v;
        dist[u][v] = dist[v][u] = c;
    }
    for (int k = 0; k < n; ++k) for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) ckmin(dist[i][j], dist[i][k] + dist[k][j]);
    vector<vector<int>> dp(r, vector<int>(1<<r, 1e18));
    for (int i = 0; i < r; ++i) dp[i][1<<i] = 0;
    for (int i = 0; i < (1<<r); ++i) {
        for (int j = 0; j < r; ++j) {
            for (int k = 0; k < r; ++k) {
                if (j == k) continue;
                if (i >> j & 1) {
                    if (i >> k & 1) {
                        ckmin(dp[j][i], dp[k][i-(1<<j)] + dist[v[k]][v[j]]);
                    }
                }
            }
        }
    }
    int ans = 1e18;
    for (int i = 0; i < r; ++i) ckmin(ans, dp[i][(1<<r)-1]);
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
