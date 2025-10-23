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
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

vector<int> solve(int n, int q, vector<array<int, 4>> qu) {
    vector<int> ans;
    // seguinte isomorfismo: (i, j) |=> (i-j, i)
    // agora os updates sao fazer um sweep nas linhas do array (mais facil de pensar pra mim)
    // gostaria de manter apenas, pra cada linha, os divisores de n
    //
    // tah, agora eh basicamente fazer cada update de cada vez, e ir mantendo o modulo atual
    vector<int> divs(n); divs[0] = true;
    for (int i = 1; i < n; ++i) divs[i] = (n % i == 0);
    auto transform = [n] (int i, int j) {return pair((i-j+n)%n, i); };
    vector<vector<ii>> g(n);
    vector<int> vis(n), weight(n);
    for (auto& arr : qu) {
        auto [x1, y1] = transform(arr[0], arr[1]);
        auto [x2, y2] = transform(arr[2], arr[3]);
        g[x1].pb({x2, (y2-y1+n)%n});
        g[x2].pb({x1, (y1-y2+n)%n});
        auto dfs = [&] (auto&& self, int u, int m) -> int {
            vis[u] = m;
            for (auto [v, w] : g[u]) {
                if (vis[v] == m) {
                    int cycle = (weight[u] - weight[v] + m + w) % m;
                    if (cycle) return cycle; 
                } else {
                    weight[v] = (weight[u] + w) % m;
                    int ret = self(self, v, m);
                    if (ret) return ret;
                }
            }
            return 0;
        };
        int ret = 0;
        for (int i = 0; i < n; ++i) {
            if (!vis[i]) {
                int m = n;
                while (true) {
                    int nm = dfs(dfs, i, m);
                    if (nm == 0) break;
                    m = gcd(n, nm);
                    assert(m);
                }
                ret += m;
            }
        }
        ans.pb(ret);
        for (int i = 0; i < n; ++i) vis[i] = 0;
    }
    return ans;
}

vector<int> solve2(int n, int q, vector<array<int, 4>> qu) {
    vector<int> ans;
    // seguinte isomorfismo: (i, j) |=> (i-j, i)
    // agora os updates sao fazer um sweep nas linhas do array (mais facil de pensar pra mim)
    // gostaria de manter apenas, pra cada linha, os divisores de n
    //
    // tah, agora eh basicamente fazer cada update de cada vez, e ir mantendo o modulo atual
    auto transform = [n] (int i, int j) {return pair((i-j+n)%n, i); };
    // quero fazer um dsu meio engracado
    // manter pra cada componente: o mod; a lista de pesos;
    // em um update: se estou unindo componentes separadas: o novo mod sera o gcd dos mods;
    // recompute os pesos na subarvore menor. (small to large, nlogn no final)
    // se estou unindo componentes iguais, temos 2 casinhos: pode ser q o peso que eu to colocando simplesmente nao afeta o gremio (nao faco nada)
    // se o peso afetou o gremio, quer dizer q o gcd vai diminuir. adiciona essa nova aresta ai, e faz o algoritmo naive enquanto os pesos
    // n estabilizarem. fica O(N * lg N) nesse caso tambem, mas amortizado!
    // falta aprender a fazer a query do caminho standard na arvore.
    vector<int> par(n), lvl(n), m(n, n), weight(n), lvl2(n); iota(all(par), 0);
    vector<vector<ii>> g(n);
    // altura do dsu vai ser pequenininha
    auto findp = [&] (auto&& self, int u) -> int {
        if (par[u] == u) return u;
        return self(self, par[u]);
    };
    int comps = n * n;
    for (auto& arr : qu) {
        auto [x1, y1] = transform(arr[0], arr[1]);
        auto [x2, y2] = transform(arr[2], arr[3]);
        // quero unir x1 com x2 com peso (y2-y1)
        int pu = findp(findp, x1);
        int pv = findp(findp, x2);
        if (pu == pv) {
            int cycle = (weight[x1] - weight[x2] + y2 - y1) % m[pu]; cycle = (m[pu] + cycle) % m[pu];
            if (cycle != 0) comps += gcd(cycle, m[pu]) - m[pu], m[pu] = gcd(cycle, m[pu]);
        } else {
            // ao inves de adicionar a aresta x1 --- x2 com peso y2-y1, quero adicionar a aresta pu -- pv
            // o peso sera equivalente a: pu --- x1 --- x2 --- pv ~> weight[x1] - weight[x2] + y2 - y1
            comps -= m[pu] + m[pv];
            if (lvl[pu] < lvl[pv]) swap(x1, x2), swap(y1, y2), swap(pu, pv);
            int nmod = gcd(m[pu], m[pv]), shift_w = (weight[x1] - weight[x2] + y2 - y1) % nmod; shift_w = (shift_w + nmod) % nmod;
            auto dfs = [&] (auto&& self, int u) -> void {
                for (auto [v, w] : g[u]) {
                    weight[v] = (weight[u] + w) % nmod;
                    lvl2[v] = 1 + lvl2[u];
                    self(self, v);
                }
            };
            weight[pv] = shift_w, lvl2[pv] = 1 + lvl2[pu];
            g[pu].pb({pv, shift_w});
            dfs(dfs, pv);
            m[pu] = nmod;
            comps += m[pu];
            par[pv] = pu;
			if (lvl[pu] == lvl[pv]) lvl[pu]++;
        }
        ans.pb(comps);
    }
    return ans;
}

vector<int> brute(int n, int q, vector<array<int, 4>> qu) {
    vector<int> ans;
    vector<vector<int>> id(n, vector<int>(n));
    vector<ii> rev(n*n);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        id[i][j] = n * i + j;
        rev[n * i + j] = {i, j};
    }
    vector<int> par(n*n), lvl(n*n);
    auto findp = [&] (auto&& self, int u) -> int { return par[u] = (par[u] == u ? u : self(self, par[u])); };
    int comp = n * n;
    auto merge = [&] (int x1, int y1, int x2, int y2) {
        if (x1 >= n) x1 -= n;
        if (x2 >= n) x2 -= n;
        if (y1 >= n) y1 -= n;
        if (y2 >= n) y2 -= n;
        int u = findp(findp, id[x1][y1]), v = findp(findp, id[x2][y2]);
        if (u == v) return;
        if (lvl[u] < lvl[v]) swap(u, v);
        par[v] = u;
        if (lvl[u] == lvl[v]) lvl[u]++;
        comp--;
    };
    iota(all(par), 0);
    for (auto arr : qu) {
        int x1 = arr[0], y1 = arr[1];
        int x2 = arr[2], y2 = arr[3];
        for (int k = 0; k < n; ++k) merge(x1 + k, y1 + k, x2 + k, y2 + k);
        ans.pb(comp);
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int n, q; cin >> n >> q;
    vector<array<int, 4>> qu(q);
    for (auto& arr : qu) cin >> arr[0] >> arr[1] >> arr[2] >> arr[3];
    auto ans = solve2(n, q, qu);
    for (auto x : ans) cout << x << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 100), q = rnd(1, 200);
        vector<array<int, 4>> qu(q);
        for (auto& arr : qu) {
            arr[0] = rnd(0, n-1), arr[1] = rnd(0, n-1);
            while (true) {
                arr[2] = rnd(0, n-1), arr[3] = rnd(0, n-1);
                if (arr[2] != arr[0] or arr[3] != arr[1]) break;
            }
        }
        auto my = solve2(n, q, qu);
        auto ans = brute(n, q, qu);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << q << endl;
            for (auto x : qu) cout << x[0] << ' ' << x[1] << ' ' << x[2] << ' ' << x[3] << endl;
            cout << "Your output: ";
            for (auto x : my) cout << x << endl;
            cout << "Correct answer: ";
            for (auto x : ans) cout << x << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
