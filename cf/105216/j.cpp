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
	int n, m; cin >> n >> m;
	vector<vector<int>> edg(n, vector<int>(n));
	for (int i = 0; i < m; ++i) {
		int u, v; cin >> u >> v;
		--u, --v;
		edg[u][v] = edg[v][u] = 1;
	}
	if (n == 1) {
		cout << "NO" << endl;
		return;
	}
	vector<ii> tot;
	for (int i = 0; i < n/2; ++i) for (int j = i+1; j < n/2; ++j) if (edg[i][j] == 0) tot.pb({i, j});
	for (int i = n/2; i < n; ++i) for (int j = i+1; j < n; ++j) if (edg[i][j] == 0) tot.pb({i, j});
	cout << "YES" << endl;
	cout << sz(tot) << endl;
	for (auto [x, y] : tot) cout << x+1 << ' ' << y+1 << endl;
}		

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
