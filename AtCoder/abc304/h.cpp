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

void solve(){
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n), gr(n);
    vector<int> deg(n), ans(n), l(n), r(n), dp(n);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), gr[v].pb(u), deg[u]++;
    }
    for (int i = 0; i < n; ++i) cin >> l[i] >> r[i];
    queue<int> q;
    for (int i = 0; i < n; ++i) if (!deg[i]) q.push(i);
    while (!q.empty()) {
        auto u = q.front(); q.pop();
        dp[u] = r[u];
        for (auto v : g[u]) ckmin(dp[u], dp[v]);
        for (auto v : gr[u]) {
            deg[v]--;
            if (deg[v] == 0) q.push(v);
        }
    }
    priority_queue<ii> pq;
    vector<vector<int>> add(n+2);
    for (int i = 0; i < n; ++i) deg[i] = sz(gr[i]);
    for (int i = 0; i < n; ++i) if (deg[i] == 0) add[l[i]].pb(i);
    for (int tt = 1; tt <= n; ++tt) {
        for (auto u : add[tt]) pq.push({-dp[u], u});
        if (pq.empty()) {
            cout << "No" << endl;
            exit(0);
        }
        auto [t, u] = pq.top(); pq.pop(); t *= -1;
        ans[u] = tt;
        if (r[u] < tt) {
            cout << "No" << endl;
            exit(0);
        }
        for (auto v : g[u]) {
            deg[v]--;
            if (deg[v] == 0) add[max(l[v], tt+1)].pb(v);
        }
    }
    cout << "Yes" << endl;
    for (auto x : ans) cout << x << ' ';
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
