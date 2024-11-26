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

void solve(){
	int n; cin >> n;
	vector<vector<int>> g(n);
	for (int i = 0; i < n-1; ++i) {
		int u, v; cin >> u >> v;
		--u, --v;
		g[u].pb(v), g[v].pb(u);
	}
	vector<int> deg(n), vis(n), par(n);
	vector<int> prox, rem;
	for (auto x : g[0]) prox.pb(x), par[x] = 0;
	int ans = n-1, cur = 0;
	deg[0] = sz(g[0]);
	for (int i = 1; i < n; ++i) {
		vector<int> nprox, nrem;
		//cout << "Rem: ";
		for (auto x : rem) {
			//cout << x << ' ';
			while (x) {
				deg[par[x]]--;
				cur--;
				if (deg[par[x]]) break;
				x = par[x];
			}
		}
		//cout << endl;
		//cout << "prox: ";
		for (auto x : prox) {
			//cout << x << ' ';
			cur++;
			for (auto y : g[x]) {
				if (y == par[x]) continue;
				nprox.pb(y), par[y] = x;
				deg[x]++;
			}
			if (deg[x] == 0) nrem.pb(x);
		}
		swap(nrem, rem), swap(prox, nprox);
		ckmin(ans, n-1-cur);
		//cout << endl;
		//cout << "final score: " << cur << endl;
	}
	//cout << endl;
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
