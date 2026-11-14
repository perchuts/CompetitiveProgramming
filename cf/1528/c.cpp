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
    array<vector<vector<int>>, 2> g;
    for (int j = 0; j < 2; ++j) {
        g[j].resize(n);
        for (int i = 1; i < n; ++i) {
            int u; cin >> u; --u;
            g[j][u].pb(i);
        }
    }
    vector<int> in(n), out(n);
    int t = 0;
    auto pre = [&] (auto&& self, int u) -> void {
        in[u] = ++t;
        for (auto v : g[1][u]) self(self, v);
        out[u] = ++t;
    };
    pre(pre, 0);
    int ans = 0;
    set<ii> s;
    auto dfs = [&] (auto&& self, int u) -> void {
        int rem = -1, estou = 0;
        auto it = s.lower_bound({in[u], 0});
        if (it != begin(s)) {
            auto [val, w] = *prev(it);
            if (in[w] < in[u] and out[u] < out[w]) {
                rem = w;
                s.erase({in[w], w});
                s.insert({in[u], u});
                estou = 1;
            } 
        }
        bool ok = 1;
        if (rem == -1 and it != end(s)) {
            auto [val, w] = *it;
            if (in[u] < in[w] and out[w] < out[u]) ok = 0;
        }
        if (ok) s.insert({in[u], u}), estou = 1;
        ckmax(ans, sz(s));
        for (auto v : g[0][u]) {
            self(self, v);
        }
        if (rem != -1) s.insert({in[rem], rem});
        if (estou) s.erase({in[u], u});
    };
    dfs(dfs, 0);
    cout << ans << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
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
