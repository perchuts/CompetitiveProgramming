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
    int n; cin >> n;
    vector<int> p(n), a(n);
    for (auto& x : p) cin >> x, --x;
    for (auto& x : a) cin >> x, --x;
    vector<int> vis(n, -1); vector<vector<int>> cyc;
    for (int i = 0; i < n; ++i) {
        if (vis[i] != -1) continue;
        cyc.pb({});
        int cur = i;
        while (vis[cur] == -1) vis[cur] = sz(cyc)-1, cyc.back().pb(cur), cur = p[cur];
    }
    vector<int> repr(n+1, inf);
    for (int i = 0; i < sz(cyc); ++i) ckmin(repr[sz(cyc[i])], cyc[i][0]);
    vector<int> ord;
    for (int i = 1; i <= n; ++i) if (repr[i] != inf) ord.pb(i);
    vector<vector<int>> g(sz(ord), vector<int>(sz(ord)));
    sort(all(ord), [&] (int x, int y) { return repr[x] < repr[y]; });
    for (int i = 0; i < sz(ord); ++i) for (int j = 0; j < sz(ord); ++j) g[i][j] = gcd(ord[i], ord[j]);
    vector<int> rot(sz(ord)), go(n+1);
    for (int i = 0; i < sz(ord); ++i) {
        int c = vis[repr[ord[i]]], best = -1, val = inf;
        for (int choice = 0; choice < sz(cyc[c]); ++choice) {
            bool ok = true;
            for (int j = 0; j < i; ++j) ok &= (rot[j] % g[i][j] == choice % g[i][j]);
            if (ok and ckmin(val, a[cyc[c][choice]])) best = choice;
        }
        assert(best != -1);
        rot[i] = go[ord[i]] = best;
    }
    vector<int> temp = a;
    for (auto c : cyc) {
        for (int i = 0; i < sz(c); ++i) a[c[i]] = temp[c[(i+go[sz(c)])%sz(c)]];
    }
    for (auto x : a) cout << x + 1 << ' ';
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
