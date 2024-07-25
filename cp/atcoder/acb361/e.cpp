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

vector<ii> g[maxn];
int dist[maxn];
void dfs(int u, int p) {
	for (auto [v, w] : g[u]) {
		if (v == p) continue;
		dist[v] = dist[u] + w;
		dfs(v, u);
	}
}

void solve(){
	int n; cin >> n;
	int ss = 0;
	for (int i = 1; i < n; ++i) {
		int a, b, c; cin >> a >> b >> c;
		ss += 2 * c;
		g[a].pb({b, c});
		g[b].pb({a, c});
	}
	dfs(1, 1);
	int big = 1, dd = 0;
	for (int i = 2; i <= n; ++i) if (ckmax(dd, dist[i])) big = i;
	for (int i = 1; i <= n; ++i) dist[i] = 0;
	dfs(big, big);
	for (int i = 1; i <= n; ++i) ckmax(dd, dist[i]);
	cout << ss - dd << endl;
	
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
