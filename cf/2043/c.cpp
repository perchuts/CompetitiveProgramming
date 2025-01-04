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
	vector<int> v(n);
	for (auto& x : v) cin >> x;
	int id = 0;
	for (int i = 0; i < n; ++i) {
		if (abs(v[i]) != 1) id = i;
	}
	vector<int> sums;
	auto solve = [&] (vector<int> a) {
		int cur1 = 0, cur2 = 0, mx = 0, mn = 0;
		for (auto x : a) {
			cur1 += x;
			cur2 += x;
			ckmax(cur1, 0);
			ckmin(cur2, 0);
			ckmax(mx, cur1);
			ckmin(mn, cur2);
		}
		for (int i = mn; i <= mx; ++i) sums.pb(i);
	};
	vector<int> a;
	for (int i = 0; i < id; ++i) a.pb(v[i]);
	solve(a);
	a.clear();
	for (int i = id+1; i < n; ++i) a.pb(v[i]);
	solve(a);
	int cur = 0, mnL = 0, mnR = 0, mxL = 0, mxR = 0;
	for (int i = id-1; i >= 0; --i) {
		cur += v[i];
		ckmin(mnL, cur);
		ckmax(mxL, cur);
	}
	cur = 0;
	for (int i = id+1; i < n; ++i) {
		cur += v[i];
		ckmin(mnR, cur);
		ckmax(mxR, cur);
	}
	for (int i = v[id]+mnL+mnR; i <= v[id]+mxL+mxR; ++i) sums.pb(i);
	sort(all(sums));
	sums.erase(unique(all(sums)), end(sums));
	cout << sz(sums) << endl;
	for (auto x : sums) cout << x << ' ';
	cout << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
