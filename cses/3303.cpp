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
    int n, m, k; cin >> n >> m >> k;
    vector<int> sp(n), sexo(k);
    for (auto& x : sexo) cin >> x, --x, sp[x] = 1;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        --u, --v; g[u].pb(v); g[v].pb(u);
    }
    vector<vector<ii>> dist(n, vector<ii>(2, pair(inf, -1)));
    queue<iii> q;
    for (auto x : sexo) dist[x][0] = {0, x}, q.push({0, x, x});
    while (!q.empty()) {
        auto [d, u, w] = q.front(); q.pop();
        d++;
        for (auto v : g[u]) {
            if (dist[v][0].first == inf) {
                dist[v][0] = {d, w};
                q.push({d, v, w});
            } else if (dist[v][1].first == inf and dist[v][0].second != w) {
                dist[v][1] = {d, w};
                q.push({d, v, w});
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        int ans = dist[i][sp[i]].first;
        cout << (ans == inf ? -1 : ans) << ' ';
    }
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
