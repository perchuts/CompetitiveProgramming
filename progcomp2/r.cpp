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
    int n, q; cin >> n >> q;
    map<ii, vector<int>> ops;
    for (int i = 1; i <= q; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        if (u < v) swap(u, v);
        ops[{u, v+n}].pb(i);
        ops[{u+n, v}].pb(i);
    }
    vector<vector<ii>> seg(4*q+10);
    auto add = [&] (auto&& self, int i, int l, int r, int x, int y, ii edg) {
        if (r < x or y < l) return;
        if (x <= l && r <= y) {
            seg[i].pb(edg);
            return;
        }
        int md = (l + r) / 2;
        self(self, 2*i, l, md, x, y, edg);
        self(self, 2*i+1, md+1, r, x, y, edg);
    };
    for (auto [edg, pos] : ops) {
        if (sz(pos)&1) pos.pb(q+1);
        for (int i = 1; i < sz(pos); i += 2) {
            add(add, 1, 1, q+1, pos[i-1], pos[i]-1, edg); 
        }
    }
    vector<int> p(2*n), lvl(2*n, 1);
    iota(all(p), 0);
    auto findp = [&] (auto&& self, int u) -> int {
        return (p[u] == u ? u : self(self, p[u]));
    };
    stack<iii> merges;
    int bad = 0;
    auto unite = [&] (int u, int v) {
        u = findp(findp, u), v = findp(findp, v);
        if (u == v) return false;
        if (lvl[u] < lvl[v]) swap(u, v);
        merges.push({u, v, bad});	
        lvl[u] += lvl[v];
        p[v] = u;
        int irmao = (v < n ? v + n : v - n);
        bad += (findp(findp, irmao) == u);
        return true;
    };
    auto undo = [&] () {
        auto [u, v, bb] = merges.top();
        bad = bb;
        merges.pop();
        p[v] = v, lvl[u] -= lvl[v];
    };
    int cur = n;
    auto dfs = [&] (auto&& self, int i, int l, int r) -> void{
        int bef = sz(merges);
        for (auto [x, y] : seg[i]) {
            if (unite(x, y)) cur--;	
        }
        int tam = sz(merges);
        if (l == r) {
            if (l != q+1) cout << (bad == 0 ? "YES" : "NO") << endl;
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md);
        while (sz(merges) != tam) undo(), cur++;
        self(self, 2*i+1, md+1, r);
        while (sz(merges) != bef) undo(), cur++;
    };
    dfs(dfs, 1, 1, q+1);
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

