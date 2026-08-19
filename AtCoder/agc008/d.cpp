#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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

const int INF = 1e9 + 50;
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
	int dfs(int v, int t, int f = INF) {
		if (!f or v == t) return f;
		for (int& i = beg[v]; i < g[v].size(); i++) {
			auto& e = g[v][i];
			if (lev[e.to] != lev[v] + 1) continue;
			int foi = dfs(e.to, t, min(f, e.cap - e.flow));
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

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    vector<int> mark(n*n, -1);
    for (auto& x : a) cin >> x, --x;
    vector<int> b;
    b.pb(-1);
    for (auto x : a) b.pb(x); 
    b.pb(n*n);
    sort(all(b));
    for (int i = 0; i < n; ++i) mark[a[i]] = i;
    dinitz dz(3*n+3);
    int src = 3*n+1, snk = src+1;
    for (int i = 0; i < n; ++i) {
        dz.add(src, 2*i, i);
        dz.add(src, 2*i+1, n-1-i);
        int tipo = 0;
        for (int j = 0; j <= n; ++j) {
            dz.add(2*i+tipo, 2*n+j, b[j+1] - b[j] - 1);
            if (j != n and mark[b[j+1]] == i) tipo = 1;
        }
    }
    for (int j = 0; j <= n; ++j) dz.add(2*n+j, snk, b[j+1] - b[j] - 1);

    int f = dz.max_flow(src, snk);
    if (f != n*n-n) {
        cout << "No" << endl;
        return;
    }
    vector<int> ans(n*n, -1);
    for (int i = 0; i < n; ++i) ans[a[i]] = i;
    vector<vector<int>> bags(n+1);
    for (int i = 0; i < 2*n; ++i) {
        for (auto e : dz.g[i]) {
            if (2*n <= e.to and e.to < src) {
                for (int j = 0; j < e.flow; ++j) bags[e.to-2*n].pb(i/2);
            }
        }
    }
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < sz(bags[i]); ++j) ans[b[i]+j+1] = bags[i][j];
    }
    cout << "Yes" << endl;
    for (auto x : ans) cout << x + 1 << " ";
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
