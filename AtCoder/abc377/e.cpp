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
	vector<int> p(n);
	for (auto& x : p) cin >> x, --x;
	vector<int> vis(n), ans(n);
	for (int i = 0; i < n; ++i) {
		if (vis[i]) continue;
		int cur = i;
		vector<int> cycle;
		while (!vis[cur]) vis[cur] = 1, cycle.pb(cur), cur = p[cur];	
		vector<int> pp(sz(cycle)); iota(all(pp), 0);
		map<vector<int>, int> mp;
		mp[pp] = 0;
		int period;
		for (int j = 1; ; ++j) {
			vector<int> pp2(sz(cycle));
			for (int w = 0; w < sz(cycle); ++w) pp2[w] = pp[pp[w]];
			swap(pp2, pp);
			if (mp[pp]) break;	
		}
	}
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
