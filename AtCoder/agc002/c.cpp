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

void solve() {
    int n, l; cin >> n >> l;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<int> ops, par(n), lvl(n), le(n), ri(n), tam(n);
    for (int i = 0; i < n; ++i) par[i] = le[i] = ri[i] = i, tam[i] = a[i];
    auto findp = [&] (auto&& self, int u) -> int {
        return par[u] = (par[u] == u ? u : self(self, par[u]));
    };
    auto merge = [&] (int u, int v) {
        u = findp(findp, u), v = findp(findp, v);
        if (lvl[u] < lvl[v]) swap(u, v);
        par[v] = u;
        lvl[u] += (lvl[u] == lvl[v]);
        ckmin(le[u], le[v]);
        ckmax(ri[u], ri[v]);
        tam[u] += tam[v];
        return u;
    };
    set<ii> mt;
    for (int i = 0; i < n-1; ++i) mt.insert({a[i]+a[i+1], i});
    while (!mt.empty()) {
        auto [val, knot] = *prev(end(mt));
        if (val < l) {
            cout << "Impossible" << endl;
            exit(0);
        }
        int pl = findp(findp, knot);
        int pr = findp(findp, knot+1);
        if (le[pl]) {
            int other = findp(findp, le[pl]-1);
            mt.erase({tam[other]+tam[pl], le[pl]-1});
        } 
        if (ri[pr] != n-1) {
            int other = findp(findp, ri[pr]+1);
            mt.erase({tam[other]+tam[pr], ri[pr]});
        }
        mt.erase({val, knot});
        int eu = merge(knot, knot+1);
        if (le[pl]) {
            int other = findp(findp, le[pl]-1);
            mt.insert({tam[other]+tam[eu], le[pl]-1});
        } 
        if (ri[pr] != n-1) {
            int other = findp(findp, ri[pr]+1);
            mt.insert({tam[other]+tam[eu], ri[pr]});
        }
        ops.pb(knot);
    }
    reverse(all(ops));
    cout << "Possible" << endl;
    for (auto x : ops) cout << x+1 << endl;
    cout << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
