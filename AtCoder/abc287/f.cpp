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
    int n; cin >> n;
    vector<vector<int>> g(n);
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(2));
    auto merge = [&] (vector<vector<int>> A, vector<vector<int>> B) {
        int tam = sz(A[0]) + sz(B[0]) - 1;
        vector<vector<int>> res(2, vector<int>(tam));
        for (int i = 0; i < sz(A[0]); ++i) {
            for (int j = 0; j < sz(B[0]); ++j) {
                for (int aa = 0; aa < 2; ++aa) for (int bb = 0; bb < 2; ++bb) {
                    if (aa + bb == 2 and i + j == 0) continue;
                    int x = i+j - (aa&bb);
                    if (x == tam) continue;
                    res[aa][x] = (res[aa][x] + A[aa][i] * B[bb][j]) % mod;
                }
            }
        }
        return res;
    };
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        dp[u][0] = {1, 0};
        dp[u][1] = {0, 1};
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
            dp[u] = merge(dp[u], dp[v]);
        }
    };
    dfs(dfs, 0, 0);
    for (int i = 1; i <= n; ++i) cout << (dp[0][1][i] + dp[0][0][i]) % mod << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
