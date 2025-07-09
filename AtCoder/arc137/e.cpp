#include <bits/stdc++.h>
// Otimizacoes agressivas, pode deixar mais rapido ou mais devagar
#pragma GCC optimize("Ofast")
// Auto explicativo
#pragma GCC optimize("unroll-loops")
// Vetorizacao
#pragma GCC target("avx2")
//#define gato
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
// MinCostMaxFlow
//
// min_cost_flow(s, t, f) computa o par (fluxo, custo)
// com max(fluxo) <= f que tenha min(custo)
// min_cost_flow(s, t) -> Fluxo maximo de custo minimo de s pra t
// Se for um dag, da pra substituir o SPFA por uma DP pra nao
// pagar O(nm) no comeco
// Se nao tiver aresta com custo negativo, nao precisa do SPFA
//
// O(nm + f * m log n)
const int INF = inf;
template<typename T> struct mcmf {
	struct edge {
		int to, rev, flow, cap; // para, id da reversa, fluxo, capacidade
		bool res; // se eh reversa
		T cost; // custo da unidade de fluxo
		edge() : to(0), rev(0), flow(0), cap(0), cost(0), res(false) {}
		edge(int to_, int rev_, int flow_, int cap_, T cost_, bool res_)
			: to(to_), rev(rev_), flow(flow_), cap(cap_), res(res_), cost(cost_) {}
	};

	vector<vector<edge>> g;
	vector<int> par_idx, par;
	T inf;
	vector<T> dist;

	mcmf(int n) : g(n), par_idx(n), par(n), inf(numeric_limits<T>::max()/3) {}

	void add(int u, int v, int w, T cost) { // de u pra v com cap w e custo cost
		edge a = edge(v, g[v].size(), 0, w, cost, false);
		edge b = edge(u, g[u].size(), 0, 0, -cost, true);

		g[u].push_back(a);
		g[v].push_back(b);
	}

	vector<T> spfa(int s) { // nao precisa se nao tiver custo negativo
		deque<int> q;
		vector<bool> is_inside(g.size(), 0);
		dist = vector<T>(g.size(), inf);

		dist[s] = 0;
		q.push_back(s);
		is_inside[s] = true;

		while (!q.empty()) {
			int v = q.front();
			q.pop_front();
			is_inside[v] = false;

			for (int i = 0; i < g[v].size(); i++) {
				auto [to, rev, flow, cap, res, cost] = g[v][i];
				if (flow < cap and dist[v] + cost < dist[to]) {
					dist[to] = dist[v] + cost;

					if (is_inside[to]) continue;
					if (!q.empty() and dist[to] > dist[q.front()]) q.push_back(to);
					else q.push_front(to);
					is_inside[to] = true;
				}
			}
		}
		return dist;
	}
	bool dijkstra(int s, int t, vector<T>& pot) {
		priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> q;
		dist = vector<T>(g.size(), inf);
		dist[s] = 0;
		q.emplace(0, s);
		while (q.size()) {
			auto [d, v] = q.top();
			q.pop();
			if (dist[v] < d) continue;
			for (int i = 0; i < g[v].size(); i++) {
				auto [to, rev, flow, cap, res, cost] = g[v][i];
				cost += pot[v] - pot[to];
				if (flow < cap and dist[v] + cost < dist[to]) {
					dist[to] = dist[v] + cost;
					q.emplace(dist[to], to);
					par_idx[to] = i, par[to] = v;
				}
			}
		}
		return dist[t] < inf;
	}

	pair<int, T> min_cost_flow(int s, int t, int flow = INF) {
		vector<T> pot(g.size(), 0);
		pot = spfa(s); // mudar algoritmo de caminho minimo aqui
		int f = 0;
		T ret = 0;
		while (f < flow and dijkstra(s, t, pot)) {
			for (int i = 0; i < g.size(); i++)
				if (dist[i] < inf) pot[i] += dist[i];

			int mn_flow = flow - f, u = t;
			while (u != s){
				mn_flow = min(mn_flow,
					g[par[u]][par_idx[u]].cap - g[par[u]][par_idx[u]].flow);
				u = par[u];
			}

			ret += pot[t] * mn_flow;

			u = t;
			while (u != s) {
				g[par[u]][par_idx[u]].flow += mn_flow;
				g[u][g[par[u]][par_idx[u]].rev].flow -= mn_flow;
				u = par[u];
			}

			f += mn_flow;
		}

		return make_pair(f, ret);
	}
};

int solve(int n, int m, int d, vector<int> a, vector<int> l, vector<int> r, vector<int> c) {
    mcmf<int> fl(n+2);
    int tot = 0;
    for (int i = 0; i < m; ++i) {
        fl.add(l[i]-1, r[i], 1, c[i]);
    }
    for (int i = 0; i < n; ++i) {
        tot += a[i];
        fl.add(i, i+1, a[i], d);
        fl.add(i, i+1, m-a[i], 0);
    }
    fl.add(n+1, 0, m, 0);
    auto [x, y] = fl.min_cost_flow(n+1, n);
    return tot*d-y;
}
int32_t main() {_
#ifndef gato
    int n, m, d; cin >> n >> m >> d;
    vector<int> a(n), l(m), r(m), c(m);
    for (auto& x : a) cin >> x;
    for (int i = 0; i < m; ++i) cin >> l[i] >> r[i] >> c[i];
    cout << solve(n, m, d, a, l, r, c) << endl;
#else
    int t = 1;
    auto start = chrono::steady_clock::now();
    auto get_time = [&]() {
        auto curr = chrono::steady_clock::now();
        return int32_t(chrono::duration_cast<chrono::milliseconds>(curr - start).count());
    };
    while (true) {
        int n = rnd(1, 2000), m = rnd(1, 2000), d = rnd(1, 1e9);
        vector<int> a(n), l(m), r(m), c(m);
        for (auto& x : a) x = rnd(1, m);
        for (int i = 0; i < m; ++i) {
            l[i] = rnd(0, n-1), r[i] = rnd(l[i], n-1);
            c[i] = rnd(1, 1e9);
        }
        int ans = dual(n, m, d, a, l, r, c);
        cout << get_time() << endl;
        exit(0);
        //int my = solve(n, m, d, a, l, r, c), ans = dual(n, m, d, a, l, r, c);
        //if (ans != my) {
        //    cout << "Wrong answer on test " << t << endl;
        //    cout << n << ' ' << m << ' ' << d << endl;
        //    for (auto x : a) cout << x << ' ';
        //    cout << endl;
        //    for (int i = 0; i < m; ++i) cout << l[i] + 1 << ' ' << r[i] + 1 << ' ' << c[i] << endl;
        //    cout << "Your output: " << my << endl;
        //    cout << "Answer: " << ans << endl;
        //    exit(0);
        //}
        //cout << "Accepted on test " << t++ << endl;
    }
#endif
}
