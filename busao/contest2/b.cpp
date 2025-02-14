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
	// 00110
	// 00111
	int n, m; cin >> n >> m;
	vector<int> val(n), viz(n);
	vector<vector<int>> g(n);
	for (auto& x : val) cin >> x;
	for (int i = 0; i < m; ++i) {
		int u, v; cin >> u >> v;
		--u, --v;
		g[u].push_back(v), g[v].push_back(u);
	}
	vector<vector<pair<int, bool>>> bl(n, vector<pair<int, bool>>(20, make_pair(-1, false)));
	auto check_cycle = [&] (auto&& self, int u, int p) -> void {
		if (u != p) {
			for (int i = 0; i < 20; ++i) {
				if (i == 0) {
					bl[u][0].second = (val[u] == val[p]);
				}
				int pp = bl[u][i-1].first;
				if (bl[pp][i-1].first == -1) break;
				bl[u][i].first = bl[pp][i-1].first;
			}
		}
		for (auto v : g[u]) {

		}
	};
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
