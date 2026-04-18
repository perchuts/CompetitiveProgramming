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

const int inf = 1e18;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve() {
    int n, m; cin >> n >> m;
    vector<ii> pos(m);
    vector<int> cost(m);
    for (int i = 0; i < m; ++i) cin >> pos[i].first >> pos[i].second >> cost[i], --pos[i].first, --pos[i].second;
    vector<int> dist(n, inf);
    vector<vector<ii>> g(n);
    for (int i = 1; i < m; ++i) {
        g[pos[i].first].pb({pos[i].second, cost[i]});
    }
    priority_queue<ii, vector<ii>, greater<>> pq;
    dist[pos[0].second] = 0;
    pq.push({0, pos[0].second});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue;
        for (auto [v, w] : g[u]) { 
            if (ckmin(dist[v], d+w)) pq.push({dist[v], v});
        }
    }
    if (dist[pos[0].first] == inf) cout << -1 << endl;
    else cout << dist[pos[0].first] + cost[0] << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
