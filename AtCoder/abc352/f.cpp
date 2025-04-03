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
    int n, m; cin >> n >> m;
    vector<vector<ii>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        --u, --v;
        g[u].pb({v, -w});
        g[v].pb({u, w});
    }
    vector<int> vis(n, inf), mask; vector<vector<int>> comp;
    auto dfs = [&] (auto&& self, int u) -> void {
        comp.back().pb(u);
        for (auto [v, w] : g[u]) {
            if (vis[v] != inf) continue;
            vis[v] = w + vis[u];
            self(self, v);
        }
    };
    for (int i = 0; i < n; ++i) {
        if (vis[i] != inf) continue;
        comp.pb(vector<int>());
        vis[i] = 0;
        dfs(dfs, i);
        int mn = 0, M = 0;
        for (auto x : comp.back()) ckmin(mn, vis[x]);
        for (auto x : comp.back()) vis[x] -= mn, M |= (1 << vis[x]);
        mask.pb(M);
    }
    int N = sz(mask);
    vector<vector<int>> dp1(N+2, vector<int>(1<<n)), dp2 = dp1;
    dp1[0][0] = dp2[N+1][0] = 1;
    for (int i = 1; i <= N; ++i) {
        assert(mask[i-1]&1);
        for (int eu = mask[i-1]; eu < (1 << n); eu <<= 1) {
            for (int j = 0; j < (1 << n); ++j) {
                if ((eu&j) == eu) dp1[i][j] |= dp1[i-1][j-eu];
            }
        }
    }
    for (int i = N; i >= 1; --i) {
        for (int eu = mask[i-1]; eu < (1 << n); eu <<= 1) {
            for (int j = 0; j < (1 << n); ++j) {
                if ((eu&j) == eu) dp2[i][j] |= dp2[i+1][j-eu];
            }
        }
    }
    vector<int> ans(n, -2);
    for (int i = 1; i <= N; ++i) {
        vector<int> pode;
        for (int eu = mask[i-1], shift = 0; eu < (1 << n); eu <<= 1, shift++) {
            int rest = (1 << n) - eu - 1;
            for (int j = 0; j < (1 << n); ++j) {
                if ((rest&j) == j) if (dp1[i-1][j] and dp2[i+1][rest-j]) {
                    pode.pb(shift);
                    break;
                }
            }
        }
        if (sz(pode) == 1) for (auto x : comp[i-1]) ans[x] = vis[x] + pode[0];
    }
    for (auto x : ans) cout << x+1 << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
