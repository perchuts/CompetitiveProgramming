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

vector<int> g[maxn];
// 2-SAT
//
// solve() retorna um par, o first fala se eh possivel
// atribuir, o second fala se cada variavel eh verdadeira
//
// O(|V|+|E|) = O(#variaveis + #restricoes)

struct sat {
	int n, tot;
	vector<vector<int>> g;
	vector<int> vis, comp, id, ans;
	stack<int> s;

	sat() {}
	sat(int n_) : n(n_), tot(n), g(2*n) {}

	int dfs(int i, int& t) {
		int lo = id[i] = t++;
		s.push(i), vis[i] = 2;
		for (int j : g[i]) {
			if (!vis[j]) lo = min(lo, dfs(j, t));
			else if (vis[j] == 2) lo = min(lo, id[j]);
		}
		if (lo == id[i]) while (1) {
			int u = s.top(); s.pop();
			vis[u] = 1, comp[u] = i;
			if ((u>>1) < n and ans[u>>1] == -1) ans[u>>1] = ~u&1;
			if (u == i) break;
		}
		return lo;
	}

	void add_impl(int x, int y) { // x -> y = !x ou y
		x = x >= 0 ? 2*x : -2*x-1;
		y = y >= 0 ? 2*y : -2*y-1;
		g[x].push_back(y);
		g[y^1].push_back(x^1);
	}

	pair<bool, vector<int>> solve() {
		ans = vector<int>(n, -1);
		int t = 0;
		vis = comp = id = vector<int>(2*tot, 0);
		for (int i = 0; i < 2*tot; i++) if (!vis[i]) dfs(i, t);
		for (int i = 0; i < tot; i++)
			if (comp[2*i] == comp[2*i+1]) return {false, {}};
		return {true, ans};
	}
};

void solve(){
	int n; cin >> n;
	for (int i = 0; i < 2*n; ++i) g[i].clear();
	vector<int> c(2*n), par(2*n);
	vector<vector<int>> color(n);
	for (int i = 0; i < 2 * n; ++i) {
		cin >> c[i];
		--c[i];
		color[c[i]].pb(i);
	}
	for (int i = 0; i < 2*n-1; ++i) {
		int u, v; cin >> u >> v;
		--u, --v;
		cout.flush();
		g[u].pb(v), g[v].pb(u);
	}
	vector<int> subt(2*n);
	auto pre = [&] (auto&& self, int u, int p) -> void {
		subt[u] = 0, par[u] = p;
		for (auto v : g[u]) {
			if (v == p) continue;
			self(self, v, u);
			subt[u] += subt[v];
		}
		subt[u]++;
	};
	pre(pre, 0, 0);
	auto find_centroid = [&] (auto&& self, int u, int p) -> int {
		for (auto v : g[u]) {
			if (v == p) continue;
			if (subt[v] * 2 > 2*n) return self(self, v, u);
		}
		return u;
	};
	int ct = find_centroid(find_centroid, 0, 0);
	pre(pre, ct, ct);
	for (auto v : g[ct]) {
		if (subt[v] * 2 == n) {
			vector<int> cc(n), ans;
			queue<int> q;
			cc[c[v]] = 1;
			q.push(v);
			while (!q.empty()) {
				int u = q.front();
				q.pop();
				ans.pb(u);
				for (auto w : g[u]) {
					if (cc[c[w]]) continue;
					cc[c[w]] = 1;
					q.push(w);
				}
			}
			if (sz(ans) == n) {
				for (auto x : ans) cout << x+1 << ' ';
				cout << endl;
				return;
			}
		}
	}
	sat S(2*n);
	for (int i = 0; i < 2*n; ++i) {
		for (int j = 0; i < n && j < 2; ++j) {
			S.add_impl(color[i][j], ~color[i][j^1]);
			S.add_impl(~color[i][j], color[i][j^1]);
		}
		S.add_impl(i, par[i]);
	}
	auto [consegue, ans] = S.solve();
	if (!consegue) {
		cout << -1 << endl;
		return;
	}
	for (int i = 0; i < 2 * n; ++i) if (ans[i]) cout << i+1 << ' ';
	cout << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
