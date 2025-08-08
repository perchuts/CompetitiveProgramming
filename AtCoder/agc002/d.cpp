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
    int n, m; cin >> n >> m;
    vector<ii> edges(m);
    for (auto& [u, v] : edges) cin >> u >> v, --u, --v;
    int q; cin >> q;
    vector<int> ans(q, m);
    vector<iii> query(q);
    for (auto& [x, y, z] : query) cin >> x >> y >> z, --x, --y;
    vector<ii> ranges(q, pair(0, m-1));
    while (true) {
        vector<vector<int>> ask(m);
        int tem = 0;
        for (int i = 0; i < q; ++i) {
            auto [l, r] = ranges[i];
            if (l <= r) tem = 1, ask[l + (r-l+1)/2].push_back(i);
        }
        //for (auto [l, r] : ranges) cout << l << ' ' << r << endl;
        //cout << "###" << endl;
        if (!tem) break;
        vector<int> par(n), lvl(n, 1); iota(all(par), 0);
        auto findp = [&] (auto&& self, int u) -> int {
            return par[u] = (par[u] == u ? u : self(self, par[u]));
        };
        auto merge = [&] (int u, int v) {
            u = findp(findp, u), v = findp(findp, v);
            if (u == v) return;
            if (lvl[u] < lvl[v]) swap(u, v);
            par[v] = u;
            lvl[u] += lvl[v];
        };
        for (int i = 0; i < m; ++i) { 
            merge(edges[i].first, edges[i].second);
            //cout << "merging " << edges[i].first << ' ' << edges[i].second << endl;
            for (auto idq : ask[i]) {
                auto [u, v, z] = query[idq];
                auto& [l, r] = ranges[idq];
                int comp_u = findp(findp, u);
                int comp_v = findp(findp, v);
                int tam = lvl[comp_u] + (comp_u != comp_v ? lvl[comp_v] : 0);
                //if (idq == 0) cout << tam << ' ' << comp_u << ' ' << comp_v << endl;
                if (tam >= z) {
                    ans[idq] = i;
                    r = i-1;
                } else {
                    l = i+1;
                }
            }
        }
    }
    for (auto x : ans) cout << x + 1 << endl;
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
