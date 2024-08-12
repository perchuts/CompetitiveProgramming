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
vector<int> dv[maxn];
vector<ii> queries[maxn];
void solve(){
	int n, q; cin >> n >> q;
	vector<int> pos(n);
	for (auto& x : pos) cin >> x;
	for (int i = 1; i <= q; ++i) {
		int c, x; cin >> c >> x;
		int k = sz(dv[c]);
		for (int j = 1; j < (1 << k); ++j) {
			int cur = 1;
			for (int w = 0; w < k; ++w) {
				if ((j>>w)&1) cur *= dv[c][w];
			}
			queries[cur].pb({i, x});
		}
	}
	for (int i = 1; i <= 1e5; ++i) {
		queries[i].pb({0, 0});
		sort(all(queries[i]));
		for (int j = 1; j < sz(queries[i]); ++j) queries[i][j].second += queries[i][j-1].second;
	}
	for (int i = 0; i < n; ++i) {
		int l = 1, r = q, ans = -1;
		while (l <= r) {
			int md = l + (r-l+1)/2;
			int k = sz(dv[i+1]), tot = 0;
			for (int j = 1; j < (1 << k); ++j) {
				int cur = 1;
				for (int w = 0; w < k; ++w) {
					if ((j>>w)&1) cur *= dv[i+1][w];
				}
				auto p = upper_bound(all(queries[cur]), make_pair(md, inf)) - begin(queries[cur]) - 1;

				auto [x, y] = queries[cur][p];
				if (__builtin_popcount(j)&1) tot += y;
				else tot -= y;
			}
			if (tot >= pos[i]) ans = md, r = md - 1;
			else l = md + 1;
		}		
		cout << ans << endl;
	}

}
int crivo[maxn];
int32_t main(){_
  int t = 1; //cin >> t;
  for (int i = 2; i <= 1e5; ++i) {
	if (crivo[i]) continue;
	for (int j = i; j <= 1e5; j += i) {
		crivo[j] = 1;
		dv[j].pb(i);
	}
  }
  while(t--) solve();
}
