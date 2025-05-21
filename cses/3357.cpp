#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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
int dist[2500][2500][2];
void solve(){
    int n, m, q; cin >> n >> m >> q;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) dist[i][j][0] = dist[i][j][1] = inf;
    auto get = [&] (int src) {
        dist[src][src][0] = 0;
        queue<ii> q;
        q.push({src, 0});
        while (!q.empty()) {
            auto [u, p] = q.front(); q.pop();
            int dx = dist[src][u][p]+1;
            for (auto v : g[u]) { 
                if (dist[src][v][0] == inf) dist[src][v][0] = dx, q.push({v, 0});
                else if (dist[src][v][0] % 2 != dx % 2 and dist[src][v][1] == inf) dist[src][v][1] = dx, q.push({v, 1});
            }
        }
    };
    for (int i = 0; i < n; ++i) get(i);
    while (q--) {
        int a, b, x; cin >> a >> b >> x;
        --a, --b;
        if (dist[a][b][0] % 2 == x % 2) cout << (dist[a][b][0] <= x ? "YES" : "NO") << endl;
        else cout << (dist[a][b][1] <= x and dist[a][b][1] % 2 == x % 2 ? "YES" : "NO") << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
