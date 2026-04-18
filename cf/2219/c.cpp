#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
#define pb push_back
#define int ll
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
//#define gato

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

double brute(int n, string s, vector<vector<int>> g) {
    vector<int> p(n); iota(begin(p), end(p), 0);
    vector<int> deg(n), good(n);
    for (int i = 0; i < n; ++i) deg[i] = sz(g[i]);
    for (int i = 0; i < n; ++i) {
        for (auto v : g[i]) {
            if (s[v] == '1') good[i]++;
        }
    }
    double ans = 1e18;
    do {
        auto cur = good;
        double val = 0;
        bool ok = 1;
        for (auto u : p) {
            if (s[u] == '0') {
                if (cur[u] == 0) { ok = 0; break; }
                val += double(deg[u])/cur[u];
                for (auto v : g[u]) cur[v]++;
            }
        }
        if (ok and ckmin(ans, val)) {
            //cout << "ans = " << ans << endl;
            //for (auto x : p) cout << x + 1 << " ";
            //cout << endl << endl;
        }
    } while(next_permutation(all(p)));
    return ans;
}

//void solve(int n, string s, vector<vector<int>> g) {
void solve() {
    int n; cin >> n;
    string s; cin >> s;
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    //brute(n, s, g);
    vector<int> pai(n);
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        for (auto v : g[u]) {
            if (v == p) continue;
            pai[v] = u;
            self(self, v, u);
        }
    };
    dfs(dfs, 0, 0);
    vector<int> deg(n), good(n);
    for (int i = 0; i < n; ++i) deg[i] = sz(g[i]);
    for (int i = 0; i < n; ++i) {
        for (auto v : g[i]) {
            if (s[v] == '1') good[i]++;
        }
    }
    auto cmp = [&](int a, int b) { 
        if (deg[a] * (good[b] * (good[b]+1)) == deg[b] * (good[a] * (good[a]+1))) return a < b;
        return deg[a] * (good[b] * (good[b]+1)) < deg[b] * (good[a] * (good[a]+1));
    };
    set<int, decltype(cmp)> caras(cmp);
    for (int i = 0; i < n; ++i) {
        if (s[i] == '0' and good[i]) caras.insert(i);
    }
    double ans = 0;
    vector<int> foi(n);
    while (!caras.empty()) {
        int u = *begin(caras); caras.erase(begin(caras));
        foi[u] = true;
        //cout << "matando " << u << endl; cout << flush;
        ans += (double)deg[u]/good[u];
        for (auto v : g[u]) {
            if (s[v] == '0' and !foi[v]) {
                if (good[v] == 0) good[v]++, caras.insert(v);
                else {
                    caras.erase(v);
                    good[v]++;
                    caras.insert(v);
                }
            }
        }
    }
    //assert(ans == brute(n, s, g));
    cout << fixed << setprecision(10) << ans << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int n = rnd(3, 7);
        vector<vector<int>> g(n);
        cout << n << endl;
        for (int i = 1; i < n; ++i) {
            int x = rnd(0, i-1);
            cout << i+1 << " " << x+1 << endl;
            g[x].pb(i), g[i].pb(x);
        }
        string s;
        bool ok = 0;
        for (int i = 0; i < n; ++i) {
            if (rnd(0, 1)) s += '0';
            else s += '1', ok = 1;
        }
        if (ok == 0) continue;
        cout << s << endl;
        cout << "indo!" << endl;
        solve(n, s, g);
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
