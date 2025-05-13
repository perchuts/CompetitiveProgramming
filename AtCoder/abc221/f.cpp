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
    int n; cin >> n;
    vector<vector<int>> g(n);
    vector<int> dist(n), par(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    auto get_far = [&] (auto&& self, int u, int p) -> ii {
        if (u == p) dist[u] = 0;
        ii resp = {0, u};
        for (auto v : g[u]) {
            if (v == p) continue;
            dist[v] = dist[u] + 1, par[v] = u;
            ckmax(resp, self(self, v, u));
        }
        resp.first++;
        return resp;
    };
    int root = get_far(get_far, 0, 0).second;
    int D = get_far(get_far, root, root).first-1;
    if (D&1) {
        vector<int> vis(n), subt(n);
        auto find_cen = [&] (auto&& self, int u, int p, int S) -> int {
            for (auto v : g[u]) {
                if (vis[v] or v == p) continue;
                if (2 * subt[v] > S) return self(self, v, u, S);
            }
            return u;
        };
        auto get = [&] (auto&& self, int u, int p) -> void {
            subt[u] = 1;
            for (auto v : g[u]) {
                if (vis[v] or v == p) continue;
                self(self, v, u);
                subt[u] += subt[v];
            }
        };
        auto dfs = [&] (auto&& self, int u, int p) -> ii {
            ii ret = {0, 1};
            for (auto v : g[u]) {
                if (vis[v] or v == p) continue;
                auto cur = self(self, v, u);
                if (ret.first < cur.first) ret = cur;
                else if (ret.first == cur.first) ret.second += cur.second;
            }
            ret.first++;
            return ret;
        };
        int ans = 0;
        auto decomp = [&] (auto&& self, int u) -> void {
            get(get, u, u);
            u = find_cen(find_cen, u, u, subt[u]);
            ii big = {0, 1};
            for (auto v : g[u]) {
                if (vis[v]) continue;
                auto eu = dfs(dfs, v, u);
                if (eu.first + big.first == D) ans += eu.second * big.second;
                if (big.first < eu.first) big = eu;
                else if (big.first == eu.first) big.second += eu.second;
            }
            vis[u] = 1;
            for (auto v : g[u]) {
                if (vis[v]) continue;
                self(self, v);
            }
        };
        decomp(decomp, 0);
        ans %= mod;
        cout << ans << endl;
        exit(0);
    }
    int center = -1, ans = 0;
    for (int i = 0; i < n; ++i) {
        if (dist[i] == D) center = i;
    }
    assert(center != -1);
    for (int i = 0; i < D/2; ++i) center = par[center];
    get_far(get_far, center, center);
    int qt = 0, tot = 1;
    auto dfs2 = [&] (auto&& self, int u, int p) -> int {
        if (dist[u] * 2 == D) return 1;
        int ret = 0;
        for (auto v : g[u]) {
            if (v == p) continue;
            int k = self(self, v, u);
            if (u == p) {
                tot = tot * (k+1) % mod;
                qt += k;
            } else ret += k;
        }
        return ret;
    };
    dfs2(dfs2, center, center);
    ans = (tot - qt - 1 + mod) % mod;
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
