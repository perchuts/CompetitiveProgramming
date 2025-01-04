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
	int n, k; cin >> n >> k;
	vector<int> a(n), b(n);
	vector<ii> ev;
	for (auto& x : a) cin >> x, ev.pb({x+1, 1}), ev.pb({x, 0});
	for (auto& x : b) cin >> x, ev.pb({x+1, -1}), ev.pb({x, 0});
	sort(all(ev));
	int ans = 0, alive = n, lst = 0, neg = 0, best = 0;
	for (int l = 0, r = 0; l < 4*n; l = r) {
		while (r < 4*n and ev[r].first == ev[l].first) {
			if (ev[r].second == 1) neg++;
			else if (ev[r].second == -1) neg--, alive--, ans -= lst;
			r++;
		}
		ans += alive * (ev[l].first - lst);
		if (neg <= k) ckmax(best, ans);
		lst = ev[l].first;
	}
	cout << best << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
