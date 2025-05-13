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
    vector<vector<ii>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb({v, i});
    }
    vector<int> dist(n); 
    vector<ii> prox(n);
    auto go = [&] (int block) {
        for (int i = 1; i < n; ++i) dist[i] = inf;
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto [v, id] : g[u]) {
                if (id == block) continue;
                if (ckmin(dist[v], dist[u] + 1)) q.push(v), prox[v] = {u, id};
            }
        }
        return (dist[n-1] == inf ? -1 : dist[n-1]);
    };
    int ans = go(-1);
    if (ans == -1) {
        for (int i = 0; i < m; ++i) cout << -1 << endl;
        exit(0);
    }
    vector<int> mark(m);
    int cur = n-1;
    while (cur) mark[prox[cur].second] = true, cur = prox[cur].first;
    for (int i = 0; i < m; ++i) {
        if (!mark[i]) cout << ans << endl;
        else cout << go(i) << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
