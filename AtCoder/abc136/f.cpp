#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
	using ord_set = tree<T, null_type, less<T>, rb_tree_tag,
	tree_order_statistics_node_update>;
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = (119<<23)+1;
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
	vector<int> pw(n+1, 1);
	for (int i = 1; i <= n; ++i) pw[i] = (pw[i-1] + pw[i-1]) % mod;
	vector<ii> pt(n);
	for (auto& [x, y] : pt) cin >> x >> y;
	int ans = 0;
	for (int i = 1; i < n; ++i) ans = (ans + 4*(pw[i] - 1)) % mod;
	vector<int> ord_x(n); iota(all(ord_x), 0);
	sort(all(ord_x), [&] (int a, int b) {
		return pt[a].first < pt[b].first;
	});
	ord_set<int> s;
	for (int w = 0; w < 2; ++w) {
		for (int i = 0; i < n; ++i) {
			auto k = pt[ord_x[i]];
			int eu = s.order_of_key(k.second);
			ans = (ans + mod - pw[eu] + 1) % mod;
			ans = (ans + mod - pw[i-eu] + 1) % mod;
			s.insert(k.second);
		}
		s.clear();
		reverse(all(ord_x));
	}
	ans = ((pw[n] - 1)*n - ans) % mod;
	if (ans < 0) ans += mod;
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
