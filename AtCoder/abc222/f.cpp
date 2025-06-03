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
    int n; cin >> n;
    vector<vector<ii>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v, w; cin >> u >> v >> w;
        --u, --v;
        g[u].pb({v, w});
        g[v].pb({u, w});
    }
    vector<int> d(n);
    for (auto& x : d) cin >> x;
    vector<set<ii>> sexo(n);
    vector<int> down(n), up(n);
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        for (auto [v, w] : g[u]) {
            if (v == p) continue;
            self(self, v, u);
            sexo[u].insert({max(down[v], d[v]) + w, v});
            ckmax(down[u], max(down[v], d[v]) + w);
        }
    };
    dfs(dfs, 0, 0);
    auto dfs2 = [&] (auto&& self, int u, int p, int w) -> void {
        if (u != p) {
            sexo[p].erase({max(down[u], d[u]) + w, u});
            up[u] = max(up[p], d[p]) + w;
            if (!sexo[p].empty()) ckmax(up[u], prev(end(sexo[p]))->first + w);
            sexo[p].insert({max(down[u], d[u]) + w, u});
        }
        for (auto [v, w2] : g[u]) {
            if (v == p) continue;
            self(self, v, u, w2);
        }
    };
    dfs2(dfs2, 0, 0, 0);
    for (int i = 0; i < n; ++i) cout << max(down[i], up[i]) << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
