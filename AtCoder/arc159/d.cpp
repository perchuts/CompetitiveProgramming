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
	int n; cin >> n;
	vector<ii> v(n);
	vector<int> cc;
	for (auto& [y, x] : v) cin >> x >> y, cc.pb(x), cc.pb(y);
	sort(all(cc));
	cc.erase(unique(all(cc)), end(cc));
	vector<ii> seg(8*n+1, make_pair(-1e18, -1e18));
	auto upd = [&] (auto&& upd, int i, int l, int r, int x, int a, int b) -> void {
		if (l == r) {
			ckmax(seg[i].first, a);
			ckmax(seg[i].second, b);
			return;
		}
		int md = (l + r) / 2;
		if (x <= md) upd(upd, 2*i, l, md, x, a, b);
		else upd(upd, 2*i+1, md+1, r, x, a, b);
		seg[i].first = max(seg[2*i].first, seg[2*i+1].first);
		seg[i].second = max(seg[2*i].second, seg[2*i+1].second);
	};
	auto query = [&] (auto&& query, int i, int l, int r, int x, int y) -> ii {
		if (x > y or y < l or r < x) return make_pair(-1e18, -1e18);
		if (x <= l and r <= y) return seg[i];
		int md = (l + r) / 2;
		auto pl = query(query, 2*i, l, md, x, y);
		auto pr = query(query, 2*i+1, md+1, r, x, y);
		return make_pair(max(pl.first, pr.first), max(pl.second, pr.second));
	};	
	int ans = 0;
	for (auto [r, l] : v) {
		int lx = lower_bound(all(cc), l) - begin(cc);
		int rx = lower_bound(all(cc), r) - begin(cc);
		// posso pegar um intervalo que termina antes de eu comecar!
		int my = max(r-l+1, query(query, 1, 0, 2*n-1, 0, lx-1).first + r-l+1);
		ckmax(my, query(query, 1, 0, 2*n-1, lx, rx).second + r);
		upd(upd, 1, 0, 2*n-1, rx, my, my - r);
		ckmax(ans, my);
	};
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
