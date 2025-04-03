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
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb(v);
    }
    vector<int> ans;
    int tam = 1e18;
    for (int i = 0; i < n; ++i) {
        queue<int> q;
        vector<int> dist(n, inf), pai(n);
        dist[i] = 0;
        q.push(i);
        while (!q.empty()) {
            auto u = q.front(); q.pop();
            for (auto v : g[u]) {
                if (dist[v] == inf) dist[v] = 1 + dist[u], q.push(v), pai[v] = u;
                else if (v == i) {
                    if (ckmin(tam, dist[u] + 1)) {
                        ans = {i};
                        int cur = u;
                        while (cur != i) ans.pb(cur), cur = pai[cur];
                    }
                }
            }
        }
    }
    if (ans.empty()) cout << -1 << endl;
    else {
        cout << tam << endl;
        for (auto x : ans) cout << x + 1 << ' '; 
        cout << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
