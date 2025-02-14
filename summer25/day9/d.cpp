#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
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
	return l + rand() % (r-l+1);
}

int solve(int n, int m, int k, vector<ii> edg, int l, vector<int> want, int b, vector<int> gas) {
	vector<vector<int>> g(n);
	for (auto& [u, v] : edg) {
		cout.flush();
		--u, --v, g[u].pb(v), g[v].pb(u);
	}
	for (auto& x : want) --x;
	for (auto& x : gas) --x;
	vector<vector<int>> dist(n, vector<int>(n));
	auto get_dist = [&] (int src) {
		queue<int> q;
		dist[src] = vector<int>(n, n+1);
		q.push(src);
		dist[src][src] = 0;
		while (!q.empty()) {
			auto u = q.front(); q.pop();
			for (auto v : g[u]) if (ckmin(dist[src][v], dist[src][u]+1)) dist[src][v] = dist[src][u] + 1, q.push(v);
		}
	};
	for (int i = 0; i < n; ++i) get_dist(i);
	vector<int> pref(l);
	for (int i = 1; i < l; ++i) pref[i] = pref[i-1] + dist[want[i]][want[i-1]];
	int ans = inf;
	if (pref.back() <= k) { return pref.back(); }
	vector<vector<int>> dp(b, vector<int>(l, ans));	
	vector<int> optimus_prime(n+1);
	for (int i = 0; i < l; ++i) {
		for (int j = 0; j < b; ++j) {
			if (pref[i] + dist[want[i]][gas[j]] <= k) {
				dp[j][i] = pref[i] + dist[want[i]][gas[j]];	
			}
		}
	}
	for (int j = 0; j < l-1; ++j) {
		priority_queue<ii, vector<ii>, greater<>> pq;
		for (int i = 0; i < b; ++i) {
			if (dp[i][j] < inf) pq.push({dp[i][j], i});
		}
		// posso me manter no mesmo nivel	
		while (!pq.empty()) {
			auto u = pq.top() pq.pop();
			for (int i = 0; i < b; ++i) {
						
			}
		}
		for (int i = 0; i < b; ++i) {
			int meu = pref[j] + dist[want[j]][gas[i]];
			if (meu > k) continue;
			ckmin(dp[i][j], meu + optimus_prime[k-meu]);
		}
		for (int i = 0; i < b; ++i) {
			int eu = -pref[j+1] + dist[want[j+1]][gas[i]];
			if (0 <= eu and eu <= n) ckmax(optimus_prime[eu], dp[i][j] + eu);
		}
	}
	for (int i = 0; i < b; ++i) for (int j = 0; j < l-1; ++j) {
		int custo = pref.back() - pref[j+1] + dist[gas[i]][want[j+1]];
		if (custo <= k) ckmin(ans, custo + dp[i][j]);	
	}
	//cout << "dist:" << endl;
	//for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cout << dist[i][j] << " \n"[j==n-1];
	cout << "dp:" << endl;
	for (int i = 0; i < b; ++i) for (int j = 0; j < l; ++j) cout << dp[i][j] << " \n"[j==l-1];
	return (ans == inf ? -1 : ans);
}

int brute(int n, int m, int k, vector<ii> edg, int l, vector<int> want, int b, vector<int> gas) {
	vector<vector<int>> g(n);
	for (auto& [x, y] : edg) --x, --y, g[x].pb(y), g[y].pb(x);
	for (auto& x : want) --x;
	for (auto& x : gas) --x;
	vector dist(n, vector(k+1, vector(l, inf)));
	vector vis(n, vector(k+1, vector(l, false)));
	dist[want[0]][k][0] = 0;
	deque<iii> q;
	q.push_front({want[0], k, 0});
	int ans = inf;
	vector<int> postinho(n);
	for (auto x : gas) postinho[x] = 1;
	while (!q.empty()) {
		auto [u, cap, foi] = q.front(); q.pop_front();
		if (foi == l-1) ckmin(ans, dist[u][cap][foi]);
		if (vis[u][cap][foi]) continue;
		vis[u][cap][foi] = 1;
		if (postinho[u] and ckmin(dist[u][k][foi], dist[u][cap][foi])) q.push_front({u, k, foi});
		if (foi != l-1 and want[foi+1] == u and ckmin(dist[u][cap][foi+1], dist[u][cap][foi])) q.push_front({u, cap, foi+1});
		if (cap == 0) continue;
		for (auto v : g[u]) if (ckmin(dist[v][cap-1][foi], dist[u][cap][foi]+1)) q.pb({v, cap-1, foi});
	}
	return (ans == inf ? -1 : ans);
}
// bfs comecando de cada gas station
// imagine que todas as cidades que preciso visitar sao um tipo de gas station
// entao temos uma DP bem simples: dp[want[i]] -> menor numero de reabastecidas pra chegar ate aqui
// olha pro i, j (transicoes do i pro j). simplesmente quero encontrar, pra cada K,
// o maior L tal que posso ir de DP[i][K] -> DP[j][L]+1.
// cost(L, R) >= cost(L+1, R)?
// cost(L, R) = (i -> L) + (R -> j) + (L->(L+1)->...->(R-1)->R) 
// cost(L, R) - cost(L+1, R) = (L->(L+1)) + (i -> L) - (i -> (L+1))
// por desigualdade triangular (pois claramente (->) se trata de uma funcao de distancia): (i -> (L+1)) <= (i -> L -> L+1)
// logo podemos fazer um one pointer pra cada par de coisas pra computar os pontos otimos de transicao.
int32_t main(){_
#ifndef gato
	int n, m, k; cin >> n >> m >> k;
	vector<ii> edg(m);
	for (auto& [x, y] : edg) cin >> x >> y;
	int l; cin >> l;
	vector<int> sexo(l);
	for (auto& x : sexo) cin >> x;
	int b; cin >> b;
	vector<int> postinho(b);
	for (auto& x : postinho) cin >> x;
	cout << solve(n, m, k, edg, l, sexo, b, postinho) << endl;
#else
	int t = 1;
	while (true) {
restart:
		srand(t++);
		int n = rnd(2, 6), m = rnd(n-1, 10), k = rnd(1, n);
		vector<ii> edg(m);
		map<ii, bool> foi;
		for (int i = 2; i <= n; ++i) {
			int j = rnd(1, i-1);
			foi[{i, j}] = foi[{j, i}] = 1;	
			edg[i-2] = {i, j};
		}
		for (int i = n-1; i < m; ++i) {
			auto& [x, y] = edg[i];
			x = rnd(1, n);
			y = rnd(1, n);
			while (y == x) y = rnd(1, n); 
			if (foi[{x, y}]) {
				cout << "Failed to generate test " << t-1 << endl;
				goto restart; 
			}
			assert(x != 0);
			foi[{x, y}] = foi[{y, x}] = 1;
		}
		int l = rnd(1, n);
		vector<int> sexo(n); iota(all(sexo), 1);
		random_shuffle(all(sexo));
		while (sz(sexo) != l) sexo.pop_back();
		int b = rnd(1, n);
		vector<int> postinho(n); iota(all(postinho), 1);
		random_shuffle(all(postinho));
		while (sz(postinho) != b) postinho.pop_back();
		int my = solve(n, m, k, edg, l, sexo, b, postinho);
		if (my == -2) { assert(false); }
		int opt = brute(n, m, k, edg, l, sexo, b, postinho); 
		if (my != opt) {
			cout << "Wrong answer on test " << t-1 << endl;
			cout << n << ' ' << m << ' ' << k << endl;
			for (auto [x, y] : edg) cout << x << ' ' << y << endl;
			cout << l << endl;
			for (auto x : sexo) cout << x << ' ';
			cout << endl;
			cout << b << endl;
			for (auto x : postinho) cout << x << ' ';
			cout << endl;
			cout << "Your output: " << my << endl;
			cout << "Answer: " << opt << endl;
			exit(0);
		}
		cout << "Accepted on test " << t-1 << endl;
	}
#endif
}
