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

int par[maxn], lvl[maxn], h[maxn];
int findp(int u) {
	return par[u] = (par[u] == u ? u : findp(par[u]));
}
void merge(int u, int v) {
	if (lvl[u] < lvl[v]) swap(u, v);
	par[v] = u, h[u] = max(h[u], h[v]);
	if (lvl[u] == lvl[v]) lvl[u]++;
}

vector<ii> components[maxn];
void solve(){
 	int n; cin >> n;
	vector<ii> v(n);
	map<ii, int> exist;
	for (auto& [x, y] : v) cin >> x >> y;
	for (int i = 1; i <= n; ++i) exist[v[i-1]] = i, par[i] = i, h[i] = v[i-1].second;
	for (int i = 1; i <= n; ++i) {
		auto [x, y] = v[i-1];
		if (exist[make_pair(x-1, y+1)]) merge(i, exist[make_pair(x-1, y+1)]);
		if (exist[make_pair(x+1, y-1)]) merge(i, exist[make_pair(x+1, y-1)]);
	}
	for (int i = 1; i <= n; ++i) {
		cout << findp(i) << ' ';
		components[v[i-1].first].push_back({v[i-1].second, h[findp(i)]});	
	}
	cout << endl;
	int ans = 0;
	for (int i = 0; i <= 200000; ++i) {
		sort(all(components[i]));
		int mxH = 0;
		for (auto [lx, rx] : components[i]) {
			ckmax(mxH, lx);
			ans += max(0ll, mxH - rx+1);
			ckmax(mxH, rx+1);
		}
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
