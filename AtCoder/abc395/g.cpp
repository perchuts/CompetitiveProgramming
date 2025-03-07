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
    vector<vector<int>> c(n, vector<int>(n));
    for (auto& x : c) for (auto& y : x) cin >> y;
    vector<vector<int>> ans(n, vector<int>(n, 1e18));
    auto steiner = [&] (vector<vector<int>> adj) {
        vector<vector<vector<int>>> d(1<<k, vector<vector<int>>(n, vector<int>(n, 1e18)));
        d[0] = adj;
        for (int x = 0; x < n; ++x) for (int y = 0; y < n; ++y) for (int z = 0; z < n; ++z) ckmin(d[0][y][z], d[0][y][x] + d[0][x][z]);
        for (int i = 0; i < k; ++i) d[1 << i][i][i] = 0;
        vector<vector<int>> d_b(1<<k, vector<int>(n, 1e18));
        for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) ckmin(d_b[0][i], d[0][i][j]);
        for (int mask = 1; mask < (1 << k); mask++) {
            for (int a = (mask - 1) & mask; a; a = (a - 1) & mask) {
                int b = mask ^ a;
                for (int v = 0; v < n; v++)
                    for (int w = 0; w < n; ++w) {
                        ckmin(d[mask][v][w], d_b[a][v] + d[b][w][v]);
                        ckmin(d[mask][v][w], d_b[b][v] + d[a][w][v]);
                        ckmin(d[mask][v][w], d_b[a][w] + d[b][w][v]);
                        ckmin(d[mask][v][w], d_b[b][w] + d[a][w][v]);
                    }
            }
            int a = 0, b = mask;
            priority_queue<tuple<ll, int, int>> pq;
            for (int v = 0; v < n; v++) {
                for (int w = 0; w < n; ++w) {
                    if (d[mask][v][w] == 1e18) continue;
                    pq.emplace(-d[mask][v][w], v, w);
                }
            }
            while (pq.size()) {
                auto [ndist, u, v] = pq.top(); pq.pop();
                if (-ndist > d[mask][u][v]) continue;
                if (ckmin(d[mask][v][u], d[mask][u][v])) pq.emplace(-d[mask][v][u], v, u);
                for (int idx = 0; idx < n; ++idx) if (ckmin(d[mask][idx][v], d[mask][u][v] + min(adj[v][idx], adj[u][idx]))) pq.emplace(-d[mask][idx][v], idx, v);
            }
            for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) ckmin(d_b[mask][i], d[mask][i][j]);
        }
        for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) ans[i][j] = d[(1<<k)-1][i][j];
    };
	steiner(c);
    int q; cin >> q;
    while (q--) {
        int u, v; cin >> u >> v;
        --u, --v;
        cout << ans[u][v] << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
