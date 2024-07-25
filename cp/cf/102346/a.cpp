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

int par[maxn], lvl[maxn];
int findp(int u) { return par[u] = (par[u] == u ? u : findp(par[u])); }
void merge(int u, int v) {
	u = findp(u), v = findp(v);
	if (u == v) return;
	if (lvl[u] < lvl[v]) swap(u, v);
	par[v] = u;
	if (lvl[u] == lvl[v]) lvl[u]++;
}

void solve(){
	int m, n, k; cin >> m >> n >> k;
	vector<iii> v(k);
	for (auto& [x, y, z] : v) cin >> x >> y >> z;
	for (int i = 0; i <= k + 10; ++i) par[i] = i;
	auto dist = [&] (int x1, int y1, int x2, int y2) {
		return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
	};
	for (int i = 0; i < k; ++i) {
		auto [x1, y1, r1] = v[i];
		for (int j = i + 1; j < k; ++j) {
			auto [x2, y2, r2] = v[j];
			if (dist(x1, y1, x2, y2) <= r1*r1+r2*r2+2*r1*r2) merge(i, j);
		}
		if (dist(x1, y1, 0, y1) <= r1*r1) merge(i, k);
		if (dist(x1, y1, x1, n) <= r1*r1) merge(i, k+1);
		if (dist(x1, y1, m, y1) <= r1*r1) merge(i, k+2);
		if (dist(x1, y1, x1, 0) <= r1*r1) merge(i, k+3);
	}
	if (findp(k) == findp(k+3) || findp(k+1) == findp(k+2) || findp(k) == findp(k+2) || findp(k+1) == findp(k+3)) cout << "N" << endl;
	else cout << "S" << endl;

}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
