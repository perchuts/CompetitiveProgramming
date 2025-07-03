#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
//#define sz(x) (int) x.size()
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

struct dsu {
    int n;
    vector<int> sz, id;
    dsu(int _n = 0) : n(_n), sz(n, 1), id(n) {
        iota(id.begin(), id.end(), 0);
    }
    int find(int i) {
        if (i == id[i]) return i;
        return id[i] = find(id[i]);
    }
    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        sz[a] += sz[b];
        id[b] = a;
        return true;
    }
};

void solve(){
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int& i : a) cin >> i;
    vector<int> ord(n); iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&] (int i, int j) { return a[i] < a[j]; });

    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> ans(n);

    dsu d(n);
    for (int l = 0, r = 0; l < n; l = r) {
        while (r < n && a[ord[l]] == a[ord[r]]) r++;
        for (int i = l; i < r; i++) {
            int u = ord[i];
            for (int v : g[u]) if (a[v] <= a[u]) d.unite(u, v);
        }
        for (int i = l; i < r; i++) {
            int u = ord[i];
            ans[u] = d.sz[d.find(u)];
        }
    }

    for (int i = 0; i < n; i++) cout << ans[i] << "\n";
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
