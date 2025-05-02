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
    vector<vector<pair<int, char>>> g(n);
    for (int i = 0; i < m; ++i) {
        int a, b; char c; cin >> a >> b >> c;
        --a, --b;
        g[a].pb({b, c});
        if (a != b) g[b].pb({a, c});
    }
    vector<vector<int>> dist(n, vector<int>(n+1, inf));
    queue<ii> q;
    for (int i = 0; i < n; ++i) {
        for (auto [j, c] : g[i]) dist[i][j] = 1, q.push({i, j});
    }
    for (int i = 0; i < n; ++i) {
        for (auto [j1, c1] : g[i]) {
            for (auto [j2, c2] : g[i]) {
                if (c1 == c2) {
                    if (ckmin(dist[j1][j2], 2)) q.push({j1, j2});
                    if (ckmin(dist[j2][j1], 2)) q.push({j2, j1});
                }
            }
        }
    }
    while (!q.empty()) {
        auto [u, v] = q.front(); q.pop();
        for (auto [j1, c1] : g[u]) for (auto [j2, c2] : g[v]) {
            if (c1 == c2) {
                if (ckmin(dist[j1][j2], dist[u][v]+2)) q.push({j1, j2});
                if (ckmin(dist[j2][j1], dist[u][v]+2)) q.push({j2, j1});
            }
        }
    }
    cout << (dist[0][n-1] == inf ? -1 : dist[0][n-1]) << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
