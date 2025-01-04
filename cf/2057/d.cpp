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
	int n, q; cin >> n >> q;
	vector<int> v(n);
	for (auto& x : v) cin >> x;
	struct node {
		int best, mn1, mx1, mn2, mx2;
	} seg[4*n+59];
	auto merge = [&] (node a, node b) {
		node res;
		res.mn1 = min(a.mn1, b.mn1);
		res.mx1 = max(a.mx1, b.mx1);
		res.mn2 = min(a.mn2, b.mn2);
		res.mx2 = max(a.mx2, b.mx2);
		res.best = max({a.best, b.best, b.mx1 - a.mn1, a.mx2 - b.mn2});
		return res;
	};
	function<void(int,int,int)> build = [&] (int i, int l, int r) {
		if (l == r) {
			seg[i].mn1 = seg[i].mx1 = v[l] - l;
			seg[i].mn2 = seg[i].mx2 = v[l] + l;
			seg[i].best = 0;
			return;
		}
		int md = (l+r)/2;
		build(2*i, l, md), build(2*i+1, md+1, r);
		seg[i] = merge(seg[2*i], seg[2*i+1]);
	};
	function<void(int,int,int,int,int)> upd = [&] (int i, int l, int r, int x, int k) {
		if (l == r) {
			seg[i].mn1 = seg[i].mx1 = k - l;
			seg[i].mn2 = seg[i].mx2 = k + l;
			return;
		}
		int md = (l + r) / 2;
		if (x <= md) upd(2*i, l, md, x, k);
		else upd(2*i+1, md+1, r, x, k);
		seg[i] = merge(seg[2*i], seg[2*i+1]);
	};
	build(1, 0, n-1);
	cout << seg[1].best << endl;
	while (q--) {
		int i, x; cin >> i >> x;
		--i;
		upd(1, 0, n-1, i, x);
		cout << seg[1].best << endl;
	}
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
