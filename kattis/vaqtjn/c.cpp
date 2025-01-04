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
	vector<double> tmp(n);
	int mx = -inf;
	for (auto& x : v) cin >> x, ckmax(mx, x);
	double l = -inf, r = mx, ans = l;
	auto possible = [&] (double x) {
		double s = 0, cur = 0, mn = 0, elem = 0, mxelem = 0;
		for (int i = 0; i < n; ++i) {
			s += v[i] - x;
			cur += v[i] - x, elem++;
			if (cur >= 0) cur = 0, elem = 0;
			if (ckmin(mn, cur)) mxelem = elem;
		}
		return (s > mn and mxelem < n);
	};
	for (int __ = 0; __ < 80; ++__) {
		double md = (l+r)/2;
		if (possible(md)) ans = md, l = md;
		else r = md;
	}
	if (ans < 0) {
		cout << 0 << endl;
		return;
	}
	cout << fixed << setprecision(10) << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
