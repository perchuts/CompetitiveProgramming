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
	int n, q; cin >> n >> q;
	int ans = n;
	vector<set<int>> g(n);
	while (q--) {
		int op; cin >> op;
		if (op == 1) {
			int u, v; cin >> u >> v;
			--u, --v;
			g[u].insert(v);
			g[v].insert(u);
			if (sz(g[u]) == 1) ans--;
			if (sz(g[v]) == 1) ans--;
		} else {
			int u; cin >> u;
			-- u;
			for (auto i : g[u]) {
				g[i].erase(u);
				if (g[i].empty()) ans++;
			}
			if (!g[u].empty()) ans++;
			g[u].clear();
		}
		cout << ans << endl;
	}
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
