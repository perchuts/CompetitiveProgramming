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

void solve(){
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n), t(n), nt(n);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb(v);
        g[v].pb(u);
    }
    vector<int> dist(n, inf), par(n);
    dist[n-1] = 0;
    queue<int> q;
    q.push(n-1);
    while (!q.empty()) {
        auto u = q.front(); q.pop();
        for (auto v : g[u]) {
            if (dist[v] != inf) {
                if (par[u] != v) nt[u].pb(v);
                continue;
            }
            t[v].pb(u), t[u].pb(v), par[v] = u;
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
    // f[u] = menor numero de arestas pra fugir dessa subarvore descendo e ir pra raiz dnv
    vector<int> f(n), tin(n), tout(n);
    int T = 0;
    auto pre = [&] (auto&& self, int u, int p) -> void {
        tin[u] = ++T;
        for (auto v : t[u]) if (v != p) self(self, v, u);
        tout[u] = T;
    };
    pre(pre, n-1, n-1);
    vector<set<ii>> sexo(n), sexo2(n);
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        for (auto v : t[u]) {
            if (v == p) continue;
            self(self, v, u);
            if (sz(sexo[v]) > sz(sexo[u])) swap(sexo[u], sexo[v]), swap(sexo2[u], sexo2[v]);
        }
        for (auto v : t[u]) {
            if (v == p) continue;
            for (auto x : sexo[v]) sexo[u].insert(x);
            for (auto x : sexo2[v]) sexo2[u].insert(x);
        }
        while (!sexo2[u].empty()) {
            auto it = sexo2[u].lower_bound(make_pair(tin[u], -inf));
            if (it == end(sexo2[u]) or it->first > tout[u]) break;
            sexo[u].erase({it->second, it->first});
            sexo2[u].erase(it);
        }
        for (auto v : nt[u]) {
            if (tin[v] < tin[u] or tout[u] < tin[v]) {
                int x = dist[u] + dist[v] + 1;
                sexo[u].insert({x, tin[v]});
                sexo2[u].insert({tin[v], x});
            }
        }
        if (sexo[u].empty()) f[u] = inf;
        else f[u] = begin(sexo[u])->first - dist[u];
    };
    dfs(dfs, n-1, n-1);
    vector<int> dp(n, inf);
    priority_queue<ii, vector<ii>, greater<>> pq;
    dp.back() = f.back() = 0;
    pq.push({0, n-1});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dp[u]) continue;
        ckmax(dp[u], f[u]);
        for (auto v : g[u]) if (ckmin(dp[v], dp[u]+1)) pq.push({dp[v], v});
    }
    cout << (dp[0] == inf ? -1 : dp[0]) << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
