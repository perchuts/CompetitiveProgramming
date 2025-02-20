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
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
// Articulation Points
//
// Computa os pontos de articulacao (vertices criticos) de um grafo
//
// art[i] armazena o numero de novas componentes criadas ao deletar vertice i
// se art[i] >= 1, entao vertice i eh ponto de articulacao
// 
// O(n+m)

int N;
vector<vector<int>> g;
stack<int> s;
vector<int> id, art;

int dfs_art(int i, int& t, int p = -1) {
	int lo = id[i] = t++;
	s.push(i);
	for (int j : g[i]) if (j != p) {
		if (id[j] == -1) {
			int val = dfs_art(j, t, i);
			lo = min(lo, val);

			if (val >= id[i]) {
				art[i]++;
				while (s.top() != j) s.pop();
				s.pop();
			}
			// if (val > id[i]) aresta i-j eh ponte
		}
		else lo = min(lo, id[j]);
	}
	if (p == -1 and art[i]) art[i]--;
	return lo;
}

void compute_art_points() {
	id = vector<int>(N, -1);
	art = vector<int>(N, 0);
	int t = 0;
	for (int i = 0; i < N; i++) if (id[i] == -1) 
		dfs_art(i, t, -1);
}
void solve(){
    int n, m; cin >> n >> m;
    N = n*m;
    g.resize(N);
    vector<string> grid(n);
    for (auto& x : grid) cin >> x;
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
        if (i < n-1 and grid[i][j] == '#' and grid[i+1][j] == '#') g[m*i+j].pb(m*(i+1)+j), g[m*(i+1)+j].pb(m*i+j);
        if (j < m-1 and grid[i][j] == '#' and grid[i][j+1] == '#') g[m*i+j].pb(m*i+j+1), g[m*i+j+1].pb(m*i+j);
    }
    compute_art_points();
    int s1 = 0, s2 = 0, cmps = 0;
    vector<int> foi(N);
    auto dfs = [&] (auto&& self, int u) -> void {
        foi[u] = 1;
        for (auto v : g[u]) {
            if (!foi[v]) self(self, v);
        }
    };
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
        if (foi[m*i+j] == false and grid[i][j] == '#') dfs(dfs, m*i + j), cmps++;
    }
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
        if (grid[i][j] == '#') {
            s2++;
            s1 += cmps + art[m*i+j] - g[m*i+j].empty();
            s1 %= mod;
        }
    }
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    cout << (s1 * fexp(s2, mod-2)) % mod << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
