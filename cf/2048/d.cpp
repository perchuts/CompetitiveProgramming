#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
	using ord_set = tree<T, null_type, less<T>, rb_tree_tag,
	tree_order_statistics_node_update>;

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
	int n, m; cin >> n >> m;
	vector<int> a(n), b(m);
	for (auto& x : a) cin >> x;
	for (auto& x : b) cin >> x;
	ord_set<ii> os;
	for (int i = 0; i < n; ++i) os.insert({-a[i], i});
	vector<int> big;
	for (auto x : b) if (x > a[0]) big.pb(x);
	sort(all(big));
	for (int k = 1; k <= m; ++k) {
		ll ans = m/k;
		for (int w = m % k; w < sz(big); w += k) ans += os.order_of_key(make_pair(-big[w], inf));
		cout << ans << ' ';
	}
	cout << endl;

}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
