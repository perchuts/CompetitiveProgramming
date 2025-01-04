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
	// maximal segments
	vector<vector<map<int, int>>> maximal(20);
	// which maximal set i belong
	vector<vector<int>> where(20, vector<int>(n)), val(20);
	vector<vector<ii>> intr(20); // bounds for each maximal set
	// how many, qtd for each maximal set (must be sorted by bigger)
	vector<multiset<ii>> best(20);
	// should run in a very ugly nlog^2	
	v.pb(n);
	for (int pot = 0; (1 << pot) <= n; ++pot) {
		int l = 0;
		for (int i = 0; i <= n; ++i) {
			if (v[i] >= (1 << pot)) {
				if (l != i) {
					map<int, int> mp;
					for (int x = l; x < i; ++x) mp[v[x]]++, where[pot][x] = sz(maximal[pot]);
					maximal[pot].pb(mp);
					intr[pot].pb({l, i-1});
					val[pot].pb(sz(mp));
					best[pot].insert({-sz(mp), -(i-l)}); 
				}
				l = i+1;
			}
		}
	}
	while (q--) {
		int i, x; cin >> i >> x;
		--i;
		for (int pot = 0; (1 << pot) <= n; ++pot) {
			int idx = where[pot][i];
			if (v[i] < (1 << pot) and v[i]+x >= (1 << pot)) {
				// erase from this set
				int ls = i-intr[pot][idx].first, rs = intr[pot][idx].second-i;
				map<int, int> mp;
				best[pot].erase(best[pot].find({-val[pot][idx], - (intr[pot][idx].second-intr[pot][idx].first+1)}));
				if (ls <= rs) {
					for (int j = intr[pot][idx].first; j <= i; ++j) {
						where[pot][j] = sz(maximal[pot]);
						if (j != i) mp[v[j]]++;
						maximal[pot][idx][v[j]]--;
						if (maximal[pot][idx][v[j]] == 0) val[pot][idx]--;
					}
					val[pot].pb(sz(mp));
					if (rs) best[pot].insert({-val[pot][idx], -rs}); 
					if (ls) best[pot].insert({-sz(mp), -ls});
					intr[pot].pb({intr[pot][idx].first, i-1});
					maximal[pot].pb(mp);
					intr[pot][idx].first = i+1;
				} else {
					for (int j = i; j <= intr[pot][idx].second; ++j) {
						where[pot][j] = sz(maximal[pot]);
						if (j != i) mp[v[j]]++;
						maximal[pot][idx][v[j]]--;
						if (maximal[pot][idx][v[j]] == 0) val[pot][idx]--;
					}
					val[pot].pb(sz(mp));
					if (rs) best[pot].insert({-sz(mp), -rs});
					if (ls) best[pot].insert({-val[pot][idx], -ls}); 
					intr[pot].pb({i+1, intr[pot][idx].second});
					maximal[pot].pb(mp);
					intr[pot][idx].second = i-1;
				}
			} else if (v[i]+x < (1 << pot)) {
				// ill exist here. update accordingly
				best[pot].erase(best[pot].find({-val[pot][idx], -(intr[pot][idx].second-intr[pot][idx].first+1)}));
				maximal[pot][idx][v[i]]--;
				if (maximal[pot][idx][v[i]] == 0) val[pot][idx]--;
				maximal[pot][idx][v[i]+x]++;
				if (maximal[pot][idx][v[i]+x] == 1) val[pot][idx]++;
				best[pot].insert({-val[pot][idx], -(intr[pot][idx].second-intr[pot][idx].first+1)});
			}
		}
		v[i] += x;
		int ans = 0;
		for (int pot = 0; (1 << pot) <= n; ++pot) {
			if (!best[pot].empty()) {
				auto [a, b] = *begin(best[pot]);
				if (-a == (1 << pot)) ckmax(ans, -b);
			}
		}
		cout << ans << endl;
	}
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
