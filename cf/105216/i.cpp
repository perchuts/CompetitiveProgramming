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
	int n, d; cin >> n >> d;

	vector<vector<ii>> intr(n, vector<ii>(d)), cmpr = intr;
	vector<vector<int>> hlp(d);

	for (auto& x : intr) for (auto& [y, z] : x) cin >> y >> z;

	int q; cin >> q;

	vector<int> answer(q);

	for (int i = 0; i < d; ++i) {
		for (int j = 0; j < n; ++j) {
			hlp[i].pb(intr[j][i].first);	
			hlp[i].pb(intr[j][i].second);	
		}
		sort(all(hlp[i]));
		hlp[i].erase(unique(all(hlp[i])), end(hlp[i]));
		for (int j = 0; j < n; ++j) {
			cmpr[j][i].first = lower_bound(all(hlp[i]), intr[j][i].first) - begin(hlp[i]) + 1;
			cmpr[j][i].second = lower_bound(all(hlp[i]), intr[j][i].second) - begin(hlp[i]) + 1;
		}
	}

	const int magic = 100;

	vector<vector<iii>> block(n/magic+10);

	for (int i = 0; i < q; ++i) {
		int l, r; cin >> l >> r;
		--l, --r;
		block[l/magic].pb({r, l, i});
	}

	vector<vector<array<int, 3>>> bit(d, vector<array<int, 3>>(2*n+1));

	auto insert = [&] (int dim, int x, int a, int b, int c) {
		while (x <= 2*n) {
			bit[dim][x][0] += a, bit[dim][x][1] += b, bit[dim][x][2] += c;
			x += x & (-x);
		}
	};

	auto query = [&] (int dim, int x) {
		array<int, 3> ans;
		ans[0] = ans[1] = ans[2] = 0;
		while (x) {
			ans[0] += bit[dim][x][0];
			ans[1] += bit[dim][x][1];
			ans[2] += bit[dim][x][2];
			x -= x & (-x);
		}
		return ans;
	};
	// soma dos L, soma dos R, soma de qnts tem
	for (int bl = 0; bl * magic < n; ++bl) {
		sort(all(block[bl]), [&] (iii x, iii y) {
				return x < y;
				});
		for (int dim = 0; dim < d; ++dim) {
			for (int i = 1; i <= 2*n; ++i) {
				bit[dim][i][0] = bit[dim][i][1] = bit[dim][i][2] = 0;
			}
		}
		int l = bl*magic-1, r = bl*magic;
		for (auto [rx, lx, id] : block[bl]) {
			auto add = [&] (int i, int pos, int c) {
				insert(i, cmpr[pos][i].second, 0, c * intr[pos][i].second, c);
				insert(i, 1, c * intr[pos][i].first, 0, -c);
				insert(i, cmpr[pos][i].first+1, -c * intr[pos][i].first, 0, c);
			};
			while (r <= rx) {
				for (int i = 0; i < d; ++i) add(i, r, 1);
				r++;
			}
			while (l < lx-1) {
				l++;
				for (int i = 0; i < d; ++i) add(i, l, -1);
			}
			while (lx <= l) {
				for (int i = 0; i < d; ++i) add(i, l, 1);
				l--;
			}
			// ternary search
			for (int dim = 0; dim < d; ++dim) {
				auto f = [&] (int pos) {
					auto bef = query(dim, pos);
					return hlp[dim][pos-1] * bef[2] - bef[1] + bef[0];
				};
				int lp = 1, rp = sz(hlp[dim]);
				while (rp-lp > 2) {
					int m1 = lp + (rp-lp)/3;
					int m2 = rp - (rp-lp)/2;
					if (f(m1) < f(m2)) rp = m2;
					else lp = m1;
				}
				int best = 1e18;
				for (int i = lp; i <= rp; ++i) ckmin(best, f(i));
				answer[id] += best;
			}
		};
	}
	for (auto x : answer) cout << x << endl;

}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
