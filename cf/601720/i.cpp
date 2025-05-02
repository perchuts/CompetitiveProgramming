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
// Block-Cut Tree
//
// Cria a block-cut tree, uma arvore com os blocos
// e os pontos de articulacao
// Blocos sao componentes 2-vertice-conexos maximais
// Uma 2-coloracao da arvore eh tal que uma cor sao
// os blocos, e a outra cor sao os pontos de art.
// Funciona para grafo nao conexo
//
// art[i] responde o numero de novas componentes conexas
// criadas apos a remocao de i do grafo g
// Se art[i] >= 1, i eh ponto de articulacao
// 
// Para todo i <= blocks.size()
// blocks[i] eh uma componente 2-vertce-conexa maximal
// edgblocks[i] sao as arestas do bloco i
// tree[i] eh um vertice da arvore que corresponde ao bloco i
// 
// pos[i] responde a qual vertice da arvore vertice i pertence
// Arvore tem no maximo 2n vertices
//
// O(n+m)
 
struct block_cut_tree {
	vector<vector<int>> g, blocks, tree;
	vector<vector<pair<int, int>>> edgblocks;
	stack<int> s;
	stack<pair<int, int>> s2;
	vector<int> id, art, pos;
	
	block_cut_tree(vector<vector<int>> g_) : g(g_) {
		int n = g.size();
		id.resize(n, -1), art.resize(n), pos.resize(n);
		build();
	}
 
	int dfs(int i, int& t, int p = -1) {
		int lo = id[i] = t++;
		s.push(i);	
		
		if (p != -1) s2.emplace(i, p);
		for (int j : g[i]) if (j != p and id[j] != -1) s2.emplace(i, j);
		
		for (int j : g[i]) if (j != p) {
			if (id[j] == -1) {
				int val = dfs(j, t, i);
				lo = min(lo, val);
 
				if (val >= id[i]) {
					art[i]++;
					blocks.emplace_back(1, i);
					while (blocks.back().back() != j) 
						blocks.back().push_back(s.top()), s.pop();
 
					edgblocks.emplace_back(1, s2.top()), s2.pop();
					while (edgblocks.back().back() != pair(j, i))
						edgblocks.back().push_back(s2.top()), s2.pop();
				}
				// if (val > id[i]) aresta i-j eh ponte
			}
			else lo = min(lo, id[j]);
		}
		
		if (p == -1 and art[i]) art[i]--;
		return lo;
	}
 
	vector<vector<int>> bl;
	vector<int> lvl;
	int tot = 0;
	void init(int u, int p) {
		tot++;
		lvl[u] = lvl[p] + 1;
		bl[0][u] = p;
		for (int i = 1; i < 19; ++i) bl[i][u] = bl[i-1][bl[i-1][u]];
		for (auto v : tree[u]) {
			if (v == p) continue;
			init(v, u);
		}
	}
 
	int lca(int u, int v) {
		if (lvl[u] < lvl[v]) swap(u, v);
		for (int i = 19; i >= 0; --i) {
			if (lvl[bl[i][u]] >= lvl[v]) u = bl[i][u];
		}
		if (u == v) return u;
		for (int i = 19; i >= 0; --i) {
			if (bl[i][u] != bl[i][v]) u = bl[i][u], v = bl[i][v];
		}
		return bl[0][u];
	}
	
	void build() {
		int t = 0;
		for (int i = 0; i < g.size(); i++) if (id[i] == -1) dfs(i, t, -1);
		
		tree.resize(blocks.size());
		for (int i = 0; i < g.size(); i++) if (art[i]) 
			pos[i] = tree.size(), tree.emplace_back();
 
		for (int i = 0; i < blocks.size(); i++) for (int j : blocks[i]) {
			if (!art[j]) pos[j] = i;
			else tree[i].push_back(pos[j]), tree[pos[j]].push_back(i);
		}
 
		bl = vector<vector<int>>(20, vector<int>(tree.size()+1));
		lvl = vector<int>(tree.size()+1);
		init(0, tree.size());
		assert(tot == tree.size());
	}
};
void solve(){
	int n, m; cin >> n >> m;
	vector<vector<int>> g(n);
	map<ii, bool> appear;
	for (int i = 0; i < m; ++i) {
		int u, v; cin >> u >> v;
		--u, --v;
		if (appear[{min(u, v), max(u, v)}]) continue;
		appear[{min(u, v), max(u, v)}] = 1;
		g[u].pb(v), g[v].pb(u);
	}
	block_cut_tree buceta(g);
    int U, V; cin >> U >> V;
    --U, --V;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int c = i, u = U, v = V;
        if (u == c or v == c) {
            continue;
        }
        if (buceta.art[c] == 0) {
            ans++;
            continue;
        }
        u = buceta.pos[u], v = buceta.pos[v], c = buceta.pos[c];
        if (u == v) {
            ans++;
            continue;
        }
        int x = buceta.lca(u, c), y = buceta.lca(v, c), z = buceta.lca(u, v);
        if (x == c or y == c) {
            if (buceta.lvl[z] <= buceta.lvl[c]) {}
            else ans++;
        } else ans++;
    }
    cout << n-ans << endl;
}
 
int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
