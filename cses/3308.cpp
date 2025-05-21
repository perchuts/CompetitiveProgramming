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
    vector<int> pode(1<<n);
    vector<vector<int>> adj(n, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        adj[u][v] = adj[v][u] = 1;
    }
    pode[0] = 1;
    for (int i = 1; i < (1 << n); ++i) {
        int cara = -1;
        for (int j = 0; j < n; ++j) {
            if (i >> j & 1) {
                if (cara == -1) pode[i] = pode[i - (1 << j)], cara = j;
                else pode[i] &= (adj[cara][j] ^ 1);
            }
        }
    }
    vector<int> dp(1<<n, n+1), tr(1<<n);
    dp[0] = 0;
    for (int i = 1; i < (1 << n); ++i) {
        for (int j = i; j >= (1+i)/2; j = (j-1)&i) {
            if (pode[j] and ckmin(dp[i], dp[i-j]+1)) tr[i] = j;
        }
    }
    vector<int> color(n);
    cout << dp.back() << endl;
    int cur = (1 << n) - 1, val = 1;
    while (cur) {
        int x = tr[cur];
        for (int j = 0; j < n; ++j) {
            if (x >> j & 1) color[j] = val;
        }
        val++;
        cur -= x;
    }
    for (auto x : color) cout << x << ' ';
    cout << endl;
    
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
