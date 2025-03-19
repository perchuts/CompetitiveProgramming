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
    vector<vector<int>> g(n);
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    vector<vector<vector<vector<int>>>> dp(n);
    auto merge = [&] (vector<vector<vector<int>>> A, vector<vector<vector<int>>> B) {
        int subt = sz(A[0][0]) + sz(B[0][0]) - 1;
        vector<vector<vector<int>>> res(2, vector<vector<int>>(2, vector<int>(subt, 0LL)));
        for (int i = 0; i < sz(A[0][0]); ++i) for (int j = 0; j < sz(B[0][0]); ++j) {
            for (int viza = 0; viza < 2; ++viza) {
                for (int eua = 0; eua < 2; ++eua) {
                    for (int vizb = 0; vizb < 2; ++vizb) {
                        for (int eub = 0; eub < 2; ++eub) {
                            int add = i + j + (eua == 1 and vizb == 0 and eub == 0) + (viza == 0 and eua == 0 and eub == 1);
                            if (add == subt) continue;
                            res[viza|eub][eua][add] = (res[viza|eub][eua][add] + A[viza][eua][i] * B[vizb][eub][j]) % mod;
                        }
                    }
                }
            }

        }
        return res;
    };
    auto printDP = [&] (int u) {
        cout << "printing DP " << u << ": " << endl;
        for (int p = 0; p < 2; ++p) for (int eu = 0; eu < 2; ++eu) {
            for (int i = 0; i < sz(dp[u][0][0]); ++i) {
                cout << "viz = " << p << " eu = " << eu << " i = " << i << ": " << dp[u][p][eu][i] << endl;
            }
        }
    };
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        dp[u] = vector<vector<vector<int>>>(2, vector<vector<int>>(2, vector<int>(2)));
        dp[u][0][1][1] = dp[u][0][0][0] = 1;
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
            dp[u] = merge(dp[u], dp[v]);
        }
    };
    dfs(dfs, 0, 0);
    for (int k = 0; k <= n; ++k) {
        int ans = (dp[0][0][0][k] + dp[0][0][1][k] + dp[0][1][0][k] + dp[0][1][1][k]) % mod;
        cout << ans << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
