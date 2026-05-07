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
    int n; cin >> n;
    vector<int> a(n), par(n), lvl(n);
    for (auto& x : a) cin >> x; 
    iota(all(par), 0);
    auto findp = [&] (auto&& self, int u) -> int {
        return par[u] = (par[u] == u ? u : self(self, par[u]));
    };
    auto unite = [&] (int u, int v) {
        u = findp(findp, u), v = findp(findp, v);
        if (u == v) return;
        if (lvl[u] < lvl[v]) swap(u, v);
        par[v] = u;
        lvl[u] += (lvl[u] == lvl[v]);
    };
    vector<vector<int>> g(n);
    string s; cin >> s;
    for (int i = 0; i < n-1; ++i) {
        if (s[i] == '=') unite(i, i+1);
    }
    vector<int> deg(n);
    for (int i = 0; i < n-1; ++i) {
        if (s[i] == '>') {
            g[findp(findp, i+1)].pb(findp(findp, i));
            deg[findp(findp, i)]++;
        } else if (s[i] == '<') {
            g[findp(findp, i)].pb(findp(findp, i+1));
            deg[findp(findp, i+1)]++;
        }
    }
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (findp(findp, i) == i and deg[i] == 0) q.push(i);
    }
    vector<int> ans(n, 1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v : g[u]) {
            ckmax(ans[v], 1 + ans[u]);
            deg[v]--;
            if (deg[v] == 0) q.push(v);
        }
    }
    for (int i = 0; i < n; ++i) ans[i] = ans[findp(findp, i)];
    int val = 0;
    for (int i = 0; i < n; ++i) {
        val += a[i] * ans[i];
    }
    cout << val << endl;
    for (auto x : ans) cout << x << " ";
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
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
