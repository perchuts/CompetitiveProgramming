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

void solve(){
	ll n, m, c; cin >> n >> m >> c;
	vector<ii> edgs;
	vector<vector<int>> g(n);
	for (int i = 1; i <= m; ++i) {
		int u, v; cin >> u >> v;
		--u, --v;
		g[u].pb(v), g[v].pb(u);
	}
	vector<int> dp(n), h(n), subt(n);
	vector<vector<ii>> tipos;
	auto dfs = [&] (auto&& dfs, int u, int p) -> void {
			h[u] = 1 + h[p], subt[u] = 1;
			for (auto v : g[u]) {
				if (h[v] == 0) dfs(dfs, v, u), subt[u] += subt[v], dp[u] += dp[v];
				else if (h[v] > h[u]) dp[u]--;
				else dp[u]++;
			}
			dp[u]--;
			if (u != p and dp[u] == 0) {
				// caso ponte	
				tipos.back().pb({subt[u], 0});
			} 
			if (u == p) {
				// caso raiz da arvore
				for (auto& [a, b] : tipos.back()) b = subt[u] - a; 
				tipos.back().pb({subt[u], 0});
			}
	};
	// tipo do cara, quantos tem pra um lado, quantos tem pro outro lado 
	for (int i = 0; i < n; ++i) {
		if (h[i]) continue;
		tipos.pb({});
		dfs(dfs, i, i);
	}
	if (sz(tipos) == 1 and sz(tipos[0]) == 1) {
		// se e somente se!
		cout << -1 << endl;
		return;
	}
	// fazer 12 trick para o caso onde nao uso nenhuma ponte!
	// sem usar ponte
	ll ans = 1e18, comps = sz(tipos);
	// agora usando alguma ponte do grafo original
	// fazer essa parte com bitset tambem
	bitset<100050> foi, naofoi;
	naofoi[0] = foi[0] = 1;
	vector<int> mark(n+1);
	for (auto v : tipos) {
		int tam = -1;
		for (auto [x, y] : v) {
			if (y == 0) tam = x; 
			else mark[x] = mark[y] = 1;
		}
		assert(tam != -1);
		naofoi |= (naofoi << tam);
		foi    |= (foi    << tam);
		for (int i = 1; i < tam; ++i) {
			if (mark[i] == 0) continue;
			mark[i] = 0;
			foi |= (naofoi << i);	
		}
	}
	for (ll i = 1; i < n; ++i) {
		if (foi[i] == 0) continue;
		ckmin(ans, i * i + (n-i) * (n-i) + c * (comps-1)); 
	}
	cout << ans << endl;
}
int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
