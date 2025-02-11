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
 	int n; cin >> n;
	vector<ii> intr(n);
	for (auto& [x, y] : intr) cin >> x >> y;
	int q; cin >> q;
	vector bl(n, vector(2, vector(19, make_tuple(0LL, 0LL, 0LL))));
	vector sp(n, vector(20, make_pair(0, 0)));
	for (int i = 0; (1 << i) <= n; ++i) {
		for (int j = 0; j + (1 << i) <= n; ++j) {
			if (i == 0) sp[j][i] = {intr[j].first, intr[j].second};
			else sp[j][i] = {max(sp[j][i-1].first, sp[j+(1<<(i-1))][i-1].first), min(sp[j][i-1].second, sp[j+(1<<(i-1))][i-1].second)};
		}
	}
	auto query = [&] (int l, int r) {
		int lg = 31 - __builtin_clz(r-l+1);
		int L = max(sp[l][lg].first, sp[r-(1<<lg)+1][lg].first);
		int R = min(sp[l][lg].second, sp[r-(1<<lg)+1][lg].second);
		return make_pair(L, R);
	};
	for (int i = n-1; ~i; --i) {
		vector<int> pos(2);
		pos[0] = intr[i].first, pos[1] = intr[i].second;
		for (int j = 0; j < 19; ++j) {
			for (int k = 0; k < 2; ++k) {
				if (j == 0) {
					int l = i, r = n-1, ans = i;
					while (l <= r) {
						int md = l + (r-l+1)/2;
						auto [maxL, minR] = query(i, md);
						if (pos[k] < maxL or minR < pos[k]) r = md-1;
						else l = md+1, ans = md;
					}
					bl[i][k][0] = {ans-i, pos[k], ans};
					continue;
				}
				auto [c1, row1, col1] = bl[i][k][j-1];
				assert(col1 == n-1 or (row1 < intr[col1+1].first or intr[col1+1].second < row1));
				if (col1 == n-1) { bl[i][k][j] = bl[i][k][j-1]; continue; }
				int ncost = c1, nrow, ncol;
				if (row1 < intr[col1+1].first) 
					ncost += 1+intr[col1+1].first - row1 + get<0>(bl[col1+1][0][j-1]), nrow = get<1>(bl[col1+1][0][j-1]), ncol = get<2>(bl[col1+1][0][j-1]);
				else 
					ncost += 1+row1 - intr[col1+1].second + get<0>(bl[col1+1][1][j-1]), nrow = get<1>(bl[col1+1][1][j-1]), ncol = get<2>(bl[col1+1][1][j-1]);
				bl[i][k][j] = {ncost, nrow, ncol};
			}
		}
	}
	while (q--) {
		int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
		--x1, --x2;
		if (x1 > x2) swap(x1, x2), swap(y1, y2);
		int l = x1, r = x2, ans = x1;
		while (l <= r) {
			int md = l + (r-l+1)/2;
			auto [maxL, minR] = query(x1, md);
			if (y1 < maxL or minR < y1) r = md-1;
			else l = md+1, ans = md;
		}
		if (ans == x2) {
			cout << x2 - x1 + abs(y1 - y2) << endl;
			continue;
		}
		int cost = ans-x1+1, col = ans+1, rowid = (y1 < intr[ans+1].first ? 0 : 1), row = (rowid ? intr[ans+1].second : intr[ans+1].first);
		cost += abs(row-y1);
		for (int j = 18; ~j; --j) {
			auto [cost2, row2, col2] = bl[col][rowid][j];
			if (col2 < x2) {
				cost += cost2;
				col = col2+1;
				if (row2 < intr[col2+1].first) cost += intr[col2+1].first - row2 + 1, rowid = 0, row = intr[col2+1].first;
				else assert(intr[col2+1].second < row2), cost += row2 - intr[col2+1].second + 1, rowid = 1, row = intr[col2+1].second;
			} 
		}
		cost += abs(row - y2) + abs(x2 - col);
		cout << cost << endl;
	}
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
