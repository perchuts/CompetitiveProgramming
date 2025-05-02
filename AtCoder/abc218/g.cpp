#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
	using ord_set = tree<T, null_type, less<T>, rb_tree_tag,
	tree_order_statistics_node_update>;
	
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

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
    int n; cin >> n;
    vector<int> a(n);
    for (auto & x : a) cin >> x;
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    ord_set<ii> s;
    auto get_median = [&] () {
        if (sz(s) % 2) return s.find_by_order(sz(s)/2)->first;
        int a = s.find_by_order(sz(s)/2)->first, b = s.find_by_order(sz(s)/2-1)->first;
        return (a+b)/2;
    };
    vector<int> dp1(n), dp2(n);
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        s.insert({a[u], u});
        int eu = get_median(), leaf = 1;
        for (auto v : g[u]) {
            if (v == p) continue;
            leaf = 0;
            self(self, v, u);
        }
        if (leaf) dp1[u] = dp2[u] = eu;
        else {
            dp2[u] = 1e18;
            for (auto v : g[u]) {
                if (v == p) continue;
                ckmax(dp1[u], dp2[v]);
                ckmin(dp2[u], dp1[v]);
            }
        }
        s.erase({a[u], u});
    };
    dfs(dfs, 0, 0);
    cout << dp1[0] << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
