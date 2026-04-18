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
    int n, m; cin >> n >> m;
    vector<vector<ii>> g(n);
    for (int i = 0; i < m; ++i) {
        int a, b, w; cin >> a >> b >> w;
        --a, --b;
        g[a].pb({b, w});
        g[b].pb({a, w});
    }
    // nenhum cara pode ser o zero -> 0 eh a resposta
    // exatamente um cara pode ser o zero -> o que falta eh a resposta
    // mais de um cara pode ser o zero -> -1 eh a resposta
    vector<int> vis(n), w(n);
    auto dfs = [&] (auto&& self, int u) -> void {
        vis[u] = 1;
        for (auto [v, x] : g[u]) {
            if (vis[v]) continue;
            w[v] = w[u] ^ x;
            self(self, v);
        }
    };
    dfs(dfs, 0);
    int ans = 0;
    for (auto x : w) ans ^= x;
    int penis = 0, cand = -1;
    for (int i = 1; i <= n; ++i) penis ^= i;
    vector<array<int, 2>> trie = {{0, 0}};
    int h = 1;
    for (int i = 0; i < n; ++i) {
        int cur = 0;
        for (int j = 20; ~j; --j) {
            int bit = (w[i] >> j & 1);
            if (trie[cur][bit] == 0) trie[cur][bit] = h++, trie.pb({0, 0});
            cur = trie[cur][bit];
        }
    }
    for (int i = 0; i <= n; ++i) {
        int cur = 0;
        bool ok = true;
        for (int j = 20; ~j; --j) {
            int b1 = (i >> j & 1);
            int b2 = (n >> j & 1);
            if (b2 == 0) {
                if (trie[cur][b1^1]) {
                    ok = false;
                    break;
                }
                if (trie[cur][b1] == 0) break;
                cur = trie[cur][b1];
            } else {
                if (trie[cur][b1^1] == 0) break;
                cur = trie[cur][b1^1];
            }
        }
        if (ok) {
            if (n & 1) {
                int val = i ^ ans ^ penis;
                if (val > n) continue;
                if (cand == -1) cand = val;
                else if (cand != val) {
                    cout << -1 << endl;
                    return;
                }
            } else {
                int val = ans ^ penis;
                if (val > n) continue;
                if (cand == -1) cand = val;
                else if (cand != val) {
                    cout << -1 << endl;
                    return;
                }
            }
        }
    }
    assert(cand!=-1);
    cout << cand << endl;
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
