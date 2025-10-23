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
    vector<vector<int>> par(n+1, vector<int>(20));
    vector<vector<ii>> g(n+1);
    vector<int> lvl(n+1), w(n+1);
    for (int i = 0; i < n-1; ++i) {
        int u, v, w; cin >> u >> v; 
        g[u].pb({v, w}), g[v].pb({u, w});
    }
    w[0] = 1;
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        lvl[u] = 1 + lvl[p];
        par[u][0] = p;
        for (int i = 1; i < 20; ++i) par[u][i] = par[par[u][i-1]][i-1];
        for (auto [v, we] : g[u]) {
            if (v == p) continue;
            w[v] = w[u] * we % mod;
            self(self, v, u);
        }
    };
    dfs(dfs, 1, 0);
    while (q--) {

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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
