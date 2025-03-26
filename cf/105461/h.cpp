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
    int n, m, a, b; cin >> n >> m >> a >> b;
    --a, --b;
    vector<vector<int>> g(n);
    for (int i = 1; i <n ; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    vector<iii> tram(m);
    for (auto& [x, y, z] : tram) cin >> x >> y >> z, --x, --y;
    vector<vector<vector<ii>>> arrival(m, vector<vector<ii>>(n));
    vector<int> par(n), lvl(n), period(m);
    auto pre = [&] (auto&& self, int u, int p) -> void {
        for (auto v : g[u]) {
            if (v == p) continue;
            lvl[v] = 1 + lvl[u], par[v] = u;
            self(self, v, u);
        }
    };
    pre(pre, 0, 0);
    for (int i = 0; i < m; ++i) {
        vector<int> p, p2;
        auto [u, v, z] = tram[i];
        int c1 = u, c2 = v;
        while (lvl[c1] > lvl[c2]) p.pb(c1), c1 = par[c1];
        while (lvl[c2] > lvl[c1]) p2.pb(c2), c2 = par[c2];
        while (c1 != c2) p.pb(c1), p2.pb(c2), c1 = par[c1], c2 = par[c2];
        // lca!
        p.pb(c1);
        reverse(all(p2));
        for (auto x : p2) p.pb(x);
        int tt = 0, tam = sz(p);
        for (int j = 0; j < tam-1; ++j) arrival[i][p[j]].pb({tt, p[j+1]}), tt += z;
        arrival[i][p.back()].pb({tt, p[tam-2]});
        for (int j = sz(p)-1; j; --j) {
            arrival[i][p[j]].pb({tt, p[j-1]});
            tt += z;
        }
        period[i] = tt;
    }
    vector<int> dist(n, 1e18);
    dist[a] = 0;
    priority_queue<ii, vector<ii>, greater<>> pq;
    pq.push({0, a});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue;
        for (int i = 0; i < m; ++i) {
            int eu = d % period[i];
            auto [x, y, z] = tram[i];
            for (auto [md, v] : arrival[i][u]) {
                int d2 = (d/period[i])*period[i] + md;
                if (eu > md) d2 += period[i];
                assert(d2 >= d);
                if (ckmin(dist[v], d2+z)) pq.push({dist[v], v});
            }
        }
    }
    cout << (dist[b] < 1e18 ? dist[b] : -1) << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
