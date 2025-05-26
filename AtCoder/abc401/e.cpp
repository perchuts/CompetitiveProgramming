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
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    vector<int> fora(n), dentro(n);
    int lim = 0, ans = 0, qt = 0;
    auto add = [&] (auto&& self, int u) -> void {
        if (fora[u]) ans--;
        dentro[u] = 1;
        qt++;
        for (auto v : g[u]) {
            if (fora[v] or dentro[v]) continue;
            if (v <= lim) self(self, v);
            else if (fora[v] == 0) fora[v] = 1, ans++;
        }
    };
    add(add, 0);
    cout << ans << endl;
    for (int i = 1; i < n; ++i) {
        lim++;
        for (auto v : g[i]) {
            if (dentro[v]) {
                add(add, i);
                break;
            }
        }
        if (qt == i+1) cout << ans << endl;
        else cout << -1 << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
