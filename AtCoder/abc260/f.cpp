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
    int s, t, m; cin >> s >> t >> m;
    vector<vector<int>> g(s);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v-s);
    }
    vector<vector<int>> mark(t, vector<int>(t, -1));
    for (int u = 0; u < s; ++u) {
        for (int i = 0; i < sz(g[u]); ++i) {
            for (int j = i+1; j < sz(g[u]); ++j) {
                int a = g[u][i], b = g[u][j];
                if (a < b) swap(a, b);
                if (mark[a][b] != -1) {
                    cout << u+1 << ' ' << mark[a][b]+1 << ' ' << a+1+s << ' ' << b+1+s << endl;
                    exit(0);
                }
                mark[a][b] = u;
            }
        }
    }
    cout << -1 << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
