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
    int n, q; cin >> n >> q;
    vector<vector<iii>> g(n);
    int block = 250;
    vector<int> freq(n-1), rev_id(n-1), heavy;
    vector<vector<iii>> edges(n-1);
    for (int i = 0; i < n-1; ++i) {
        int u, v, a, b; cin >> u >> v >> a >> b;
        --u, --v, --a;
        freq[a]++;
        edges[a].pb({u, v, b});
        g[u].pb({v, a, b});
        g[v].pb({u, a, b});
    }
    for (int i = 0; i < n-1; ++i) {
        if (freq[i] > block) rev_id[i] = sz(heavy), heavy.pb(i);
    }
    vector<vector<ii>> qnt;
    auto process = [&] (auto&& self, int u, int p, int x, int tot = 0, int tot2 = 0) -> void {
        qnt.back()[u] = {tot, tot2};
        for (auto [v, cor, dist] : g[u]) {
            if (v == p) continue;
            self(self, v, u, x, tot + (cor == x), tot2 + (cor == x ? dist : 0));
        }
    };
    for (auto x : heavy) {
        qnt.pb(vector<ii>(n));
        process(process, 0, 0, x);
    }
    vector<vector<ii>> bl(n, vector<ii>(17));
    vector<int> lvl(n), tin(n), tout(n);
    int tt = 0;
    auto dfs = [&] (auto&& self, int u, int p, int dd) -> void {
        lvl[u] = 1 + lvl[p];
        bl[u][0] = {p, dd};
        tin[u] = tt++;
        for (int i = 1; i < 17; ++i) {
            auto [xx, yy] = bl[u][i-1];
            bl[u][i] = {bl[xx][i-1].first, yy + bl[xx][i-1].second};
        }
        for (auto [v, cor, d] : g[u]) {
            if (v == p) continue;
            self(self, v, u, d);
        }
        tout[u] = tt;
    };
    dfs(dfs, 0, 0, 0);
    auto lca = [&] (int u, int v) {
        // returns lca + dist? yes
        if (lvl[u] < lvl[v]) swap(u, v);
        int tot_dist = 0;
        for (int i = 16; ~i; --i) {
            auto [xx, yy] = bl[u][i];
            if (lvl[xx] >= lvl[v]) tot_dist += yy, u = xx;
        }
        if (u == v) return make_pair(u, tot_dist);
        for (int i = 16; ~i; --i) {
            auto [x1, y1] = bl[u][i];
            auto [x2, y2] = bl[v][i];
            if (x1 != x2) u = x1, v = x2, tot_dist += y1 + y2;
        }
        assert(bl[u][0].first == bl[v][0].first);
        tot_dist += bl[u][0].second + bl[v][0].second;
        return make_pair(bl[u][0].first, tot_dist);
    };
    auto is_inside = [&] (int u, int v) {
        return (tin[u] <= tin[v] and tout[v] <= tout[u]);
    };
    while (q--) {
        int u, v, c, d2; cin >> c >> d2 >> u >> v;
        --u, --v, --c;
        auto [l, d] = lca(u, v);
        if (freq[c] <= block) {
            for (auto [a, b, d3] : edges[c]) {
                if (lvl[a] < lvl[b]) swap(a, b);
                if (is_inside(l, b) and (is_inside(a, u) or is_inside(a, v))) {
                    d += d2 - d3; 
                }
            }
            cout << d << endl;
        } else {
            int i = rev_id[c];
            auto [q1, s1] = qnt[i][u];
            auto [q2, s2] = qnt[i][v];
            auto [q3, s3] = qnt[i][l];
            int ans = d - s1 - s2 + 2*s3 + (q1+q2-2*q3)*d2;
            cout << ans << endl;
        }
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
