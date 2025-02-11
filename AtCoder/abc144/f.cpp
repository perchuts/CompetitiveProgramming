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
    vector<int> deg(n);
    vector<ii> edg(m);
    map<ii, int> naopode;
    for (auto& [u, v] : edg) {
        cin >> u >> v;
        --u, --v;
        gr[v].pb(u);
        g[u].pb(v);
        deg[u]++;
    }
    auto solve = [&] (int uu, int vv) {
        vector<int> dg = deg;
        queue<int> q;
        q.push(n-1);
        vector<double> dp(n);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto v : g[u]) {
                if (u == uu and v == vv) continue;
                dp[u] += dp[v] + 1;
            }
            if (u == uu) dp[u] /= (sz(g[u])-1);
            else if (u != n-1) dp[u] /= sz(g[u]);
            for (auto v : gr[u]) {
                dg[v]--;
                if (dg[v] == 0) q.push(v);
            }
        }
        return dp;
    };
    auto dp_can = solve(n, n);
    double ans = dp_can[0];
    for (int i = 0; i < n-1; ++i) {
        if (sz(g[i]) > 1) {
            double mx = 0;
            int id = 0;
            for (auto j : g[i]) if (ckmax(mx, dp_can[j])) id = j;
            ckmin(ans, solve(i, id)[0]);
        }
    }
    cout << fixed << setprecision(10) << ans << endl;

}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
