#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
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

vector<int> solve(int n, vector<vector<int>> g, string s) {
    vector<int> subt(n), par(n), foi(n), color(n), bad(n);
    set<int> pode;
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        color[u] = (s[u] == 'B');
        subt[u] = (color[u] ^ 1);
        for (auto v : g[u]) {
            if (v == p) continue;
            par[v] = u;
            self(self, v, u);
            subt[u] += subt[v];
            bad[u] += (subt[v] % 2);
        }
        if (bad[u] == 0 and s[u] == 'W') pode.insert(u);
    };
    dfs(dfs, 0, 0);
    if (subt[0] % 2 == 0) return vector<int>();
    vector<int> ans;
    while (!pode.empty()) {
        auto u = *begin(pode); pode.erase(u);
        foi[u] = true;
        ans.pb(u);
        for (auto v : g[u]) {
            if (foi[v] or v == par[u]) continue;
            // agora sei que esse cara eh um filho meu; posso swapar a cor dele!
            color[v] ^= 1;
            if (color[v] == 0 and bad[v] == 0) pode.insert(v);
        }
        bad[par[u]] -= (subt[u] % 2);
        color[par[u]] ^= 1;
        if (!foi[par[u]] and bad[par[u]] == 0 and color[par[u]] == 0) pode.insert(par[u]);
    }
    return ans;
}

vector<int> brute(int n, vector<vector<int>> g, string s) {
    vector<int> p(n); iota(all(p), 0);
    do {
        string ss = s;
        bool ok = true;
        for (auto u : p) {
            if (ss[u] == 'B') {
                ok = false; break;
            }
            for (auto v : g[u]) ss[v] = (ss[v] == 'B' ? 'W' : 'B');
        }
        if (ok) return p;
    } while(next_permutation(all(p)));
    return vector<int>();
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    int n; cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    string s; cin >> s;
    auto ans = solve(n, g, s);
    if (ans.empty()) cout << -1 << endl;
    else {
        for (auto x : ans) cout << x + 1 << ' ';
        cout << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 5);
        vector<vector<int>> g(n);
        vector<ii> edg;
        for (int i = 1; i < n; ++i) {
            int j = rnd(0, i-1);
            edg.pb({j, i});
            g[i].pb(j), g[j].pb(i);
        }
        string s(n, 'B');
        for (auto& x : s) x = (rnd(0, 1) ? 'B' : 'W');
        int cnt = 0;
        for (auto& x : s) cnt ^= (x == 'W');
        auto my = solve(n, g, s);
        auto ans = brute(n, g, s);
        if (ans != my) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto [x, y] : edg) cout << x + 1 << ' ' << y + 1 << endl;
            cout << s << endl;
            cout << "Your output: ";
            if (my.empty()) cout << -1 << endl;
            else {
                for (auto x : my) cout << x + 1 << ' ';
                cout << endl;
            }
            cout << "Correct answer: ";
            if (ans.empty()) cout << -1 << endl;
            else {
                for (auto x : ans) cout << x + 1 << ' ';
                cout << endl;
            }
            exit(0);
        }
        //if (my != ans) {
        //    cout << "Wrong answer on test " << t << endl;
        //    cout << "Your output: " << my << endl;
        //    cout << "Answer: " << ans << endl;
        //    exit(0);
        //}
        //cout << "Accepted on test " << t++ << endl;
    }
#endif
}
