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
    vector<vector<int>> adj(n, vector<int>(n));
    vector<ii> edg(m);
    for (auto& [x, y] : edg) cin >> x >> y, --x, --y, adj[x][y] = adj[y][x] = 1;
    vector<int> ans(n);
    vector<int> dp(1<<n, 1), inside(1<<n, 1);
    for (int i = 0; i < (1<<n); ++i) {
        for (auto [u, v] : edg) {
            int k = (1 << u) + (1 << v);
            if ((k & i) == k) inside[i] = 2 * inside[i] % mod;
        }
    }
    int tudo = (1<<n)-1;
    for (int i = 1; i < (1<<n); i += 2) {
        dp[i] = inside[i];
        for (int j = (i-1)&i; j; j = (j-1)&i) {
            if (j % 2 == 0) continue;
            dp[i] = (dp[i] - dp[j] * inside[i-j]) % mod, dp[i] = (dp[i] + mod) % mod;
        }
        for (int j = 1; j < n; ++j) if (i >> j & 1) ans[j] = (ans[j] + dp[i] * inside[tudo-i]) % mod;
    }
    for (int j = 1; j < n; ++j) cout << ans[j] << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
