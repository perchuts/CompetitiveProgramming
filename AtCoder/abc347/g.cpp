#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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

int score(int& n, vector<vector<int>>& grid) {
    int tot = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n-1; ++j) {
            tot += (grid[i][j]-grid[i][j+1]) * (grid[i][j]-grid[i][j+1]);
            tot += (grid[j][i]-grid[j+1][i]) * (grid[j][i]-grid[j+1][i]);
        }
    }
    return tot;
}

vector<vector<int>> brute(int n, vector<vector<int>> grid) {
    int ans = inf;
    vector<vector<int>> resp;
    auto go = [&] (auto&& self, int k, int cur) -> void {
        if (cur >= ans) return;
        if (k == n * n) { 
            ans = cur, resp = grid;
            return;
        }
        int i = k / n, j = k % n, ncur = cur;
        if (i != 0) ncur += (grid[i][j]-grid[i-1][j]) * (grid[i][j]-grid[i-1][j]);
        if (j != 0) ncur += (grid[i][j]-grid[i][j-1]) * (grid[i][j]-grid[i][j-1]);
        self(self, k+1, ncur);
        if (grid[i][j] == 0) {
            for (int p = 1; p <= 5; ++p) {
                grid[i][j] = p, ncur = cur;
                if (i != 0) ncur += (grid[i][j]-grid[i-1][j]) * (grid[i][j]-grid[i-1][j]);
                if (j != 0) ncur += (grid[i][j]-grid[i][j-1]) * (grid[i][j]-grid[i][j-1]);
                self(self, k+1, ncur);
            }
            grid[i][j] = 0;
        }
    };
    go(go, 0, 0);
    return resp;
}

// Dinitz
//
// O(min(m * max_flow, n^2 m))
// Grafo com capacidades 1: O(min(m sqrt(m), m * n^(2/3)))
// Todo vertice tem grau de entrada ou saida 1: O(m sqrt(n))
const int INF = inf;
struct dinitz {
	const bool scaling = false; // com scaling -> O(nm log(MAXCAP)),
	int lim;                    // com constante alta
	struct edge {
		int to, cap, rev, flow;
		bool res;
		edge(int to_, int cap_, int rev_, bool res_)
			: to(to_), cap(cap_), rev(rev_), flow(0), res(res_) {}
	};

	vector<vector<edge>> g;
	vector<int> lev, beg;
	ll F;
	dinitz(int n) : g(n), F(0) {}

	void add(int a, int b, int c) {
		g[a].emplace_back(b, c, g[b].size(), false);
		g[b].emplace_back(a, 0, g[a].size()-1, true);
	}
	bool bfs(int s, int t) {
		lev = vector<int>(g.size(), -1); lev[s] = 0;
		beg = vector<int>(g.size(), 0);
		queue<int> q; q.push(s);
		while (q.size()) {
			int u = q.front(); q.pop();
			for (auto& i : g[u]) {
				if (lev[i.to] != -1 or (i.flow == i.cap)) continue;
				if (scaling and i.cap - i.flow < lim) continue;
				lev[i.to] = lev[u] + 1;
				q.push(i.to);
			}
		}
		return lev[t] != -1;
	}
	int dfs(int v, int s, int f = INF) {
		if (!f or v == s) return f;
		for (int& i = beg[v]; i < g[v].size(); i++) {
			auto& e = g[v][i];
			if (lev[e.to] != lev[v] + 1) continue;
			int foi = dfs(e.to, s, min(f, e.cap - e.flow));
			if (!foi) continue;
			e.flow += foi, g[e.to][e.rev].flow -= foi;
			return foi;
		}
		return 0;
	}
	ll max_flow(int s, int t) {
		for (lim = scaling ? (1<<30) : 1; lim; lim /= 2)
			while (bfs(s, t)) while (int ff = dfs(s, t)) F += ff;
		return F;
	}
};
// Recupera as arestas do corte s-t
vector<pair<int, int>> get_cut(dinitz& g, int s, int t) {
	g.max_flow(s, t);
	vector<pair<int, int>> cut;
	vector<int> vis(g.g.size(), 0), st = {s};
	vis[s] = 1;
	while (st.size()) {
		int u = st.back(); st.pop_back();
		for (auto e : g.g[u]) if (!vis[e.to] and e.flow < e.cap)
			vis[e.to] = 1, st.push_back(e.to);
	}
	for (int i = 0; i < g.g.size(); i++) for (auto e : g.g[i])
		if (vis[i] and !vis[e.to] and !e.res) cut.emplace_back(i, e.to);
	return cut;
}

vector<vector<int>> solve(int n, vector<vector<int>> grid) {
    int a[] = {1, -1, 0, 0, 0, 0, 1, -1};
    // vou criar 5 nodes
    // 5 * n * n + 2 (src + root) + 2 * (n-1) * n * 5 * 5 (gadget nodes)
    int N = 5 * n * n + 50 * (n-1) * n, src = N, sink = N+1;
    dinitz dz(N + 2);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int viz = 0;
            if (i) viz++;
            if (i != n-1) viz++;
            if (j) viz++;
            if (j != n-1) viz++;
            int lst = src;
            for (int t = 0; t < 5; ++t) {
                if (i == 4 and j == 1) {
                    //cout << lst << ' ' << t * n * n + i * n + j << ' ' << ((t == 5 - grid[i][j] or grid[i][j] == 0) ? viz * (5-t) * (5-t) : inf) << endl;
                }
                dz.add(lst, t * n * n + i * n + j, ((t == 5 - grid[i][j] or grid[i][j] == 0) ? viz * (5-t) * (5-t) : inf));
                lst = t * n * n + i * n + j;
            }
            dz.add(lst, sink, inf);
        }
    }
    int cur = 5 * n * n;
    map<int, array<int, 4>> sexo;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int w = 0; w < 2; ++w) {
                int i2 = i, j2 = j;
                if (w) i2++;
                else j2++;
                if (max(i2, j2) == n) continue;
                for (int a = 0; a < 5; ++a) {
                    for (int b = 0; b < 5; ++b) {
                        sexo[cur] = {i2, j2, a, b};
                        dz.add(cur, sink, 2);
                        if (grid[i][j] == 0 or a < 5 - grid[i][j]) dz.add(a * n * n + i * n + j, cur, 2);
                        if (grid[i2][j2] == 0 or b < 5 - grid[i2][j2]) dz.add(b * n * n + i2 * n + j2, cur, 2);
                        cur++;
                    }
                }
            }
        }
    }
    int ans = dz.max_flow(src, sink) - 100 * n * (n-1);
    auto e = get_cut(dz, src, sink);
    map<ii, int> forb;
    for (auto [x, y] : e) forb[{x, y}] = forb[{y, x}] = 1;
    vector<int> vis(N+2);
    auto dfs = [&] (auto&& self, int u) -> void {
        vis[u] = 1;
        for (auto e : dz.g[u]) {
            if (forb[{e.to, u}] or vis[e.to]) continue;
            self(self, e.to);
        }
    };
    dfs(dfs, src);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j]) continue;
            grid[i][j] = 5;
            for (int t = 0; t < 5; ++t) {
                if (vis[n * n * t + n * i + j]) grid[i][j]--;
            }
        }
    }
    return grid;
}

int32_t main() {_
#ifndef gato
    int n; cin >> n;
    vector<vector<int>> grid(n, vector<int>(n));
    for (auto& x : grid) for (auto& y : x) cin >> y;
    auto ans = solve(n, grid);
    for (auto x : ans) {
        for (auto y : x) cout << y << ' ';
        cout << endl;
    }

#else
    int t = 1;
    while (true) {
        int n = rnd(1, 5);
        int lim = 8;
        vector<vector<int>> grid(n, vector<int>(n));
        for (auto& x : grid) {
            for (auto& y : x) {
                y = rnd((lim == 0), 5);
                if (y == 0) --lim;
            }
        }
        auto my = solve(n, grid);
        auto ans = brute(n, grid);

        if (my != score(n, ans)) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << score(n, ans) << endl;
            for (auto x : ans) {
                for (auto y : x) cout << y << ' ';
                cout << endl;
            }
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
        //if (score(n, my) != score(n, ans)) {
        //    cout << "Wrong answer on test " << t << endl;
        //    cout << "Your output: " << score(n, my) << endl;
        //    for (auto x : my) {
        //        for (auto y : x) cout << y << ' ';
        //        cout << endl;
        //    }
        //    cout << "Answer: " << score(n, ans) << endl;
        //    for (auto x : ans) {
        //        for (auto y : x) cout << y << ' ';
        //        cout << endl;
        //    }
        //    exit(0);
        //}
        //cout << "Accepted on test " << t++ << endl;
    }
#endif
}
