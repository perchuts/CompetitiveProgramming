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
	vector<iii> v(n);
	vector<int> cd;
	for (auto& [x, y, z] : v) cin >> x >> y >> z, cd.pb(x), cd.pb(y);
	sort(all(cd)); cd.erase(unique(all(cd)), end(cd));
	for (auto& [x, y, z] : v) x = lower_bound(all(cd), x) - begin(cd) + 1, y = lower_bound(all(cd), y) - begin(cd) + 1;
	vector<int> ord(n); iota(all(ord), 0);
	sort(all(ord), [&] (int x, int y) {
		auto [a1, b1, c1] = v[x];
		auto [a2, b2, c2] = v[y];
		if (a1 == a2) return b1 < b2;
		return a1 < a2;
	});
	vector<int> ans(n), bit(2*n+1);
	auto insert = [&] (int x, int k) {
		while (x <= 2*n) bit[x] += k, x += x&(-x);
	};
	auto query = [&] (int x) {
		int r = 0;
		while (x) r += bit[x], x -= x&(-x);
		return r;
	};
	for (auto i : ord) {
		auto [x, y, cost] = v[i];
		insert(y, cost);
		ans[i] = query(y);
	}	
	for (auto x : ans) cout << x << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
