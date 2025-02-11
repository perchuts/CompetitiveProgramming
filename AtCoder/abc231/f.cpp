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
	vector<int> a(n), b(n);
	ord_set<pair<int, int>> s;
	for (auto& x : a) cin >> x;
	for (auto& x : b) cin >> x;
	for (int i = 0; i < n; ++i) s.insert({a[i], i});
	int ans = n*n;
	for (int i = 0; i < n; ++i) ans -= n-s.order_of_key({a[i], inf});
	vector<int> ord(n); iota(all(ord), 0);
	sort(all(ord), [&] (int x, int y) {
			return a[x] < a[y];
			});
	s.clear();
	for (int l = 0, r = 0; l < n; l = r) {
		vector<int> upd;
		while (r != n and a[ord[r]] == a[ord[l]]) {
			auto x = ord[r];
			s.insert({b[x], x});		
			upd.pb(x);
			r++;
		}
		for (auto x : upd) ans -= s.order_of_key({b[x], -1}); 
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
