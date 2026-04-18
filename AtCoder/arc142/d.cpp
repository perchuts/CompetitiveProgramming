#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
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
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int solve(int n, vector<vector<int>> g) {
    // Lemma 1: the answer comes in pairs.
    // proof. consider the graph G_S s.t. vertices are non even subsets of input graph, and uv \in E(G_S) iff you can go from u <-> v in one step.
    // condition two being valid for u is equivalent to the component contaning u being a path on two vertices.
    // The argument used to prove Lemma 1 is very powerful. We can reuse it to make other claims about valid states.
    // Lemma 2: each valid state must be a dominating set.
    // proof. consider otherwise. one can easily show that the component containing such state has at least three vertices.
    // from now on, i make some particular claims that are probably useful to gather some intuiton, but do not generalize very well.
    // Lemma 3: for a tree to have at least one valid subset, no more than two leafs can be connected to the same vertex.
    // proof. consider otherwise. Let u be such vertex, and a, b, c be leafs connected to u. by L2, a or u must be in any valid subset S. if u \in S,
    // WLOG a, b \in S, because otherwise we would be able to reach > 1 state from S. but this makes moving both a and b impossible. if u \notin S,
    // then a \in S and b, c \notin S. We reach at least two states from the neighboring state of S. absurd.
    //
    // From this, we can slightly simplify the input tree: while there is a vertex u with three neighbors, two being leafs (a, b), we can remove all of them 
    // from the tree and multiply the answer by two (all valid sets must have exactly (u, a) or (u, b))
    //
    //
    //
    // okay, so given a dominating set D, when it forms a valid subset? one simple condition is: if i can partition my graph into many disjoint paths,
    // with each consisting of vertices from D and one vertex from [n] \ D in one of the borders of the path. The "construction" of the neighbor of D is trivial.
    // can there be any more valid sets?
    // i have convinced myself that this is an if and only if (by both conditions of valid set, the directed graph of swaps naturally forms this partition).
    // stronger necessity: borders of each path should neighbor borders of other paths or be leafs.
    // to define which border of each path is empty, should respect the constraint that no neighboring borders can be of same type.

    vector<vector<int>> dp(n, vector<int>(5));
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        // dp[u][i]: tamanho da branch que ta saindo daqui
        vector<int> c;
        for (auto v : g[u]) {
            if (v != p) self(self, v, u);
        }
        for (auto v : g[u]) {
            if (v != p) c.pb(v);
        }
        array<int, 4> tipos;
        tipos[0] = 1;
        tipos[1] = tipos[2] = tipos[3] = 0;
        dp[u][0] = dp[u][1] = 1;
        for (auto v : c) {
            tipos[3] = (tipos[3] * dp[v][4] + tipos[2] * dp[v][1] + tipos[1] * dp[v][0]) % mod;
            tipos[2] = (tipos[2] * dp[v][4] + tipos[0] * dp[v][0]) % mod;
            tipos[1] = (tipos[1] * dp[v][4] + tipos[0] * dp[v][1]) % mod;
            tipos[0] = tipos[0] * dp[v][4] % mod;
            // start here!
            dp[u][0] = dp[u][0] * dp[v][3] % mod;
            dp[u][1] = dp[u][1] * dp[v][2] % mod;
        }
        dp[u][4] = tipos[3];
        dp[u][0] = (dp[u][0] + tipos[2]) % mod;
        dp[u][1] = (dp[u][1] + tipos[1]) % mod;
        // not start here
        tipos[0] = tipos[1] = tipos[2] = tipos[3] = 0;
        tipos[0] = tipos[1] = 1;
        for (auto v : c) {
            tipos[2] = (tipos[2] * dp[v][3] + tipos[1] * dp[v][0]) % mod;
            tipos[3] = (tipos[3] * dp[v][2] + tipos[0] * dp[v][1]) % mod;
            tipos[0] = tipos[0] * dp[v][2] % mod;
            tipos[1] = tipos[1] * dp[v][3] % mod;
        }
        dp[u][2] = tipos[2];
        dp[u][3] = tipos[3];
    };
    dfs(dfs, 0, 0);
    //for (int i = 0; i < n; ++i) {
    //    for (int j = 0; j < 5; ++j) cout << dp[i][j] << " \n"[j==4];
    //}
    return (dp[0][2] + dp[0][3] + dp[0][4]) % mod;
}

int brute(int n, vector<vector<int>> g) {
    vector<vector<int>> nodes(n+1);
    for (int i = 1; i < (1 << n); ++i) nodes[__builtin_popcount(i)].pb(i);
    vector<vector<int>> g2(1<<n);
    for (int i = 1; i <= n; ++i) {
        for (auto a : nodes[i]) {
            for (auto b : nodes[i]) {
                if (a <= b) continue;
                bool ok = true;
                auto dfs = [&] (auto&& self, int u, int p) -> int {
                    int tem = 0, need = 0;
                    for (auto v : g[u]) {
                        if (v == p) continue;
                        int res = self(self, v, u);
                        if (ok == false) return 0;
                        if (res > 0) tem++;
                        if (res < 0) need++;
                    }
                    if (max(tem, need) > 1) ok = false;
                    int tipo = 2 * (a >> u & 1) + (b >> u & 1);
                    if (tipo == 0) {
                        if (tem or need) ok = false;
                        return 0;
                    } else if (tipo == 1) {
                        if (need) ok = false;
                        return (tem ? 0 : -1);
                    } else if (tipo == 2) {
                        if (tem) ok = false;
                        return (need ? 0 : 1);
                    } 
                    if (tem == 0 and need == 0) ok = false;
                    return tem - need;
                };
                int ret = dfs(dfs, 0, 0);
                if (ret == 0 and ok == 1) g2[a].pb(b), g2[b].pb(a);
            }
        }
    }
    int ans = 0;
    //cout << "valid states: ";
    for (int i = 0; i < (1 << n); ++i) {
        if (sz(g2[i]) == 1 and sz(g2[g2[i][0]]) == 1) {
            //cout << bitset<6>(i) << endl;
            ans++;
        }
    }
    return ans;
}
int32_t main() {_
#ifndef gato
    int n; cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    cout << solve(n, g) << endl;
    //cout << brute(n, g) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 10);
        vector<vector<int>> g(n);
        vector<ii> edg;
        for (int i = 1; i < n; ++i) {
            int j = rnd(0, i-1);
            edg.pb({j, i});
            g[j].pb(i), g[i].pb(j);
        }
        int my = solve(n, g), ans = brute(n, g);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto [x, y] : edg) cout << x + 1 << ' ' << y + 1 << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
