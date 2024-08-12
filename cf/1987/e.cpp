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

vector<int> g[maxn];
int a[maxn], ans, dep[maxn], upd[maxn];

int update(int u) {
	int total = upd[u];
	for (auto v : g[u]) total += update(v);
	a[u] += total, upd[u] = 0;
	return total;
}

void solve(int u) {
	if (sz(g[u]) == 0) return;
	int tot = 0;
	for (auto v : g[u]) dep[v] = dep[u] + 1, solve(v), tot += a[v];
	queue<int> q;
	for (auto v : g[u]) q.push(v);
	while (a[u] > tot) {
		int v = q.front();	
		q.pop();
		if (sz(g[v]) == 0) {
			upd[v] += (a[u] - tot);
			ans += (dep[v] - dep[u]) * (a[u] - tot);
			break;
		}
		int tot2 = 0;
		for (auto w : g[v]) {
			tot2 += a[w];	
			q.push(w);
		}
		assert(tot2 >= a[v]);
		int consigo = min(a[u] - tot, tot2 - a[v]);
		ans += consigo * (dep[v] - dep[u]), tot += consigo; 
		upd[v] += consigo;
	}
	for (auto v : g[u]) update(v);
}	
void solve(){
	int n; cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i], upd[i] = 0;
	for (int i = 1; i < n; ++i) {
		int x; cin >> x;
		g[x].pb(i+1);
	}
	solve(1);
	cout << ans << endl;
	for (int i = 1; i <= n; ++i) g[i].clear();
	ans = 0;
}

int32_t main(){_
  int t; cin >> t;
  while(t--) solve();
}
