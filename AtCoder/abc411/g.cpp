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
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        adj[u][v]++, adj[v][u]++;
    }
    vector<vector<int>> dp(1<<n, vector<int>(n));
    int ans = 0;
    for (int i = 0; i < (1<<n); ++i) {
        int c = __builtin_popcount(i);
        if (c < 2) continue;
        if (c == 2) {
            int u = -1, v = -1;
            for (int j = 0; j < n; ++j) {
                if (i >> j & 1) {
                    if (u == -1) u = j;
                    else v = j;
                }
            }
            dp[i][v] = adj[u][v];
            ans = (ans + adj[u][v] * (adj[u][v]-1)) % mod;
            continue;
        }
        int prim = -1;
        for (int j = 0; j < n; ++j) {
            if (i >> j & 1) {
                if (prim == -1) prim = j;
                for (int k = prim+1; k < n; ++k) {
                    if (i >> k & 1) {
                        dp[i][k] = (dp[i][k] + dp[i-(1<<k)][j] * adj[k][j]) % mod;
                        // aresta tem que ser pro primeiro cara do ciclo pra n ter overcounting
                    }
                }
            }
        }
        for (int k = prim+1; k < n; ++k) {
            ans = (ans + dp[i][k] * adj[k][prim]) % mod;
        }
    }
    ans = (ans * (mod+1)/2) % mod;
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
