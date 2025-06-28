#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
    int n, l, r; cin >> n >> l >> r;
    auto query = [&] (int i, int j) {
        cout << "? ";
        cout << i << ' ' << j << endl;
        int x; cin >> x;
        return x;
    };
    vector<vector<int>> g((1<<n)+1);
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; ((j+1)<<i) <= (1 << n); ++j) {
            g[j<<i].pb((j+1)<<i);
            g[((j+1)<<i)].pb(j<<i);
        }
    }
    vector<int> dist((1<<n)+1, inf), par = dist;
    queue<int> q;
    q.push(l); dist[l] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v : g[u]) {
            if (dist[v] == inf) dist[v] = dist[u] + 1, q.push(v), par[v] = u;
        }
    }
    vector<int> ops;
    int cur = r+1;
    while (cur != l) ops.pb(cur), cur = par[cur];
    ops.pb(l);
    reverse(all(ops));
    int ans = 0;
    for (int i = 1; i < sz(ops); ++i) {
        int d = abs(ops[i-1] - ops[i]);
        int j = 0;
        while ((1 << j) < d) j++;
        int x = query(j, min(ops[i], ops[i-1])>>j);
        if (ops[i-1] < ops[i]) ans = (ans + x) % 100;
        else ans = (ans + 100 - x) % 100;
    }
    cout << "! " << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
