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
// Max flow com lower bound
// 
// add(a, b, l, r):
// 	adiciona aresta de a pra b, onde precisa passar f de fluxo, l <= f <= r
// add(a, b, c):
// 	adiciona aresta de a pra b com capacidade c
//
// Mesma complexidade do Dinitz
// Dinitz
//
// O(min(m * max_flow, n^2 m))
// Grafo com capacidades 1: O(min(m sqrt(m), m * n^(2/3)))
// Todo vertice tem grau de entrada ou saida 1: O(m sqrt(n))

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

	int f;
	T ret;
    pair<int, T> min_cost_flow(int s, int t) {
        vector<T> pot(g.size(), 0);
        pot = spfa(s); // mudar algoritmo de caminho minimo aqui

        while (dijkstra(s, t, pot)) {
            for (int i = 0; i < g.size(); i++)
                if (dist[i] < inf) pot[i] += dist[i];

            int mn_flow = INF, u = t;
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

struct lb_mcmf : mcmf<int> {
    vector<int> d;
    lb_mcmf(int n) : mcmf(n + 2), d(n, 0) {}
    void add(int a, int b, int c, int l, int r) {
        d[a] -= l;
        d[b] += l;
        mcmf::add(a, b, r - l, c);
    }
    void add(int a, int b, int c, int w) {
        mcmf::add(a, b, w, c);
    }
    bool has_circulation() {
        int n = d.size();

        ll cost = 0;
        for (int i = 0; i < n; i++) {
            if (d[i] > 0) {
                cost += d[i];
                mcmf::add(n, i, d[i], 0);
            } else if (d[i] < 0) {
                mcmf::add(i, n+1, -d[i], 0);
            }
        }
        int ret = mcmf::min_cost_flow(n, n+1).first;
        return (ret == cost);
    }
    bool has_flow(int src, int snk) {
        mcmf::add(snk, src, INF, 0);
        return has_circulation();
    }
    ii vrum_vrum(int src, int snk) {
        mcmf::ret = mcmf::f = 0;
        if (!has_flow(src, snk)) {
            //cout << "infeasible!" << endl;
            return {-1, -1};
        }
        return {mcmf::f, mcmf::ret};
    }
};

void solve() {
    int n; cin >> n;
    vector<int> x(n), y(n), val(n);
    for (int i = 0; i < n; ++i) cin >> x[i] >> y[i] >> val[i];
    int m; cin >> m;
    vector<tuple<char, int, int>> no(m);
    int mx_use = n;
    for (auto& [a, b, c] : no) {
        cin >> a >> b >> c;
        if (a == 'R' and b == 1) ckmin(mx_use, c);
        if (a == 'U' and b == 1) ckmin(mx_use, c);
    }
    int ans = 0;
    const int maxC = 100;
    for (int use = 1; use <= mx_use; ++use) {
        lb_mcmf fluxo(2*maxC+2);
        vector<array<int, 2>> h(maxC+1, {0, use}), v(maxC+1, {0, use});
        for (auto [a, b, c] : no) {
            if (a == 'R' and b == 1) continue;
            if (a == 'U' and b == 1) continue;
            if (a == 'L') h[b][1] = c;
            if (a == 'R' and c <= use) h[b-1][0] = use-c;
            if (a == 'U' and c <= use) v[b-1][0] = use-c;
            if (a == 'D') v[b][1] = c;
        }
		//cout << "use = " << use << endl;
        for (int i = 2; i <= maxC; ++i) {
            ckmax(h[i][0], h[i-1][0]);
            ckmax(v[i][0], v[i-1][0]);
        }
		for (int i = maxC-1; i >= 1; --i) {
            ckmin(h[i][1], h[i+1][1]);
            ckmin(v[i][1], v[i+1][1]);
		}
		//cout << "h: " << endl;
		//for (int i = 1; i <= maxC; ++i) {
		//	cout << h[i][0] << " " << h[i][1] << endl;
		//}
		//cout << endl;
		//cout << "v: " << endl;
		//for (int i = 1; i <= maxC; ++i) {
		//	cout << v[i][0] << " " << v[i][1] << endl;
		//}
        int src = 0, sink = 2*maxC+1;
        for (int i = maxC; i != 1; --i) fluxo.add(i, i-1, 0, h[i-1][0], h[i-1][1]);
        for (int i = 1; i != maxC; ++i) fluxo.add(maxC+i, maxC+i+1, 0, v[i][0], v[i][1]);
        fluxo.add(src, maxC, 0, use, use);
        fluxo.add(2*maxC, sink, 0, use, use);
        for (int i = 0; i < n; ++i) fluxo.add(x[i], maxC+y[i], -val[i], 0, 1);
        auto [f, c] = fluxo.vrum_vrum(src, sink); c *= -1;
        if (f == -1) continue;
		//cout << "fluxo: ";
		//cout << f << " " << c << endl;
        ckmax(ans, c);
    }
    cout << ans << endl;
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
