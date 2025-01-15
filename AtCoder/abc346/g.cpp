#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
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
	vector<int> a(n);
	for (auto& x : a) cin >> x;
	vector<int> prox(n), lst(n), occ(n+1);
	for (int i = n-1; i >= 0; --i) {
		if (occ[a[i]] == 0) prox[i] = n; 
		else prox[i] = occ[a[i]];
		occ[a[i]] = i;
	}
	occ = vector<int>(n+1, -1);
	for (int i = 0; i < n; ++i) {
		if (occ[a[i]] == -1) lst[i] = -1;
		else lst[i] = occ[a[i]];
		occ[a[i]] = i;
	}
	int ans = 0;
	vector<int> bestL(n), bestR(n);
	int big = (1LL << 62) - 1; big = 2 * big - 1;
	auto solve = [&] (auto&& self, int l, int r) -> void {
		if (l == r) {
			ans++;
			return;
		}
		int md = (l+r)/2, aqui = 0;
		self(self, l, md), self(self, md+1, r); 
		multiset<int> s;
		for (int i = l; i <= md; ++i) if (lst[i] < l and md < prox[i]) s.insert(min(prox[i]-1, r)); 
		vector<ii> v1, v2;
		for (int i = l; i <= md; ++i) {
			if (l == 5 and r == 9) {
			}
			if (!s.empty()) v1.pb({*prev(end(s)), i});
			else v1.pb({md, i});
			if (md < prox[i]) {
				s.erase(s.find(min(prox[i]-1, r)));
			}
			if (prox[i] <= md and md < prox[prox[i]]) s.insert(min(prox[prox[i]]-1, r));
		}
		s.clear();
		for (int i = md+1; i <= r; ++i) if (lst[i] < md and r < prox[i]) s.insert(max(lst[i]+1, l)); 
		for (int i = r; i > md; --i) {
			if (!s.empty()) v2.pb({i, *begin(s)});
			if (lst[i] < md) s.erase(s.find(max(lst[i]+1, l)));
			if (md <= lst[i] and lst[lst[i]] < md) s.insert(max(lst[lst[i]]+1, l));
		}
		sort(all(v1));	
		sort(all(v2));
		ord_set<ii> sexo;
		for (auto [x, y] : v2) sexo.insert({y, x});
		int j = 0;
		for (int i = 0; i < sz(v1); ++i) {
			while (j != sz(v2) and v2[j].first <= v1[i].first) sexo.erase({v2[j].second, v2[j].first}), j++;
			aqui += v1[i].first - md + sexo.order_of_key({v1[i].second, n});
		}
		ans += aqui;
	};
	solve(solve, 0, n-1);
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
