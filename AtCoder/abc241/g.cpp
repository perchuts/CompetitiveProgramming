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
// Dinitz
//
// O(min(m * max_flow, n^2 m))
// Grafo com capacidades 1: O(min(m sqrt(m), m * n^(2/3)))
// Todo vertice tem grau de entrada ou saida 1: O(m sqrt(n))

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
	int dfs(int v, int s, int f = 4818418) {
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

void solve(){
    int n, m; cin >> n >> m;
    vector<vector<int>> win(n, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        win[u][v] = 1;
    }
    vector<int> ganha;
    for (int i = 0; i < n; ++i) {
        vector<int> wins(n);
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (j == k) continue;
                if (win[j][k]) wins[j]++;
                if (j == i and (win[j][k] == 0 and win[k][j] == 0)) wins[i]++;
            }
        }
        bool ok = 1;
        for (int j = 0; j < n; ++j) {
            if (wins[j] >= wins[i] and j != i) ok = 0;
        }
        if (!ok) continue;
        vector<ii> matches;
        for (int j = 0; j < n; ++j) for (int k = j+1; k < n; ++k) {
            if (j == i or k == i or win[j][k] or win[k][j]) continue;
            matches.pb({j, k});
        }
        int l = sz(matches), src = n+l, sink = n+l+1;
        dinitz dz(n+l+2);
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            dz.add(j, sink, wins[i] - wins[j] - 1);
        }
        for (int j = 0; j < l; ++j) {
            auto [x, y] = matches[j];
            dz.add(src, n+j, 1);
            dz.add(n+j, x, 1);
            dz.add(n+j, y, 1);
        }
        if (dz.max_flow(src, sink) == l) ganha.pb(i);
    }
    for (auto x : ganha) cout << x + 1 << ' ';
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
