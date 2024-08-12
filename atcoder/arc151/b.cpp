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
const int mod = 998244353;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

void solve(){
 	int n, m; cin >> n >> m;
	vector<int> p(n);
	for (auto& x : p) cin >> x, --x;
	if (m == 1) {
		cout << 0 << endl;
		return;
	}
	vector<int> par(n), lv(n); iota(all(par), 0);
	function<int(int)> findp = [&] (int u) {
		return par[u] = (par[u] == u ? u : findp(par[u]));
	};
	auto merge = [&] (int u, int v) {
		u = findp(u), v = findp(v);
		if (u == v) return false;
		if (lv[u] < lv[v]) swap(u, v);
		if (lv[u] == lv[v]) lv[u]++;
		par[v] = u;
		return true;
	};	
	int comps = n;
	vector<int> pt(n+1);
	pt[0] = 1;
	for (int i = 1; i <= n; ++i) pt[i] = pt[i-1] * m % mod;
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		if (findp(i) == findp(p[i])) {
			continue;
		} // faz o L, pra chegar aqui os dois vao ser iguais
		ans = (ans + pt[comps-2] * m % mod * (m-1) % mod * 499122177 % mod) % mod;
		merge(i, p[i]);
		comps--;
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
