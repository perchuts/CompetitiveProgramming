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
    int n, m, x; cin >> n >> m >> x;
    vector<vector<vector<int>>> g(2, vector<vector<int>>(n));
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[0][u].pb(v);
        g[1][v].pb(u);
    }
    vector<vector<int>> dist(n, vector<int>(2, 1e18));
    dist[0][0] = 0;
    priority_queue<iii, vector<iii>, greater<>> pq;
    pq.push({0, 0, 0});
    while (!pq.empty()) {
        auto [d, u, type] = pq.top();
        pq.pop();
        if (d != dist[u][type]) continue;
        if (ckmin(dist[u][type^1], d + x)) {
            pq.push({d+x, u, type^1});
        }
        for (auto v : g[type][u]) {
            if (ckmin(dist[v][type], d + 1)) pq.push({d+1, v, type});
        }
    }
    cout << min(dist[n-1][0], dist[n-1][1]) << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
