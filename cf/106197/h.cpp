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
    vector<int> deg(n), bad(n);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        deg[u]++;
        g[v].pb(u);
    }
    queue<int> q;
    vector<int> vis(n);
    vis[n-1] = 1;
    q.push(n-1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v : g[u]) {
            if (vis[v]) continue;
            bad[v]++;
            if (2 * bad[v] > deg[v]) {
                vis[v] = 1;
                q.push(v);
            }
        }
    }
    if (vis[0]) {
        cout << -1 << endl;
        return;
    }
    vector<ii> ans;
    for (int i = 0; i < n; ++i) {
        if (!vis[i]) continue;
        for (auto j : g[i]) {
            if (!vis[j]) ans.pb({j+1, i+1});
        }
    }
    cout << sz(ans) << endl;
    for (auto [u, v] : ans) cout << u << " " << v << endl;
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
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
