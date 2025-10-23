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

struct dsu {
    int n, comps;
    vector<int> lvl, par;
    dsu(int n_) {
        lvl.resize(n_);
        par.resize(n_);
        n = comps = n_;
        iota(all(par), 0);
    }
    int findp(int u) {
        return par[u] = (par[u] == u ? u : findp(par[u]));
    }
    bool merge(int u, int v) {
        u = findp(u);
        v = findp(v);
        if (u == v) return false;
        if (lvl[u] < lvl[v]) swap(u, v);
        par[v] = u;
        if (lvl[u] == lvl[v]) lvl[u]++;
        comps--;
        return true;
    }
};

void solve() {
    int n, m, x; cin >> n >> m >> x;
    vector<iii> edg(m);
    for (auto& [w, u, v] : edg) cin >> u >> v >> w, --u, --v;
    sort(all(edg));
    map<ii, int> mp;
    for (int i = 0; i < m; ++i) {
        auto [u, v, w] = edg[i];
        mp[{u, v}] = mp[{v, u}] = i;
    }
    auto get = [&] (int z) {
        dsu grandao(m);
        auto unite = [&] (int i, int j) {
            dsu act(n);
            int tot = 0;
            for (int k = 0; k < m; ++k) {
                if (k == i or k == j) {
                    auto [w, u, v] = edg[k];
                    act.merge(u, v);
                    tot += w;
                }
            }
            for (auto [w, u, v] : edg) if (act.merge(u, v)) tot += w;
            if (tot <= z) grandao.merge(i, j);
        };
        for (int j = 1; j < m; ++j) unite(0, j);
        for (int i = 0; i < n; ++i) {
            auto [u1, v1, fodase] = edg[0];
            if (mp.count({u1, i}) and mp.count({v1, i})) unite(mp[{u1, i}], mp[{v1, i}]);
        }
        int tot = 1;
        for (int i = 0; i < grandao.comps; ++i) tot = (tot + tot) % mod;
        return tot;
    };
    cout << (get(x-1) - get(x) + mod) % mod << endl;
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
