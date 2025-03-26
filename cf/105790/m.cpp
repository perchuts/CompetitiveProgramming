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
const int maxn = 1e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int MAX = maxn;
// Virtual Tree
//
// Comprime uma arvore dado um conjunto S de vertices, de forma que
// o conjunto de vertices da arvore comprimida contenha S e seja
// minimal e fechado sobre a operacao de LCA
// Se |S| = k, a arvore comprimida tem menos que 2k vertices
// As arestas de virt possuem a distancia do vertice ate o vizinho
// Retorna a raiz da virtual tree
// 
// lca::pos deve ser a ordem de visitacao no dfs
// voce pode usar o LCAcomHLD, por exemplo
//
// O(k log(k))
namespace lca {
vector<int> g[MAX];
int pos[MAX], h[MAX], sz[MAX];
int pai[MAX], t;

void build(int k, int p = -1, int f = 1) {
    pos[k] = t++; sz[k] = 1;
    for (int& i : g[k]) if (i != p) {
        pai[i] = k;
        h[i] = (i == g[k][0] ? h[k] : i);
        build(i, k, f); sz[k] += sz[i];

        if (sz[i] > sz[g[k][0]] or g[k][0] == p) swap(i, g[k][0]);
    }
    if (p*f == -1) t = 0, h[k] = k, build(k, -1, 0);
}

int lca(int a, int b) {
    if (pos[a] < pos[b]) swap(a, b);
    return h[a] == h[b] ? b : lca(pai[h[a]], b);
}

bool anc(int a, int b) {
    return pos[a] <= pos[b] and pos[b] <= pos[a]+sz[a]-1;
}
}
vector<int> virt[MAX];

#warning lembrar de buildar o LCA antes
int build_virt(vector<int> v) {
	auto cmp = [&](int i, int j) { return lca::pos[i] < lca::pos[j]; };
	sort(v.begin(), v.end(), cmp);
	for (int i = v.size()-1; i; i--) v.push_back(lca::lca(v[i], v[i-1]));
	sort(v.begin(), v.end(), cmp);
	v.erase(unique(v.begin(), v.end()), v.end());
	for (int i = 0; i < v.size(); i++) virt[v[i]].clear();
	for (int i = 1; i < v.size(); i++) virt[lca::lca(v[i-1], v[i])].clear();
	for (int i = 1; i < v.size(); i++) {
		int parent = lca::lca(v[i-1], v[i]);
#warning soh to colocando aresta descendo
		virt[parent].emplace_back(v[i]);
	}
	return v[0];
}
int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

vector<int> solve(int n, vector<ii> edg, vector<vector<int>> queries){
    for (int i = 0; i < n; ++i) lca::g[i].clear();
    for (auto [u, v] : edg) lca::g[u-1].pb(v-1), lca::g[v-1].pb(u-1);
    lca::build(0);
    vector<int> mark(n, -1), qt(n), added(n), subt(n);
    vector<vector<int>> bichos(n);
    vector<int> resp;
    for (auto caras : queries) {
        int k = sz(caras), ans = 0;
        vector<int> atv(k);
        for (int i = 0; i < k; ++i) caras[i]--, mark[caras[i]] = i, ans += caras[i]+1;
        int root = build_virt(caras);
        vector<int> par(k), lvl(k, 1);
        iota(all(par), 0);
        auto findp = [&] (auto&& self, int x) -> int {
            return par[x] = (par[x] == x ? x : self(self, par[x]));
        };
        auto unite = [&] (int x, int y) -> int {
            x = findp(findp, x), y = findp(findp, y);
            if (x == y) return 0LL;
            if (lvl[x] < lvl[y]) swap(x, y);
            par[y] = x;
            int ret = lvl[x] * lvl[y];
            lvl[x] += lvl[y];
            return ret;
        };
        auto add = [&] (int x, int val) {
            atv[x] = 1;
            if (x and atv[x-1]) {
				int w = unite(x, x-1);
//#ifndef gato
//				cout << x << "<->" << x-1 << endl;
//				cout << "Adicionando " << w << " com raiz " << val << endl;
//#endif
				added[val-1] += w;
			}
            if (x != k-1 and atv[x+1]) {
				int w = unite(x, x+1);
//#ifndef gato
//				cout << x << "<->" << x+1 << endl;
//				cout << "Adicionando " << w << " com raiz " << val << endl;
//#endif
				added[val-1] += w;
			}
        };
        auto pre = [&] (auto&& self, int u) -> int {
            qt[u] = (mark[u] != -1);
            for (auto v : virt[u]) qt[u] += self(self, v);
            return qt[u];
        };
        pre(pre, root);
        auto dfs = [&] (auto&& self, int u) -> void {
            ii mx = {-1, -1};
            for (auto v : virt[u]) if (ckmax(mx.first, qt[v])) mx.second = v;
            for (auto v : virt[u]) if (v != mx.second) {
                self(self, v);
                for (auto x : bichos[v]) par[x] = x, lvl[x] = 1, atv[x] = 0;
            }
            if (mx.second != -1) self(self, mx.second), swap(bichos[u], bichos[mx.second]);
//#ifndef gato
//			cout << "vou calcular o " << u << endl;
//			for (int i = 0; i < k; ++i) cout << atv[i] << ' ';
//			cout << endl;
//#endif
            if (mark[u] != -1) add(mark[u], u+1), bichos[u].pb(mark[u]);
            for (auto v : virt[u]) {
				subt[u] += subt[v];
				if (v != mx.second) {
					added[u] -= subt[v];
					for (auto w : bichos[v]) add(w, u+1), bichos[u].pb(w);
				}
            }
			subt[u] += added[u];
			ans += (u+1)*added[u];
        };
        dfs(dfs, root);
//#ifndef gato
//		cout << "added: ";
//		for (int i = 0; i < n; ++i) cout << added[i] << ' ';
//		cout << endl;
//#endif
        resp.pb(ans);
        auto limpa = [&] (auto&& self, int u) -> void {
            mark[u] = -1;
            qt[u] = added[u] = subt[u] = 0;
            bichos[u].clear();
            for (auto v : virt[u]) self(self, v);
        };
        limpa(limpa, root);
    }
    return resp;
}

vector<int> brute(int n, vector<ii> edg, vector<vector<int>> queries) {
    vector<vector<int>> g(n);
    for (auto [x, y] : edg) {
        --x, --y;
        g[x].pb(y), g[y].pb(x);
    }
    vector<int> resp;
    for (auto caras : queries) {
        int k = sz(caras), tot = 0;
        for (int i = 0; i < k; ++i) for (int j = i; j < k; ++j) {
            vector<int> mark(n);
            for (int w = i; w <= j; ++w) mark[caras[w]-1] = 1;
            int ans = 0;
            auto get = [&] (auto&& self, int u, int p) -> int {
                int eu = mark[u];
                for (auto v : g[u]) {
                    if (v == p) continue;
                    eu += self(self, v, u);
                }
                if (!ans and j-i+1 == eu) ans = u+1;
                return eu;
            };
            get(get, 0, 0);
            tot += ans;
        }
        resp.pb(tot);
    }
    return resp;
}

int32_t main(){_
#ifndef gato
    int n, q; cin >> n >> q;
    vector<ii> edg;
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v;
        edg.pb({u, v});
    }
    vector<vector<int>> queries(q);
    for (auto& x : queries) {
        int k; cin >> k;
        x.resize(k);
        for (auto& y : x) cin >> y;
    }
    auto ans = solve(n, edg, queries);
    for (auto x : ans) cout << x << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 20), q = 20;
        vector<ii> edg;
        for (int i = 2; i <= n; ++i) edg.pb({i, rnd(1, i-1)});
        vector<vector<int>> queries(q);
        vector<int> pp(n); iota(all(pp), 1);
        for (auto& x : queries) {
            int k = rnd(1, n);
            shuffle(all(pp), rng);
            for (int i = 0; i < k; ++i) x.pb(pp[i]);
        }
        auto my = solve(n, edg, queries);
        auto ans = brute(n, edg, queries);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << q << endl;
            for (auto [x, y] : edg) cout << x << ' ' << y << endl;
            for (auto x : queries) {
                cout << sz(x) << ' ';
                for (auto y : x) cout << y << ' ';
                cout << endl;
            }
            cout << "Your output: " << endl;
            for (auto x : my) cout << x << endl;
            cout << "Answer: " << endl;
            for (auto y : ans) cout << y << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
