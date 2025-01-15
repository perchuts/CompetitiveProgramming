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
	int h, w, m; cin >> h >> w >> m;
	vector<iii> ops(m);
	for (auto& [x, y, z] : ops) cin >> x >> y >> z;
	reverse(all(ops));
	map<int, int> ans, row, col;
	for (auto [t, a, c] : ops) {
		if (t == 1) {
			if (row[a]) continue;
			ans[c] += w - sz(col);
			row[a] = 1;
		} else {
			if (col[a]) continue;
			ans[c] += h - sz(row);
			col[a] = 1;
		}
	}
	int q0 = h*w;
	for (auto [x, y] : ans) if (x) q0 -= y;
	ans[0] = q0;
	vector<ii> resp;
	for (auto [x, y] : ans) if (y != 0) resp.pb({x, y});
	cout << sz(resp) << endl;
	for (auto [x, y] : resp) cout << x << ' ' << y << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
