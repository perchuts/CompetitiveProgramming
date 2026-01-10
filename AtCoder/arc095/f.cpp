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
    vector<ii> edg(n-1);
    vector<vector<int>> g(n);
    for (auto& [x, y] : edg) cin >> x >> y, --x, --y, g[x].pb(y), g[y].pb(x);
    // once the permutation is set, let s_1 < ... < s_k be the indicies of the suffix minimums.
    // notice 1 = p[s_1] < ... < p[s_k]
    // we have edges from inv[n] ... inv[p[s_k]+1] to s_k
    // inv[p[s_k]] ... inv[p[s_{k-1}]+1] to s_{k-1}
    // inv[p[s_2]] ... inv[2] to s_1
    // folhas: nao suffix minimums
    // u -> cara menor que u
    // entao dado uma arvore direcionada, posso fazer algo como uma ordenacao topologica. em seguida, precisamos posicionar os
    // suffix minimuns de acordo.
    // i.e. ordene os vertices de valor nao folha em ordem crescente.
    if (n == 2) {
        cout << "1 2" << endl;
        exit(0);
    }
    int src = (sz(g[0]) > 1 ? 0 : g[0][0]);
    vector<int> ponta;
    auto dfs = [&] (auto&& self, int u, int p, int cnt = 0) -> void {
        for (auto v : g[u]) {
            if (v == p) continue;
            if (sz(g[v]) == 1) continue;
            self(self, v, u, 1);
            cnt++;
        }
        if (cnt > 2) {
            cout << -1 << endl;
            exit(0);
        }
        if (cnt == 1) ponta.pb(u);
    };
    dfs(dfs, src, src);
    vector<int> z;
    if (ponta.empty()) {
        // 1 3 4 5 6 2
        cout << 1 << ' ';
        for (int i = 3; i < n; ++i) cout << i << " ";
        cout << 2 << ' ' << n << endl;
        exit(0);
    }
    for (auto v : ponta) {
        if (sz(g[g[v][0]]) == 1) v = g[v][0];
        else v = g[v][1];
        int cur = v, lst = -1;
        vector<int> seq;
        while (true) {
            seq.pb(sz(g[cur]) - (cur != v));
            int prox = -1;
            for (auto w : g[cur]) {
                if (lst != w and sz(g[w]) > 1) prox = w;
            }
            if (prox == -1) break;
            lst = cur, cur = prox;
        }
        vector<int> p;
        cur = 0;
        for (auto x : seq) {
            for (int i = cur + 1; i < cur + x; ++i) p.pb(i);
            p.pb(cur);
            cur += x;
        }
        p.pb(n-1);
        if (z.empty() or p < z) z = p;
    }
    for (auto x : z) cout << x + 1 << ' ';
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
