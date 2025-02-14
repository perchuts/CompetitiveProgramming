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
	int k; cin >> k;
	int n, m; cin >> n >> m;
	vector<ii> x, y;
	int p1 = 998244353, p2 = 998244853;
	auto solve = [&] (vector<ii> v, int bound) {
		vector<ii> tipos;
		ii sum = {0, 0};
		for (auto [l, r] : v) {
			if (l > r) swap(l, r);
			int k1 = rnd(1, p2), k2 = rnd(1, p2);	

			if (l != 0) sum.first += k1, sum.second += k1, tipos.pb({l, k2-k1});
			else sum.first += k2, sum.second += k2; 

			tipos.pb({r, k1-k2});
		}
		sum.first %= p1, sum.second %= p2;

		tipos.pb({bound, 0});

		sort(all(tipos));

		map<ii, int> qnt;

		int last = 0, best = 0;
		for (int l = 0, r = 0; l < sz(tipos); l = r) {
			qnt[sum] += tipos[l].first - last;
			ckmax(best, qnt[sum]);
			//cout << "do " << last << " ate o " << tipos[l].first-1 << ": " << sum.first << endl;
			while (r != sz(tipos) and tipos[r].first == tipos[l].first) {
				sum.first = (sum.first + tipos[r].second) % p1;
				sum.second = (sum.second + tipos[r].second) % p2;
				r++;
			}
			sum.first = (sum.first + p1) % p1;
			sum.second = (sum.second + p2) % p2;
			assert(min(sum.first, sum.second) >= 0);
			last = tipos[l].first;
		}
		return best;
	};
	for (int i = 0; i < k; ++i) {
		int a, b, c, d; cin >> a >> b >> c >> d;
		x.pb({a, c});
		y.pb({b, d});
	}
	cout << solve(x, n) * solve(y, m) << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}

