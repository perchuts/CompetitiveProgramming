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

void solve(){
 	int n, w; cin >> n >> w;
	vector<int> p(n), eh_consec(n);
	vector<vector<int>> g(n);
	int consec = 0;
	for (int i = 1; i < n; ++i) {
		cin >> p[i]; --p[i];
		if ((i + 1) % n == p[i] || (p[i] + 1) % n == i) eh_consec[i] = 1;
		g[p[i]].pb(i), g[i].pb(p[i]);
	}	
	vector<int> qnt(n), precisa(n), totw(n);
	vector<vector<ii>> dono(n);
	auto dfs = [&] (auto&& self, int u, int pp) -> void {
		bool ok = 0, leaf = 1;
		for (auto v : g[u]) {
			if (v == (u + 1) % n) ok = 1, consec++;
			if (v == pp) continue;
			leaf = 0;
			self(self, v, u);
		}
		for (auto v : g[u]) {
			if (v == pp) continue;
			for (auto [a, b] : dono[v]) {
				if (b != u) dono[u].pb({a, b});
			}
		}
		if (!ok) {
			assert(leaf);
			dono[u].pb({u, p[(u+1)%n]});
			if (u != n-1) dono[(u+1)%n].pb({u, p[(u+1)%n]});
		}
	};
	dfs(dfs, 0, 0);
	for (int i = 0; i < n; ++i) {
		//cout << i << ": ";
		for (auto [a, b] : dono[i]) {
			//cout << a << ' ';
			precisa[a]++;
		}
		//cout << endl;
		qnt[i] = sz(dono[i]);
	}
	int ans = n * w, sum = 0, ruins = n - consec;
	
	for (int i = 0; i < n - 1; ++i) {
		int x, y; cin >> x >> y;
		--x;
		// pros consecutivos, eh isso que muda!
		if (eh_consec[x]) {
			if ((x+1)%n == p[x]) consec--, ans -= (w-sum), ans += y;
			if ((p[x]+1)%n == x) consec--, ans -= (w-sum), ans += y;
		}
		ans -= consec * (w-sum);
		sum += y;
		ans += consec * (w-sum);
		for (auto [a, b] : dono[x]) {
			precisa[a]--, totw[a] += y;
			if (precisa[a] == 0) {
				ans -= w - (sum-totw[a]), ans += totw[a], ruins--, qnt[x]--;
			}
		}
		ans -= y * (ruins-qnt[x]);
		// pros nao consecutivos, vai mudar em -y pra aqueles onde o caminho n cruza a aresta x
		cout << ans << ' ';
	}
	cout << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
