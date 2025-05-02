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
    int n, u, v; cin >> n >> u >> v; --u, --v;
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int x, y; cin >> x >> y;
        --x, --y;
        g[x].pb(y), g[y].pb(x);
    }
    vector<int> du, dv;
    auto get = [&] (int src) {
        vector<int> dist(n, inf);
        queue<int> q;
        q.push(src);
        dist[src] = 0;
        while (!q.empty()) {
            int x = q.front(); q.pop();
            for (auto y : g[x]) {
                if (ckmin(dist[y], dist[x] + 1)) q.push(y);
            }
        }
        return dist;
    };
    du = get(u), dv = get(v);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (sz(g[i]) == 1 and du[i] < dv[i]) ckmax(ans, dv[i] - 1);
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
