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

vector<int> g[maxn];

int vis[maxn], dp1[maxn], dp2[maxn];

vector<int> comp;

void dfs1(int u, int p) {
	comp.pb(u);
	vis[u] = comp[0];
	for (auto v : g[u]) {
		if (v == p) continue;
		dfs1(v, u);
		ckmax(dp1[u], dp1[v] + 1);
	}
}

void dfs2(int u, int p) {
	ii best = {0, 0};
	int reserva = 0;
	for (auto v : g[u]) {
		if (v == p) continue;
		if (dp1[v] + 2 > reserva) {
			if (dp1[v] + 2 >= best.first) reserva = best.first, best = {dp1[v] + 2, v};
			else reserva = dp1[v] + 2;
		}
	}
	for (auto v : g[u]) {
		if (v == p) continue;
		if (v == best.second) dp2[v] = max(dp2[u]+1, reserva);
		else dp2[v] = max(dp2[u]+1, best.first);
		dfs2(v, u);
	}
}
vector<int> vals[maxn];
vector<ii> sufixos[maxn];
void preprocess(int u) {
	comp.clear();
	dfs1(u, u), dfs2(u, u);
	for (auto v : comp) vals[u].pb(max(dp1[v], dp2[v]));
	sort(all(vals[u])), reverse(all(vals[u])), vals[u].pb(-1);
	int s = 0, cur = vals[u][0], foi = 0;
	for (auto x : vals[u]) {
		if (x != cur) s += foi, sufixos[u].pb({cur, s});
		assert(x == -1 || x + 1 >= cur);
		foi++;
		cur = x;
	}
	vals[u].pop_back();
	reverse(all(vals[u]));
	reverse(all(sufixos[u]));
}
void solve(){
 	int n, m, q; cin >> n >> m >> q;
	for (int i = 1; i <= m; ++i) {
		int u, v; cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	for (int i = 1; i <= n; ++i) {
		if (!vis[i]) preprocess(i);
	}
	map<ii, double> answer;
	// me parece muito O(nsqrtn) isso aqui, confiar :pray:
	while (q--) {
		int u, v; cin >> u >> v;
		u = vis[u], v = vis[v];
		if (u == v) {
			cout << -1 << endl;
			continue;
		}
		if (sz(vals[u]) > sz(vals[v])) swap(u, v);
		if (!answer.count(make_pair(u, v))) {
			int q1 = sz(vals[u]), q2 = sz(vals[v]);
			int min_diam = max(sufixos[u].back().first, sufixos[v].back().first);
			int st = lower_bound(all(sufixos[v]), make_pair(min_diam-vals[u][0], 0ll)) - begin(sufixos[v]);
			int tot = 0;
			for (auto x : vals[u]) {
				// te garanto que vou andar com st O(sz(sufixos[u])) vezes (se isso n for verdade eu tomei no cu)
				// a intuicao por tras eh q a freq das dist maximas eh um bagulho continuo. n faz nem um pouco sentido
				// disso pular de x -> x + 2. eu acredito q st anda no maximo 1 vez por iteracao
				while (st && sufixos[v][st-1].first+x >= min_diam) st--;
				if (st == sz(sufixos[v])) continue;
				int plus = sufixos[v][st].first-(min_diam-x);
				assert(sufixos[v][st].first+x >= min_diam);
				tot += sufixos[v][st].second + plus*q2;
			}
			answer[make_pair(u, v)] = min_diam + tot/(double)(q1*q2);
			cout << fixed << setprecision(10) << answer[make_pair(u, v)] << endl;
		} else cout << fixed << setprecision(10) << answer[make_pair(u, v)] << endl;
	}
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
