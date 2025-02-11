#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
	int n, m; cin >> n >> m;
	vector<int> v(n);
	for (auto& x : v) cin >> x;
	int l = 1, r = 1e18, ans = 0;
	auto calc1 = [&] (int x) {
		int resp = 0, left = m;
		for (auto val : v) {
			if (val > x) continue;
			int lim = (x-val)/(2*val)+1;	
			ckmax(lim, 0LL);
			int lim2 = sqrt(left / val);	
			while (lim2 * lim2 + 2 * lim2 + 1 <= left/val) lim2++;
			if (lim > lim2) return false;
			resp += lim;
			assert(lim*lim <= left/val);
			left -= lim*lim*val;
		}
		return true;
	};
	auto calc2 = [&] (int x) {
		int resp = 0, left = m;
		for (auto val : v) {
			if (val > x) continue;
			int lim = (x-val)/(2*val)+1;	
			ckmax(lim, 0LL);
			resp += lim;
			assert(lim*lim <= left/val);
			left -= lim*lim*val;
		}
		for (auto val : v) {
			int lim = (x-val)/(2*val)+1;	
			ckmax(lim, 0LL);
			int k = (2*lim+1)*val;
			assert(k > x);
			if (k == x+1 and k <= left) resp++, left -= k;
		}
		return resp;
	};
	int point = 0;
	while (l <= r) {
		int md = l + (r-l+1)/2;
		if (calc1(md)) point = md, l = md+1;
		else r = md-1;
	}
	cout << calc2(point) << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}

