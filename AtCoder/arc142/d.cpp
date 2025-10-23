#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
#define gato

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
    // Lemma 3: for a tree to have at least one valid subset, no more than two leafs can be connected to the same vertex.
    // proof. consider otherwise. Let u be such vertex, and a, b, c be leafs connected to u. by L2, a or u must be in any valid subset S. if u \in S,
    // WLOG a, b \in S, because otherwise we would be able to reach > 1 state from S. but this makes moving both a and b impossible. if u \notin S,
    // then a \in S and b, c \notin S. We reach at least two states from the neighboring state of S. absurd.
    //
    // From this, we can slightly simplify the input tree: while there is a vertex u with three neighbors, two being leafs (a, b), we can remove all of them 
    // from the tree and multiply the answer by two (all valid sets must have exactly (u, a) or (u, b))
    //
    // okay, so given a dominating set D, when it forms a valid subset? one simple condition is: if i can partition my graph into many disjoint paths,
    // with each consisting of vertices from D, and a vertex from [n] \ D in one of the borders of the path. The "construction" of the neighbor of D is trivial.
    // can there be any more valid sets?
    // i have convinced myself that this is an if and only if (by both conditions of valid set, the directed graph of swaps naturally forms this partition).

    // so problem is: count number p_k of partitions of G into K paths of length >= 2, answer is sum p_k * 2^k (clearly ans is even by this formula)
    // dp[u][0]: no path ending at here
    // dp[u][1]: path ending at here
    vector<vector<int>> dp(n, vector<int>(5));
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        // dp[u][i]: tamanho da branch que ta saindo daqui
        vector<int> cc;
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
            cc.pb(v);
        }
        // o numero de transicoes eh bem infinito, mas da pra separar pelo mais simples: quantos caras de tamanho 1 existem

        // 0 caras de tamanho 1
        // dp[0]
        // 2 * dp[a][2] * dp[b][2] * \prod (dp[c][0] + 2*dp[c][2] + dp[c][4])
        {
            vector<int> pref(sz(cc)+1, 1), suf = pref;
            for (int i = 1; i <= sz(cc); ++i) pref[i] = pref[i-1] * (dp[cc[i-1]][0] + 2 * dp[cc[i-1]][2] + dp[cc[i-1]][4]) % mod;
            for (int i = sz(cc)-1; i >= 0; --i) suf[i] = suf[i+1] * (dp[cc[i]][0] + 2 * dp[cc[i]][2] + dp[cc[i]][4]) % mod;
            int add = 0, cum = 0;
            for (int i = 0; i < sz(cc); ++i) {
                int v = cc[i];
                dp[u][0] = (dp[u][0] + add * dp[v][2] % mod * suf[i+1] * 2) % mod;
                add = (add * (dp[v][0] + 2 * dp[v][2]) % mod + cum * dp[v][2]) % mod;
                cum = (cum * (dp[v][0] + 2 * dp[v][2])) % mod;
            }
        }
        // dp[1] -> proibido dp[4] interagir com dp[1]!!!
        {
            dp[u][1] = 1;
            // nao eh *2dp[v][2] pra nao dar problema de multiplicidade! qnd o u se definir tds os caras de baixo vao se definir
            for (auto v : cc) dp[u][1] = dp[u][1] * (dp[v][0] + dp[v][2]) % mod;
        }
        // dp[2] -> duas versoes: se nao tem dp[4], me comporto como um dp[2] mesmo. mas se existe PELO MENOS UM dp[4], entao sou como um dp[1] pro meu pai
        {
            // eh escolher alguem pra me adotar
            // msm ideia da multiplicidade do dp[1]
            vector<int> pref(sz(cc)+1, 1), suf = pref;
            for (int i = 1; i <= sz(cc); ++i) pref[i] = pref[i-1] * (dp[cc[i-1]][0] + dp[cc[i-1]][2]) % mod;
            for (int i = sz(cc)-1; i >= 0; --i) suf[i] = suf[i+1] * (dp[cc[i]][0] + dp[cc[i]][2]) % mod;
            for (int i = 0; i < sz(cc); ++i) {
                dp[u][2] = (dp[u][2] + pref[i] * suf[i+1] % mod * dp[cc[i]][2]) % mod;
            }
        }
		// versao com pelo menos um filho meu sendo o dp[4]. particionar pelo dp[4] mais a esquerda!!
        {
            // eh escolher alguem pra me adotar
            // msm ideia da multiplicidade do dp[1]
            vector<int> pref1(sz(cc)+1, 1), suf1 = pref1, pref2 = suf1, suf2 = pref2;

            for (int i = 1; i <= sz(cc); ++i) pref1[i] = pref1[i-1] * (dp[cc[i-1]][0] + dp[cc[i-1]][2] + dp[cc[i-1]][4]) % mod;
            for (int i = sz(cc)-1; i >= 0; --i) suf1[i] = suf1[i+1] * (dp[cc[i]][0] + dp[cc[i]][2] + dp[cc[i]][4]) % mod;

            for (int i = 1; i <= sz(cc); ++i) pref2[i] = pref2[i-1] * (dp[cc[i-1]][0] + dp[cc[i-1]][2]) % mod;
            for (int i = sz(cc)-1; i >= 0; --i) suf2[i] = suf2[i+1] * (dp[cc[i]][0] + dp[cc[i]][2]) % mod;

            for (int i = 0; i < sz(cc); ++i) {
				int ways = (pref1[i] * suf1[i+1] - pref2[i] * suf2[i+1]) % mod;
				ways = (ways + mod) % mod;
				dp[u][1] = (dp[u][1] + ways * dp[cc[i]][2]) % mod;
            }
        }
        // agora deixo ter 1 cara de tamanho 1. automaticamente vou ter que me parear com ele!
        // dp[0] -> proibido de transicionar com dp[4]
        {
            // vou escolher outro bicho pra me parear junto. o resto vai ter q ser dp[0] ou dp[2]
            // dp[a][1] * dp[b][2] * \prod (dp[c][0] + dp[c][2])
            vector<int> pref(sz(cc)+1, 1), suf = pref;
            for (int i = 1; i <= sz(cc); ++i) pref[i] = pref[i-1] * (dp[cc[i-1]][0] + dp[cc[i-1]][2]) % mod;
            for (int i = sz(cc)-1; i >= 0; --i) suf[i] = suf[i+1] * (dp[cc[i]][0] + dp[cc[i]][2]) % mod;
            int um = 0, dois = 0;
            for (int i = 0; i < sz(cc); ++i) {
                dp[u][0] = (dp[u][0] + 2 * um * dp[cc[i]][2] % mod * suf[i+1]) % mod;
                dp[u][0] = (dp[u][0] + 2 * dois * dp[cc[i]][1] % mod * suf[i+1]) % mod;
                um = (um * (dp[cc[i]][0] + dp[cc[i]][2]) + pref[i] * dp[cc[i]][1]) % mod;
                dois = (dois * (dp[cc[i]][0] + dp[cc[i]][2]) + pref[i] * dp[cc[i]][2]) % mod;
            }
        }
        // dp[2] -> acredito q seja identico ao caso anterior
        {
            // escolher alguem pra me adotar; tomar cuidado com *2 dnv
            vector<int> pref(sz(cc)+1, 1), suf = pref;
            for (int i = 1; i <= sz(cc); ++i) pref[i] = pref[i-1] * (dp[cc[i-1]][0] + dp[cc[i-1]][2]) % mod;
            for (int i = sz(cc)-1; i >= 0; --i) suf[i] = suf[i+1] * (dp[cc[i]][0] + dp[cc[i]][2]) % mod;
            for (int i = 0; i < sz(cc); ++i) {
                dp[u][2] = (dp[u][2] + pref[i] * suf[i+1] % mod * dp[cc[i]][1]) % mod;
            }
        }
		// versao com pelo menos um filho meu sendo o dp[4]. particionar pelo dp[4] mais a esquerda!!
        {
            // eh escolher alguem pra me adotar
            // msm ideia da multiplicidade do dp[1]
            vector<int> pref1(sz(cc)+1, 1), suf1 = pref1, pref2 = suf1, suf2 = pref2;

            for (int i = 1; i <= sz(cc); ++i) pref1[i] = pref1[i-1] * (dp[cc[i-1]][0] + dp[cc[i-1]][2] + dp[cc[i-1]][4]) % mod;
            for (int i = sz(cc)-1; i >= 0; --i) suf1[i] = suf1[i+1] * (dp[cc[i]][0] + dp[cc[i]][2] + dp[cc[i]][4]) % mod;

            for (int i = 1; i <= sz(cc); ++i) pref2[i] = pref2[i-1] * (dp[cc[i-1]][0] + dp[cc[i-1]][2]) % mod;
            for (int i = sz(cc)-1; i >= 0; --i) suf2[i] = suf2[i+1] * (dp[cc[i]][0] + dp[cc[i]][2]) % mod;

            for (int i = 0; i < sz(cc); ++i) {
				int ways = (pref1[i] * suf1[i+1] - pref2[i] * suf2[i+1]) % mod;
				ways = (ways + mod) % mod;
				dp[u][1] = (dp[u][1] + ways * dp[cc[i]][1]) % mod;
            }
        }
        // agora 2 caras de tamanho 1. vou ter q me parear com ambos, sem escolhas
        // dp[0]
        {
            // dp[a][1] * dp[b][1] * \prod dp[0] -> tudo tem q ser zero!!
            vector<int> pref(sz(cc)+1, 1), suf = pref;
            for (int i = 1; i <= sz(cc); ++i) pref[i] = pref[i-1] * (dp[cc[i-1]][0]+dp[cc[i-1]][4]) % mod;
            for (int i = sz(cc)-1; i >= 0; --i) suf[i] = suf[i+1] * (dp[cc[i]][0]+dp[cc[i]][4]) % mod;
            int um = 0;
            for (int i = 0; i < sz(cc); ++i) {
                dp[u][4] = (dp[u][4] + 2 * um * dp[cc[i]][1] % mod * suf[i+1]) % mod;
                um = (um * dp[cc[i]][0] + pref[i] * dp[cc[i]][1]) % mod;
            }
        }
    };
    dfs(dfs, 0, 0);
	for (int i = 0; i < n; ++i) {
		cout << dp[i][0] << ' ' << dp[i][1] << ' ' << dp[i][2] << ' ' << dp[i][4] << endl;
	}
    return (dp[0][0] + dp[0][2] * 2 + dp[0][4]) % mod;
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
    for (int i = 0; i < (1 << n); ++i) if (sz(g2[i]) == 1 and sz(g2[g2[i][0]]) == 1) ans++;
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
