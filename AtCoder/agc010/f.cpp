#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
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

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

vector<int> solve(int n, vector<int> a, vector<vector<int>> g) { 
    vector<int> ans, win(n);
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        win[u] = false;
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
            if (a[u]-1 >= a[v] and win[v] == false) win[u] = true;
        }
    };
    for (int i = 0; i < n; ++i) {
        dfs(dfs, i, i);
        if (win[i]) ans.pb(i);
    }
    return ans;
}

vector<int> brute(int n, vector<int> a, vector<vector<int>> g) {
    map<pair<int, vector<int>>, bool> win;
    auto dfs = [&] (auto&& self, int u, vector<int> cur) -> bool {
        if (win.count({u, cur})) return win[{u, cur}];
        if (cur[u] == 0) return win[{u, cur}] = false;
        cur[u]--;
        for (auto v : g[u]) {
            if (!self(self, v, cur)) { cur[u]++; return win[{u, cur}] = true; }
        }
        cur[u]++;
        return win[{u, cur}] = false;
    };
    vector<int> ans;
    for (int r = 0; r < n; ++r) {
        if (dfs(dfs, r, a)) ans.pb(r);
    }
    return ans;
}



int32_t main() {_
#ifndef gato
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    auto ans = solve(n, a, g);
    for (auto x : ans) cout << x+1 << " ";
    cout << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 15);
        vector<int> a(n);
        for (auto& x : a) x = rnd(0, 4);
        vector<ii> edg;
        vector<vector<int>> g(n);
        for (int i = 1; i < n; ++i) {
            int j = rnd(0, i-1);
            edg.pb({i, j});
            g[i].pb(j), g[j].pb(i);
        }
        auto my = solve(n, a, g); 
        auto ans = brute(n, a, g);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : a)  cout << x << " ";
            cout << endl;
            for (auto [x, y] : edg) cout << x+1 << " " << y+1 << endl;
            cout << "Solve: ";
            for (auto x : my) cout << x+1 << " ";
            cout << endl;
            cout << "Brute: ";
            for (auto x : ans) cout << x+1 << " ";
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
