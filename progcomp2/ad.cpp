#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
	using ord_set = tree<T, null_type, less<T>, rb_tree_tag,
	tree_order_statistics_node_update>;
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;
const int logn = 20;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}


void solve() {
    int n, q; cin >> n >> q;
    vector<vector<ii>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v, w; cin >> u >> v >> w; --u, --v;
        g[u].pb({v, w});
        g[v].pb({u, w});
    }
    vector<int> vis(n), subt(n);
    vector<vector<int>> g2(n), bichos(n);
    vector<vector<ii>> par(n);
    auto calc = [&] (auto&& self, int u, int p) -> int {
        subt[u] = 1;
        for (auto [v, w] : g[u]) {
            if (vis[v] or v == p) continue;
            subt[u] += self(self, v, u);
        }
        return subt[u];
    };
    auto find_cen = [&] (auto&& self, int u, int p, int nn) -> int {
        for (auto [v, w] : g[u]) {
            if (vis[v] or v == p) continue;
            if (2 * subt[v] > nn) return self(self, v, u, nn);
        }
        return u;
    };
    auto dfs = [&] (auto&& self, int u, int p, int h, int cen) -> void {
        bichos[cen].pb(u);
        par[u].pb({cen, h});
        for (auto [v, w] : g[u]) {
            if (vis[v] or v == p) continue;
            self(self, v, u, w + h, cen);
        }
    };
    auto decomp = [&] (auto&& self, int u, int p) -> void {
        int cen = find_cen(find_cen, u, u, calc(calc, u, u));
        if (p != -1) g2[p].pb(cen);
        vis[cen] = 1;
        bichos[cen].pb(cen);
        par[cen].pb({cen, 0});
        reverse(all(par[cen]));
        for (auto [v, w] : g[cen]) {
            if (vis[v]) continue;
            dfs(dfs, v, cen, w, cen);
        }
        for (auto [v, w] : g[cen]) {
            if (!vis[v]) {
                self(self, v, cen);
            }
        }
    };
    decomp(decomp, 0, -1);
    vector<vector<array<int, 3>>> queries(n);
    vector<ii> qry(q);
    vector<int> ans(q), pos(n);
    for (int i = 0; i < q; ++i) {
        int u, l; cin >> u >> l; --u;
        qry[i] = {u, l};
        int lst = -1;
        for (auto [cc, dd] : par[u]) {
            queries[cc].pb({lst, i, dd});
            lst = cc;
        }
    }
    for (int i = 0; i < n; ++i) {
        // retirar as alturas uma a uma 
        ord_set<ii> ss;
        for (auto u : bichos[i]) {
            int j = 0;
            while (par[u][j].first != i) j++;
            pos[u] = j;
            ss.insert({par[u][j].second, u});
         }
        sort(all(queries[i]));
        for (int l = 0, r = 0; l < sz(queries[i]); l = r) {
            while (r != sz(queries[i]) and queries[i][l][0] == queries[i][r][0]) r++;
            int z = queries[i][l][0];
            if (z != -1) {
                for (auto u : bichos[z]) ss.erase({par[u][pos[u]].second, u});
            }
            for (int k = l; k < r; ++k) {
                auto [u, l] = qry[queries[i][k][1]];
                ans[queries[i][k][1]] += ss.order_of_key(pair(l-queries[i][k][2], inf));
            }
            if (z != -1) {
                for (auto u : bichos[z]) ss.insert({par[u][pos[u]].second, u});
            }
        }
    }
    for (auto x : ans) cout << x << endl;
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
