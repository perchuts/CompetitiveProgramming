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
// Hopcroft Karp
//
// Computa matching maximo em grafo bipartido
// 'n' e 'm' sao quantos vertices tem em cada particao
// chamar add(i, j) para add aresta entre o cara i
// da particao A, e o cara j da particao B
// (entao i < n, j < m)
//
// O(|E| * sqrt(|V|)) com constante baixa
// Para grafos esparsos gerados aleatoriamente, roda em O(|E| * log(|V|))
// com alta probabilidade

struct hopcroft_karp {
	int n, m;
	vector<vector<int>> g;
	vector<int> dist, nxt, ma, mb;

	hopcroft_karp(int n_, int m_) : n(n_), m(m_), g(n),
		dist(n), nxt(n), ma(n, -1), mb(n, -1) {}

	void add(int a, int b) { g[a].push_back(b); }

	bool dfs(int i) {
		for (int &id = nxt[i]; id < g[i].size(); id++) {
			int j = g[i][id];
			if (mb[j] == -1 or (dist[mb[j]] == dist[i] + 1 and dfs(mb[j]))) {
				ma[i] = j, mb[j] = i;
				return true;
			}
		}
		return false;
	}
	bool bfs() {
		for (int i = 0; i < n; i++) dist[i] = n;
		queue<int> q;
		for (int i = 0; i < n; i++) if (ma[i] == -1) {
			dist[i] = 0;
			q.push(i);
		}
		bool rep = 0;
		while (q.size()) {
			int i = q.front(); q.pop();
			for (int j : g[i]) {
				if (mb[j] == -1) rep = 1;
				else if (dist[mb[j]] > dist[i] + 1) {
					dist[mb[j]] = dist[i] + 1;
					q.push(mb[j]);
				}
			}
		}
		return rep;
	}
	int matching() {
		int ret = 0;
		for (auto& i : g) shuffle(i.begin(), i.end(), rng);
		while (bfs()) {
			for (int i = 0; i < n; i++) nxt[i] = 0;
			for (int i = 0; i < n; i++)
				if (ma[i] == -1 and dfs(i)) ret++;
		}
		return ret;
	}
};

int solve(int n, int m, int k, vector<ii> edg) {
    hopcroft_karp g(n, m);
    vector<int> mark1(n), mark2(n);
    for (auto [u, v] : edg) {
        mark1[u] = mark2[v] = 1;
        g.add(u, v);
    }
    int M = g.matching();
    int t1 = 0, t2 = 0;
    for (int i = 0; i < n; ++i) t1 += mark1[i], t2 += mark2[i];
    int necessary = t1+t2-M; 
    int use = min(k, m-necessary);
	int fds1 = t1 - M, fds2 = t2 - M;
    t1 += use, t2 += use, k -= use;
	while (k) {
		--k;
		if (t1 <= t2 and fds1) t2++, fds1--;
		else if (t1 >= t2 and fds2) t1++, fds2--;
		else if (fds2) fds2--, t1++;
		else if (fds1) fds1--, t2++;
		else break;
	}
	ckmin(t1, n), ckmin(t2, n);
    return n*n - (n-t1) * (n-t2);
}

int brute(int n, int m, int k, vector<ii> edg) {
    int ans = 0;
    for (int i = 0; i < (1 << m); ++i) {
        vector<int> mark1(n), mark2(n);
        if (__builtin_popcount(i) < m-k) continue;
        for (int j = 0; j < m; ++j) {
            if (i >> j & 1) mark1[edg[j].first] = mark2[edg[j].second] = 1;
        }
        int t1 = 0, t2 = 0;
        for (int j = 0; j < n; ++j) t1 += mark1[j], t2 += mark2[j];
        int sobra = m-__builtin_popcount(i);
        t1 += sobra, t2 += sobra;
        ckmin(t1, n), ckmin(t2, n);
        ckmax(ans, n*n - (n-t1)*(n-t2));
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) {
        int n, m, k; cin >> n >> m >> k;
        vector<ii> edg(m);
        for (auto& [x, y] : edg) cin >> x >> y, --x, --y;
        cout << solve(n, m, k, edg) << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 12), m = rnd(1, 2*n), k = rnd(1, m);
        ckmin(m, n * n);
        vector<vector<int>> foi(n, vector<int>(n));
        vector<ii> edg;
        while (sz(edg) != m) {
            int u = rnd(0, n-1), v = rnd(0, n-1);
            if (foi[u][v]) continue;
            foi[u][v] = 1;
            edg.pb({u, v});
        }
        int my = solve(n, m, k, edg), ans = brute(n, m, k, edg);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << m << ' ' << k << endl;
            for (auto [x, y] : edg) cout << x+1 << ' ' << y+1 << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
