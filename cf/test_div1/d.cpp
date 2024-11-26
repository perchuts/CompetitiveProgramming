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
	int n, k; cin >> n >> k;
	vector<vector<int>> tipo(2, vector<int>(n));
	vector<vector<vector<int>>> g(2, vector<vector<int>>(n, vector<int>()));
	vector<int> m(2);
	int s = 0;
	for (int a = 0; a < 2; ++a) {
		for (auto& x : tipo[a]) cin >> x, s += x;
		cin >> m[a];
		for (int i = 0; i < m[a]; ++i) {
			int u, v; cin >> u >> v;
			--u, --v;
			g[a][u].pb(v), g[a][v].pb(u);
		}
	}
	if (s != n) {
		cout << "NO" << endl;
		return;
	}
	bool ok = 1;
	for (int i = 0; i < n; ++i) ok &= (tipo[0][i] == tipo[0][0]);
	if (ok) {
		cout << "YES" << endl;
		return;
	}

}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
