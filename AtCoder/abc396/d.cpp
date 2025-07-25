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
    vector<vector<int>> adj(n, vector<int>(n, -1));
    for (int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        --u, --v;
        adj[u][v] = adj[v][u] = w;
    }
    if (n == 2) {
        cout << adj[0][1] << endl;
        exit(0);
    }
    vector<int> p(n-2); iota(all(p), 1);
    int ans = 2e18;
    do {
        int cur = 0, vert = 0;
        for (int i = 0; i < n-2; ++i) {
            if (adj[vert][n-1] != -1) ckmin(ans, cur ^ adj[vert][n-1]);
            if (adj[vert][p[i]] == -1) break;
            cur ^= adj[vert][p[i]];
            vert = p[i];
        }
        if (vert == p.back() and adj[vert][n-1] != -1) ckmin(ans, cur ^ adj[vert][n-1]);
    } while (next_permutation(all(p)));
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
