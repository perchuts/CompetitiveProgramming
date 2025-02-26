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
const int mod = (119<<23)+1;
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
    vector<vector<int>> no_edges(n);
    for (int i = 0; i < n; ++i) no_edges[i].pb(i);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        no_edges[u].pb(v), no_edges[v].pb(u);
    }
    int N = 6*n;
    vector<vector<ii>> g(N);
    auto add = [&] (auto&& self, int i, int l, int r, int x, int y, int v) -> void {
        if (r < x or y < l or x > y) return;
        if (x <= l and r <= y) {
            g[v].pb({i+n, 1});
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md, x, y, v), self(self, 2*i+1, md+1, r, x, y, v);
    };
    auto build = [&] (auto&& self, int i, int l, int r) {
        if (l == r) {
            g[i+n].pb({l, 0});
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md), self(self, 2*i+1, md+1, r);
        g[i+n].pb({2*i+n, 0}), g[i+n].pb({2*i+1+n, 0});
    };
    build(build, 1, 0, n-1);
    for (int i = 0; i < n; ++i) {
        int lst = -1;
        sort(all(no_edges[i]));
        for (auto j : no_edges[i]) {
            add(add, 1, 0, n-1, lst+1, j-1, i);
            lst = j;
        }
        add(add, 1, 0, n-1, lst+1, n-1, i);
    }
    vector<int> dp(N), dist(N, inf);
    dp[0] = 1, dist[0] = 0;
    set<int> cur, prox;
    cur.insert(0);
    while (!cur.empty()) {
        while (!cur.empty()) {
            auto u = *begin(cur);
            cur.erase(begin(cur));
            for (auto [v, d] : g[u]) {
                if (ckmin(dist[v], dist[u] + d)) {
                    if (!d) cur.insert(v);
                    else prox.insert(v);
                    dp[v] = dp[u];
                } else if (dist[v] == dist[u] + d) dp[v] = (dp[v] + dp[u]) % mod;
            }
        }
        swap(cur, prox);
    }
    cout << (dist[n-1] == inf ? -1 : dp[n-1]) << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
