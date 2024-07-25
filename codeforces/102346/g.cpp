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

const int Inf = 1e8+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

template<typename T> struct mcmf {
	struct edge {
		int to, rev, flow, cap;
		bool res;
		T cost;
		edge() : to(0), rev(0), flow(0), cap(0), cost(0), res(false) {}
		edge(int to_, int rev_, int flow_, int cap_, T cost_, bool res_) : to(to_), rev(rev_), flow(flow_), cap(cap_), res(res_), cost(cost_) {}

	};

	vector<vector<edge>> g;
	vector<int> par_idx, par;
	T inf;
	vector<T> dist;

	mcmf(int n) : g(n), par_idx(n), par(n), inf(numeric_limits<T>::max()/3) {}
	
	void add(int u, int v, int w, T cost) {
		edge a = edge(v, g[v].size(), 0, w, cost, false);
		edge b = edge(u, g[u].size(), 0, 0, -cost, true);
		
		g[u].push_back(a);
		g[v].push_back(b);
	}

	vector<T> spfa(int s) {
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
			auto [d,v ] = q.top();
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

	pair<int, T> min_cost_flow(int s, int t, int flow = Inf) {
		vector<T> pot(g.size(), 0);
		pot = spfa(s);
		int f = 0;
		T ret = 0;
		while (f < flow and dijkstra(s, t, pot)) {
			for (int i = 0; i < g.size(); ++i) 
				if (dist[i] < inf) pot[i] += dist[i];

			int mn_flow = flow - f, u = t;
			while (u != s) {
				mn_flow = min(mn_flow, g[par[u]][par_idx[u]].cap - g[par[u]][par_idx[u]].flow);
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

	vector<pair<int, int>> recover() {
		vector<pair<int, int>> used;
		for (int i = 0; i < g.size(); i++) for (edge e : g[i])
				if (e.flow == e.cap && !e.res) used.push_back({i, e.to});
		return used;
	}
};	

using ld = long double;

void solve(){
 	int n; cin >> n;
	vector<vector<ld>> a(n, vector<ld>(n));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			int x; cin >> x;
			a[i][j] = log(x);
		}
	}
	// vertices vao pra prateleiras
	int src = 2*n, sink = 2*n+1;
	mcmf<ld> fluxo(2*n+5);
	for (int i = 0; i < n; ++i) {
		fluxo.add(src, i, 1, 0);
		fluxo.add(i+n, sink, 1, 0);
		for (int j = 0; j < n; ++j) fluxo.add(i, j+n, 1, -a[i][j]);
	}
	fluxo.min_cost_flow(src, sink);
	auto v = fluxo.recover();
	vector<int> p(n);
	for (auto [x, y] : v) {
		if (max(x, y) < src) {
			p[max(x, y) - n] = min(x, y);
		}
	}
	for (auto x : p) cout << x + 1 << ' ';
	cout << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
