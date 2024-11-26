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
	int n, m, k; cin >> n >> m >> k;
	vector<int> h(n), pos(n);
	for (auto& x : h) cin >> x;
	for (auto& x : pos) cin >> x;
	auto possible = [&] (int tries) {
		vector<ii> ev;
		for (int i = 0; i < n; ++i) {
			int l = 1, r = pos[i], lx = pos[i];
			if (h[i] > m*tries) continue;
			while (l <= r) {
				int md = (l + r) / 2;
				if (tries*max(0ll,m-abs(pos[i]-md))>=h[i]) lx = md, r = md-1;
				else l = md+1;
			}
			l = pos[i], r = pos[n-1];
			int rx = pos[i];
			while (l <= r) {
				int md = (l + r) / 2;
				if (tries*max(0ll,m-abs(pos[i]-md))>=h[i]) rx = md, l = md+1;
				else r = md-1;
			}
			ev.pb({lx, 1});
			ev.pb({rx+1, -1});
		}
		sort(all(ev));
		int tot = 0;
		for (int l = 0, r = 0; l < sz(ev); l = r) {
			while (r < sz(ev) && ev[l].first == ev[r].first) tot += ev[r++].second;
			if (tot >= k) return true;
		}
		return false;
	};
	int l = 1, r = 1e10, ans = 1e10;
	while (l <= r) {
		int md = l + (r-l+1)/2;
		if (possible(md)) r = md-1, ans = md;
		else l = md+1;
	}
	if (ans == 1e10) cout << -1 << endl;
	else cout << ans << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
