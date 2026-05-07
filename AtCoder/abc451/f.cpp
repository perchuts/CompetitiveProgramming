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

void solve() {
    int n, q; cin >> n >> q;
    vector<vector<vector<int>>> comps(n, vector<vector<int>>(2));
    for (int i = 0; i < n; ++i) comps[i][0].pb(i);
    vector<int> par(n), lvl(n, 1); iota(all(par), 0);
    vector<int> qual_lado(n);
    auto findp = [&] (auto&& self, int u) -> int { return par[u] = (par[u] == u ? u : self(self, par[u])); };
    int smaller_side = 0;
    auto unite = [&] (int u, int v) -> int {
        int pu = findp(findp, u), pv = findp(findp, v);
        if (pu == pv) return (qual_lado[u] != qual_lado[v]); 
        if (lvl[pu] < lvl[pv]) swap(pu, pv), swap(u, v);
        par[pv] = pu;
        lvl[pu] += lvl[pv];
        // identifique os lados
        smaller_side -= min(sz(comps[pv][0]), sz(comps[pv][1]));
        smaller_side -= min(sz(comps[pu][0]), sz(comps[pu][1]));
        int p = 1 ^ qual_lado[u]^qual_lado[v];
        for (auto z : comps[pv][0]) comps[pu][p].pb(z), qual_lado[z] = p;
        for (auto z : comps[pv][1]) comps[pu][p^1].pb(z), qual_lado[z] = p^1;
        smaller_side += min(sz(comps[pu][0]), sz(comps[pu][1]));
        return 1;
    };
    bool ok = 1;
    while (q--) {
        int u, v; cin >> u >> v; --u, --v;
        if (ok) ok &= (unite(u, v));
        cout << (ok ? smaller_side : -1) << endl;
    }
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
