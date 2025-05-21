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
    vector<int> c(m);
    for (auto& x : c) cin >> x;
    int N = n + m;
    vector<vector<ii>> g(N);
    for (int i = 0; i < m; ++i) {
        int k; cin >> k;
        for (int j = 0; j < k; ++j) {
            int x; cin >> x; --x;
            g[x].pb({n+i, c[i]});
            g[n+i].pb({x, 0});
        }
    }
    vector<int> dist(N, 1e18);
    priority_queue<ii, vector<ii>, greater<>> pq;
    pq.push({0, 0});
    dist[0] = 0;
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue;
        for (auto [v, w] : g[u]) {
            if (ckmin(dist[v], d + w)) pq.push({d+w, v});
        }
    }
    for (int i = 0; i < n; ++i) cout << dist[i] << ' ';
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
