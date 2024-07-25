#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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
// 2-SAT
//
// solve() retorna um par, o first fala se eh possivel
// atribuir, o second fala se cada variavel eh verdadeira
//
// O(|V|+|E|) = O(#variaveis + #restricoes)

struct sat {
	int n, tot;
	vector<vector<int>> g;
	vector<int> vis, comp, id, ans;
	stack<int> s;

	sat() {}
	sat(int n_) : n(n_), tot(n), g(2*n) {}

	int dfs(int i, int& t) {
		int lo = id[i] = t++;
		s.push(i), vis[i] = 2;
		for (int j : g[i]) {
			if (!vis[j]) lo = min(lo, dfs(j, t));
			else if (vis[j] == 2) lo = min(lo, id[j]);
		}
		if (lo == id[i]) while (1) {
			int u = s.top(); s.pop();
			vis[u] = 1, comp[u] = i;
			if ((u>>1) < n and ans[u>>1] == -1) ans[u>>1] = ~u&1;
			if (u == i) break;
		}
		return lo;
	}

	void add_impl(int x, int y) { // x -> y = !x ou y
		x = x >= 0 ? 2*x : -2*x-1;
		y = y >= 0 ? 2*y : -2*y-1;
		g[x].push_back(y);
		g[y^1].push_back(x^1);
	}
	void add_cl(int x, int y) { // x ou y
		add_impl(~x, y);
	}
	void add_xor(int x, int y) { // x xor y
		add_cl(x, y), add_cl(~x, ~y);
	}
	void add_eq(int x, int y) { // x = y
		add_xor(~x, y);
	}
	void add_true(int x) { // x = T
		add_impl(~x, x);
	}
	void at_most_one(vector<int> v) { // no max um verdadeiro
		g.resize(2*(tot+v.size()));
		for (int i = 0; i < v.size(); i++) {
			add_impl(tot+i, ~v[i]);
			if (i) {
				add_impl(tot+i, tot+i-1);
				add_impl(v[i], tot+i-1);
			}
		}
		tot += v.size();
	}

	pair<bool, vector<int>> solve() {
		ans = vector<int>(n, -1);
		int t = 0;
		vis = comp = id = vector<int>(2*tot, 0);
		for (int i = 0; i < 2*tot; i++) if (!vis[i]) dfs(i, t);
		for (int i = 0; i < tot; i++)
			if (comp[2*i] == comp[2*i+1]) return {false, {}};
		return {true, ans};
	}
};
void solve(){	
	int n; cin >> n;
	vector<iii> coords;
	vector<ii> types;
	for (int i = 0; i < n; ++i) {
		int x, y; cin >> x >> y;
		coords.pb({x, i, 1}), coords.pb({y, i, 0});
		types.pb({x, y});
	}
	sort(all(coords));
	//for (auto [x, y, z] : coords) cout << x << ' ' << y << ' ' << z << endl;
	vector<ii> v;
	for (int i = 0; i < n; ++i) {
		auto [x, y] = types[i];
		int a = lower_bound(all(coords), make_tuple(x, i, 1)) - begin(coords);
		int b = lower_bound(all(coords), make_tuple(y, i, 0)) - begin(coords);
		v.pb({a, b});
	}
	auto possible = [&] (int d) {
		sat oraculo(13*n);
		int shift = 8*n+5;
		function<void(int,int,int)> build = [&] (int i, int l, int r) {
			if (l == r) {
				oraculo.add_impl(i, ~(shift+l));
				return;
			}
		int md = (l + r) / 2;
			build(2*i, l, md), build(2*i+1, md+1, r);
			oraculo.add_impl(i, 2*i), oraculo.add_impl(i, 2*i+1);
		};
		function<void(int,int,int,int,int,int)> add_range = [&] (int i, int l, int r, int x, int y, int clause) {
			if (r < x || y < l) return;
			if (x <= l && r <= y) {
				oraculo.add_impl(clause, i);
				return;
			}
			int md = (l + r) / 2;
			add_range(2*i, l, md, x, y, clause), add_range(2*i+1, md+1, r, x, y, clause);
		};
		build(1, 0, 2*n-1);
		for (int i = 0; i < n; ++i) oraculo.add_xor(shift+v[i].first, shift+v[i].second);
		//cout << d << endl;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < 2; ++j) {
				int my = v[i].first;
				auto [my_coord, dmsada, dasda] = coords[my];
				//if (d == 8) cout << my << ": ";
				int l = 0, r = my-1, pos = -1;
				while (l <= r) {
					int md = l + (r-l+1)/2;
					auto [x, y, z] = coords[md];
					if (abs(x-my_coord) < d) pos = md, r = md - 1;
					else l = md + 1;
				}
				//if (d == 8) cout << pos << ' ';
				if (pos != -1) add_range(1, 0, 2*n-1, pos, my-1, shift+my);
				l = my+1, r = 2*n-1, pos = -1;
				while (l <= r) {
					int md = l + (r-l+1)/2;
					auto [x, y, z] = coords[md];
					if (abs(x-my_coord) < d) pos = md, l = md + 1;
					else r = md - 1;
				}
				//if (pos != -1) add_range(1, 0, 2*n-1, my+1, pos, shift+my);
				//if (d == 8) cout << pos << ' ';
				//if (d == 8) cout << endl;
				swap(v[i].first, v[i].second);
			}
			if (d == 8) cout << endl;
		}
		auto [can, soadas] = oraculo.solve();
		return can;
	};
	int l = 0, r = 1e9, ans = 0;
	while (l <= r) {
		int md = l + (r-l+1)/2;
		if (possible(md)) ans = md, l = md + 1;
		else r = md - 1;
	}
	cout << ans << endl;

}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
