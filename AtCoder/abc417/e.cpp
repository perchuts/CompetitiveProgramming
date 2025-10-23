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
    int n, m, x, y; cin >> n >> m >> x >> y;
    --x, --y;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    int cur = x;
    vector<int> mark(n); 
    vector<int> vis(n);
    while (cur != y) {
        mark[cur] = 1;
        for (int i = 0; i < n; ++i) vis[i] = 0;
        auto dfs = [&] (auto&& self, int u) -> void {
            vis[u] = true;
            for (auto v : g[u]) {
                if (vis[v] or mark[v]) continue;
                self(self, v);
            }
        };
        dfs(dfs, y);
        int sexo = n;
        for (auto v : g[cur]) {
            if (vis[v]) ckmin(sexo, v);
        }
        cout << cur+1 << ' ';
        cur = sexo;
    }
    cout << y+1 << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
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
