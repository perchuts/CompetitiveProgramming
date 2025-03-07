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
    int n, m, k, l; cin >> n >> m >> k >> l;
    vector<int> a(n), b(l), important(n);
    vector<vector<ii>> g(n);
    for (auto& x : a) cin >> x, --x;
    for (auto& x : b) cin >> x, --x, important[x] = 1;
    vector<iii> edg(m);
    for (auto& [x, y, z] : edg) cin >> x >> y >> z, --x, --y, g[x].pb({y, z}), g[y].pb({x, z});
    vector<vector<ii>> dist(n, vector<ii>(2, pair(1e18, 1e18)));
    priority_queue<iii, vector<iii>, greater<>> pq;
    for (auto x : b) {
        pq.push({0, x, a[x]});
        dist[x][0] = {0, a[x]};
    }
    while (!pq.empty()) {
        auto [d, u, group] = pq.top(); pq.pop();
        bool ok = 0;
        for (int i = 0; i < 2; ++i) ok |= (dist[u][i] == pair(d, group));
        if (!ok) continue;
        for (auto [v, w] : g[u]) {
            int d2 = d + w;
            if (d2 < dist[v][1].first) {
                if (d2 <= dist[v][0].first) {
                    if (dist[v][0].second == group) {
                        if (ckmin(dist[v][0].first, d2)) pq.push({d2, v, group}); 
                    } else {
                        dist[v][1] = dist[v][0], dist[v][0] = pair(d2, group);
                        pq.push({d2, v, group});
                    }
                } else if (dist[v][0].second != group) {
                    dist[v][1] = pair(d2, group);
                    pq.push({d2, v, group});
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        int ans = 1e18;
        for (int j = 0; j < 2; ++j) if (a[i] != dist[i][j].second) ckmin(ans, dist[i][j].first);
        cout << (ans == 1e18 ? -1 : ans) << ' ';
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
