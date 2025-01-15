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
const int maxn = 1e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

namespace seg {
	
	int n, ans[4*maxn];

	unordered_map<int, int> seg[4*maxn];
	vector<int> lz[4*maxn];

	void build(int n2) {
		n = n2;
		for (int i = 0; i < 4*n2; ++i) seg[i].clear(), lz[i].clear(), ans[i] = 0;
	}
	void prop(int p, int l, int r) {
		for (auto x : lz[p]) {
			if (seg[p][x] & 1) ans[p]--;
			seg[p][x]++;
			if (seg[p][x] & 1) ans[p]++;
		}
		if (l != r) {
			for (auto x : lz[p]) lz[2*p].pb(x), lz[2*p+1].pb(x);
		}
		lz[p].clear();
	}
	ll query(int a, int b, int p=1, int l=0, int r=n-1) {
		prop(p, l, r);
		if (l == r) return ans[p];
		int m = (l+r)/2;
		if (a <= m) return query(a, b, 2*p, l, m);
		return query(a, b, 2*p+1, m+1, r);
	}
	void update(int a, int b, int x, int p=1, int l=0, int r=n-1) {
		prop(p, l, r);
		if (a <= l and r <= b) {
			lz[p].pb(x);
			prop(p, l, r);
			return;
		}
		if (b < l or r < a) return;
		int m = (l+r)/2;
		update(a, b, x, 2*p, l, m), update(a, b, x, 2*p+1, m+1, r);
	}
};


void solve(){
	int n; cin >> n;
	vector<vector<ii>> poly(n);
	for (int i = 0; i < n; ++i) {
		int m; cin >> m;
		poly[i].resize(m);
		for (auto& [x, y] : poly[i]) cin >> x >> y;
	}
	int q; cin >> q;
	vector<ii> qu(q);
	for (auto& [x, y] : qu) cin >> x >> y;
	// N = 1
	// N = 2?
	// vou inserir dois pontos (l, r+1) em estrutura(i)
	// quero perguntar a soma de prefixo em 1, x pra toda estrutura e somar tudo
	// alternativamente, vou olhar pros pontos (x) onde se localizam as queries
	// a cada momento q eu insiro uma retinha (l, r), vou ter varios pontos aqui dentro ne
	// a resposta desses caras pode mudar?
	//
	vector<tuple<int, int, int, int>> ev;
	for (int i = 0; i < n; ++i) {
		int m = poly[i].size();
		for (int j = 0; j < m; ++j) {
			auto [x1, y1] = poly[i][j];
			auto [x2, y2] = poly[i][(j+1)%m];
			if (y1 != y2) continue;
			ev.pb({y1, min(x1, x2), max(x1, x2)-1, i});
		}
	}
	int id = 0;
	for (auto [x, y] : qu) ev.pb({y+1, -inf, x, id++}); 
	sort(all(ev), greater<>());
	seg::build(maxn);
	vector<int> ans(q);
	for (auto [y, a, b, c] : ev) {
		if (a == -inf) {
			// query
			ans[c] = seg::query(b, b);
		} else {
			// update
			seg::update(a, b, c);
		}
	}
	for (auto x : ans) cout << x << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
