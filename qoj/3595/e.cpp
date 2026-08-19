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
const int INF = 1e18;

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
    vector<vector<int>> a(n+2, vector<int>(n+2));
    for (auto& x : a) for (auto& y : x) cin >> y;
    // faca (i, j) -> (i+j, i-j)
    // pra voltar: (i, j) -> ((i+j)/2, (i-j)/2)
    // need: 0 <= (i+j)/2 <= n+1
    //       0 <= (i-j)/2 <= n+1
    // need:
    //       0 <= i <= 2n+2
    //       -n+1 <= j <= n+1
    //       i, j tem a mesma paridade
    // multiplique a por 2
    // 2a[x][y] = F(x+y) + G(x-y)
    // onde F(t) = \sum_{(i, j) eh bomba} |t - (i + j)|, G(t) = \sum_{(i, j) eh bomba} |t - (i - j)|
    // F(t) - F(t-1): {(i, j) t.q. i+j < t} - {(i, j) t.q. i+j >= t}
    // F(t) - F(t-1) - (F(t-1) - F(t-2)) = {<t} - {>=t} - ({<t-1} - {>=t-1}) = ({<t} - {<t-1}) + ({>=t-1} - {>=t})
    // = {=t-1} + {=t-1} = 2 * {=t-1}
    // F(t+1) - 2F(t) + F(t-1) = 2{=t}
    //
    // F(2k+2) - 2F(2k+1) + F(2k) = 2{=2k+1} (x1)
    // F(2k+1) - 2F(2k)   + F(2k-1) = 2{=2k}  (x2)
    // F(2k) - 2F(2k-1)   + F(2k-2) = 2{=2k-1} (x1)
    //                                         =
    // F(2k+2) - 2F(2k) + F(2k-2) = 2{=2k+1} + 4{=2k} + 2{=2k-1}
    //
    // 2a[x+1][y+1] - 2a[x][y] = F(x+y+2) - F(x+y) 
    // 2a[x+2][y+2] - 4a[x+1][y+1] + 2a[x][y] = F(x+y+4) - 2F(x+y+2) + F(x+y) = 2{=x+y+3} + 4{=x+y+2} + 2{=x+y+1}
    // we have that valid bombs are in 2 <= x + y <= 2N
    // make P[i] = {=i-1} + 2{=i} + {=i+1}
    // we can get P[2], ..., P[2N]
    vector<int> P(2*n+1);
    for (int S = 2; S <= 2*n; ++S) {
        int i = min(n-1, S-2), j = S - 2 - i;
        P[S] = a[i+2][j+2] - 2 * a[i+1][j+1] + a[i][j];
    }
    vector<int> val(2*n+1), val2(2*n+1);
    for (int v2 = 0; v2 < 2; ++v2) {
        val[2] = v2;
        for (int i = 2; i < 2*n; ++i) {
            val[i+1] = P[i] - 2*val[i] - val[i-1];
        }
        if (P[2*n] == val[2*n-1] + 2 * val[2*n]) break;
    }
    vector<int> F(2*n+3), G(2*n+3);
    for (int t = 0; t <= 2*n+2; ++t) {
        for (int i = 0; i <= 2*n; ++i) F[t] += val[i] * abs(t - i);
    }
    int shift = n+1;
    for (int t = -n-1; t <= n+1; ++t) {
        int i = max(0LL, t), j = i - t;
        G[i - j + shift] = 2 * a[i][j] - F[i+j];
    }
    for (int i = -n+1; i <= n-1; ++i) val2[i+shift] = (G[i+1+shift] - 2*G[i+shift] + G[i-1+shift])/2;
    // agr virou um problema classico de fluxo
    int src = 4*n-2, snk = src+1;
    dinitz dz(4*n);
    for (int i = 2; i <= 2*n; ++i) dz.add(src, i-2, val[i]);
    for (int i = -n+1; i <= n-1; ++i) dz.add(2*n-1 + (i+n-1), snk, val2[i+shift]);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            dz.add(i+j-2, 3*n-2 + i-j, 1);
        }
    }
    dz.max_flow(src, snk);
    vector<vector<int>> ans(n+1, vector<int>(n+1));
    for (int i = 2; i <= 2*n; ++i) {
        for (auto edg : dz.g[i-2]) {
            if (2*n-1 <= edg.to and edg.to < src and edg.flow == 1 and edg.res == 0) {
                int other = edg.to - 3*n+2;
                ans[(i+other)/2][(i-other)/2] = 1;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << ans[i][j] << " \n"[j==n];
        }
    }
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
