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
    vector<vector<int>> g(n);
    map<ii, int> mp;
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        mp[{u, v}] = mp[{v, u}] = 1;
        g[u].pb(v), g[v].pb(u);
    }
    string s; cin >> s;
    vector<int> path, deg(n), vis(n);
    int flag = 0;
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        vis[u] = 1;
        for (auto v : g[u]) {
            if (vis[v]) continue;
            path.pb(v);
            deg[v] ^= 1;
            self(self, v, u);
            path.pb(u);
            deg[u] ^= 1;
        }
        if (s[u] != char('0'+deg[u])) {
            if (u == p) flag = 1, deg[u] ^= 1;
            else path.pb(p), path.pb(u), deg[u] ^= 1, deg[p] ^= 1;
        }
    };
    dfs(dfs, 0, 0);
    if (flag) path.insert(begin(path), 0);
    for (int i = 0; i < sz(path)-1; ++i) {
        assert(mp.count({path[i], path[i+1]}));
    }
    for (auto x : path) deg[x] ^= 1;
    for (auto  x : deg) assert(x == 0);
    assert(4 * n >= sz(path));
    cout << sz(path) << endl;
    for (auto x : path) cout << x + 1 << ' ';
    cout << endl;
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
