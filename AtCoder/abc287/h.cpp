#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("bmi,bmi2,popcnt,lzcnt")
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

void solve(){
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n), gr(n);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), gr[v].pb(u);
    }
    vector<bitset<2000>> alcanca(n), alcancado(n);
    for (int i = 0; i < n; ++i) alcanca[i][i] = alcancado[i][i] = 1;
    int q; cin >> q;
    vector<int> ans(q, -1);
    vector<ii> qu(q);
    for (auto& [x, y] : qu) cin >> x >> y, --x, --y;
    for (int u = 0; u < n; ++u) {
        for (auto v : g[u]) {
            if (v > u or alcanca[u][v]) continue;
            alcanca[u] |= alcanca[v];
            for (int i = 0; i < n; ++i) {
                if (u != i and alcancado[u][i]) alcanca[i] |= alcanca[u];
            }
            alcancado[v] |= alcancado[u];
            for (int i = 0; i < n; ++i) {
                if (v != i and alcanca[v][i]) alcancado[i] |= alcancado[v];
            }
        }
        for (auto v : gr[u]) {
            if (v > u or alcanca[v][u]) continue;
            alcanca[v] |= alcanca[u];
            for (int i = 0; i < n; ++i) {
                if (v != i and alcancado[v][i]) alcanca[i] |= alcanca[v];
            }
            alcancado[u] |= alcancado[v];
            for (int i = 0; i < n; ++i) {
                if (u != i and alcanca[u][i]) alcancado[i] |= alcancado[u];
            }
        }
        for (int i = 0; i < q; ++i) {
            if (ans[i] == -1 and alcanca[qu[i].first][qu[i].second]) ans[i] = u+1;
        }
    }
    for (auto x : ans) cout << x << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
