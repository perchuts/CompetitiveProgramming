#include <bits/stdc++.h>
#define pb push_back
using namespace std;

#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define int long long
typedef long long ll;

mt19937 rng(69);

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

int32_t main() {
	fast_io;
	int n, d; cin >> d >> n;
	vector<vector<vector<pair<int, int>>>> g(d);
	vector<vector<tuple<int, int, int>>> edges(d);
	for (int i = 0; i < d; ++i) {
		g[i].resize(n);
		for (int j = 0; j < n-1; ++j) {
			int u, v, w; cin >> u >> v >> w;
			--u, --v;
			edges[i].push_back({w, u, v});
			g[i][u].pb({v, w});
			g[i][v].pb({u, w});
		}
	}
	const int lim = 998244300;
	int sexo = rnd(1, lim);
	vector<int> primes = {998244353, 998244853, 1000000007};
	if (n <= d) {
		vector<vector<int>> f(n, vector<int>(n));
		map<vector<int>, int> occ;
		for (int i = 0; i < d; ++i) {
			// computa a lista de distancias
			auto dfs = [&] (auto&& self, int src, int u, int p, int val) -> void {
				f[src][u] = val;
				for (auto [v, w] : g[i][u]) {
					if (v == p) continue;
					self(self, src, v, u, min(val, w));
				}
			};
			for (int j = 0; j < n; ++j) dfs(dfs, j, j, j, 1e9+10);
			vector<int> eu;
			for (int j = 0; j < primes.size(); ++j) {
				int pp = 1, s = 0;
				for (int a = 0; a < n; ++a) {
					for (int b = a + 1; b < n; ++b) {
						s = (s + pp * f[a][b]) % primes[j];
						pp = pp * sexo % primes[j];
					}
				}
				eu.push_back(s);
			}
			if (!occ.count(eu)) occ[eu] = i;
			cout << occ[eu] + 1 << ' ';
		}
		cout << endl;
	} else {
		vector<int> label(n);
		for (int i = 0; i < n; ++i) label[i] = rnd(1, lim);
		map<pair<int, int>, int> occ;
		vector<int> mvkaio(d);
		vector<set<int>> caras(d);
		for (int cc = 0; cc < d; ++cc) {
			sort(rbegin(edges[cc]), rend(edges[cc]));
			vector<int> par(n), comp = label, lvl(n);
			iota(begin(par), end(par), 0);
			auto fexp = [] (int b, int e, int m) {
				int ans = 1;
				while (e) {
					if (e&1) ans = ans * b % m;
					e /= 2, b = b * b % m;
				}
				return ans;
			};
			auto findp = [&] (auto&& self, int u) -> int {
				return par[u] = (par[u] == u ? u : self(self, par[u]));
			};
			vector<int> vals;
			for (int j = 0; j < primes.size(); ++j) {
				int cur = 1;
				for (int i = 0; i < n; ++i) cur = cur * comp[i] % primes[j];
				vals.push_back(cur);
			}
			auto merge = [&] (int u, int v) {
				u = findp(findp, u);
				v = findp(findp, v);
				if (lvl[u] < lvl[v]) swap(u, v);
				int novo = comp[u] + comp[v];
				int A = comp[u], B = comp[v];
				for (int i = 0; i < primes.size(); ++i) {
					vals[i] = vals[i] * fexp(A % primes[i], primes[i]-2, primes[i]) % primes[i];
					vals[i] = vals[i] * fexp(B % primes[i], primes[i]-2, primes[i]) % primes[i];
					vals[i] = vals[i] * (novo % primes[i]) % primes[i];
				}
				comp[u] = novo;
				par[v] = u;
				if (lvl[u] == lvl[v]) lvl[u]++;
			};
			vector<int> bichos;
			int sexo2 = rnd(1, primes[0] - 5);
			int eu = 0, pp = 1, pp2 = 1;
			for (int l = 0, r = 0; l < n-1; l = r) {
				while (r != n-1 and get<0>(edges[cc][r]) == get<0>(edges[cc][l])) {
					auto [w, u, v] = edges[cc][r++];
					merge(u, v);
				}
				int s = 0;
				for (auto x : vals) s += x;
				eu = (eu + pp * s) % primes[0];
				pp = pp * sexo % primes[0];	
				caras[cc].insert(get<0>(edges[cc][l]));
			}
			mvkaio[cc] = eu;
			for (int i = 0; ; ++i) {
				if (mvkaio[i] == mvkaio[cc] and caras[i] == caras[cc]) {
					cout << i + 1 << ' ';
					break;
				}
			}
		}
		cout << endl;
	}
}

