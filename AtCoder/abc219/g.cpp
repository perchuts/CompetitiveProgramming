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
    int n, m, q; cin >> n >> m >> q;
    const int X = 450;
    vector<vector<int>> g(n), big(n);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    for (int i = 0; i < n; ++i) {
        for (auto v : g[i]) if (sz(g[v]) > X) big[i].pb(v);
    }
    vector<ii> lst_s(n);
    for (int i = 0; i < n; ++i) lst_s[i] = {0, i};
    vector<ii> lst_b(n, make_pair(-inf, -inf));
    for (int i = 1; i <= q; ++i) {
        int u; cin >> u; --u;
        // quero descobrir a minha cor!
        ii last = lst_s[u];
        for (auto v : big[u]) ckmax(last, lst_b[v]);
        int cor = last.second;
        if (sz(g[u]) <= X) {
            for (auto v : g[u]) lst_s[v] = {i, cor};
        } else lst_b[u] = {i, cor};
    }
    for (int i = 0; i < n; ++i) {
        ii last = lst_s[i];
        for (auto v : big[i]) ckmax(last, lst_b[v]);
        cout << last.second+1 << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
