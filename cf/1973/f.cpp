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

void solve(){
 	int n, q; cin >> n >> q;
	vector<int> a(n), b(n), c(n);
	for (auto& x : a) cin >> x;
	for (auto& x : b) cin >> x;
	for (auto& x : c) cin >> x;
	int base_cost = 0;
	vector<ii> dps;	
	vector<int> fa, fb;
	vector<vector<int>> id_multa, id_multb;
	for (int ____ = 0; ____ < 2; ++____) {
		for (int j = 1; j * j <= a[0]; ++j) {
			if (a[0] % j) continue;
			fa.pb(a[0] / j);
			if (j * j != a[0]) fa.pb(j);
		}
		sort(all(fa));
		for (int j = 0; j < sz(fa); ++j) {
			int x = fa[j];
			vector<int> idd;
			for (int i = j+1; i < sz(fa); ++i) {
				int y = fa[i];
				if (y % x == 0) idd.pb(i);
			}
			id_multa.pb(idd);
		}
		swap(a[0], b[0]), swap(fa, fb), swap(id_multa, id_multb);
	}

	for (int __ = 0; __ < 2; ++__) {
		int s1 = sz(fa), s2 = sz(fb);
		vector<vector<ii>> freq(s1, vector<ii>(s2, make_pair(0, 0)));
		auto getId = [&] (int x, bool type) {
			if (type == false) return lower_bound(all(fa), x) - begin(fa);
			return lower_bound(all(fb), x) - begin(fb);
		};
		for (int i = 1; i < n; ++i) {
			int na = gcd(a[0], a[i]), nb = gcd(b[0], b[i]);
			int id_a = getId(na, 0), id_b = getId(nb, 1);
			freq[id_a][id_b].second++;
			id_a = getId(gcd(a[0], b[i]), 0), id_b = getId(gcd(b[0], a[i]), 1);
			freq[id_a][id_b].second++;
			freq[id_a][id_b].first += c[i];
			int g1 = gcd(gcd(a[0], a[i]), b[i]), g2 = gcd(gcd(b[0], a[i]), b[i]);
			id_a = getId(g1, 0), id_b = getId(g2, 1);
			freq[id_a][id_b].first -= c[i];
			freq[id_a][id_b].second--;
		}
		auto dp = freq;
		for (int i = 0; i < s1; ++i) {
			for (int j = 0; j < s2; ++j) {
				for (auto k : id_multa[i]) {
					dp[i][j].first += dp[k][j].first;
					dp[i][j].second += dp[k][j].second;
				}
			}
		}
		auto dp2 = dp;
		for (int i = 0; i < s1; ++i) {
			for (int j = 0; j < s2; ++j) {
				assert(j < sz(id_multb));
				for (auto k : id_multb[j]) {
					dp2[i][j].first += dp[i][k].first;
					dp2[i][j].second += dp[i][k].second;
				}
				if (dp2[i][j].second == n-1) dps.emplace_back(base_cost + dp2[i][j].first, fa[i] + fb[j]);
			}	
		}
		swap(a[0], b[0]);
		swap(fa, fb);
		swap(id_multa, id_multb);
		base_cost += c[0];
	}
	sort(all(dps));
	vector<ii> ndp;
	for (auto [x, y] : dps) {
		while (!ndp.empty() && ndp.back().second < y && ndp.back().first == x) ndp.pop_back();
		if (ndp.empty() or ndp.back().second < y) ndp.pb({x, y});
	}
	swap(ndp, dps);
	while (q--) {
		int cost; cin >> cost;
		int ans = lower_bound(all(dps), make_pair(cost+1, 0ll)) - begin(dps) - 1;
		cout << dps[ans].second << ' ';
	}
	cout << endl;

}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
