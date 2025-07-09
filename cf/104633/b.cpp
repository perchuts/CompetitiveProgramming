#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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

int dp[10050][20000];

void solve() {
    int n, c; cin >> n >> c;
    vector<vector<ii>> g(n);
    vector<int> ord, mx(n), id(n), dp1(n), dp2(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v, w; cin >> u >> v >> w;
        --u, --v;
        g[u].pb({v, w});
        g[v].pb({u, w});
        ckmax(mx[u], w), ckmax(mx[v], w);
        ord.pb(w);
    }
    auto dfs1 = [&] (auto&& self, int u, int p) -> void {
        for (auto [v, w] : g[u]) {
            if (v == p) continue;
            self(self, v, u);
            ckmax(dp1[u], dp1[v] + 1);
        }
    };
    dfs1(dfs1, 0, 0);
    for (int i = 0; i < n; ++i) sort(all(g[i]), [&] (auto x, auto y) { return dp1[x.first] > dp1[y.first]; });
    int root = 0, h = dp1[0];
    auto dfs2 = [&] (auto&& self, int u, int p) -> void {
        if (u != p) {
            assert(g[u][0].first == p);
            dp2[u] = dp2[p] + 1;
            for (int i = 1; i < min(3, sz(g[p])); ++i) {
                if (g[p][i].first != u) ckmax(dp2[u], dp1[g[p][i].first] + 2);
            }
            if (ckmin(h, max(dp2[u], dp1[u]))) root = u;
        }
        for (auto [v, w] : g[u]) {
            if (v == p) continue;
            self(self, v, u);
        }
    };
    dfs2(dfs2, 0, 0); 
    sort(all(ord));
    vector<int> placar(n);
    int cur = 0;
    auto go = [&] (auto&& self, int u, int p) -> void {
        assert(cur < 10050);
        id[u] = cur++;
        placar[u] = sz(g[u]) * c;
        if (sz(g[u]) == 1) placar[u] = 0;
        for (int i = 0; i < n-1; ++i) {
            if (ord[i] < mx[u]) dp[id[u]][i] = inf;
            else dp[id[u]][i] = 0;
        }
        for (auto [v, w] : g[u]) {
            if (v == p) continue;
            self(self, v, u);
            int opt_outro = placar[v];
            for (int i = 0; i < n-1; ++i) {
                if (ord[i] >= mx[v]) ckmin(opt_outro, dp[id[v]][i] + ord[i] - w);
                if (ord[i] < mx[u]) continue;
                dp[id[u]][i] += min(dp[id[v]][i], placar[v]) + ord[i] - w;
            }
            placar[u] += opt_outro;
        }
        cur--;
    };
    go(go, root, root);
    int ans = placar[root];
    for (int i = 0; i < n-1; ++i) ckmin(ans, dp[id[root]][i]);
    cout << ans << endl;
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
