#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
#pragma GCC optimize("Ofast")
// Auto explicativo
#pragma GCC optimize("unroll-loops")
// Vetorizacao
#pragma GCC target("avx2")
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
int v[maxn];
using matrix = vector<vector<int>>;
matrix I = {{1, 0}, {0, 1}};
matrix fib = {{1, 1}, {1, 0}};
matrix nada = {{0}, {0}};

matrix mult(const matrix& a, const matrix& b) {
	int n = a.size(), m = a[0].size(), k = b[0].size();
	matrix resp(n, vector<int>(k, 0));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < k; ++j) {
			for (int w = 0; w < m; ++w) {
				resp[i][j] = (resp[i][j] + a[i][w] * b[w][j]) % mod;
			}
		}
	}
	return resp;
}
matrix seg[4*maxn], lz[4*maxn];
matrix fexp(matrix x, int e) {
	int N = x.size();
	matrix ans(N, vector<int>(N));
	for (int i = 0; i < N; ++i) ans[i][i] = 1;
	while (e) {
		if (e&1) ans = mult(ans, x);
		x = mult(x, x), e /=2;
	}
	return ans;
};
void build(int i, int l, int r) {
		lz[i] = I;
		if (l == r) {
			auto M = fexp(fib, v[l]);
			seg[i] = mult(M, {{1}, {0}});
			return;
		}
		int md = (l + r) / 2;
		build(2*i, l, md), build(2*i+1, md+1, r);
		seg[i] = {{0}, {0}};
		seg[i][0][0] = (seg[2*i][0][0] + seg[2*i+1][0][0]) % mod;
		seg[i][1][0] = (seg[2*i][1][0] + seg[2*i+1][1][0]) % mod;
}
void push(int i, int l, int r) {
	if (lz[i] == I) return;	
	seg[i] = mult(lz[i], seg[i]);
	if (l != r) lz[2*i] = mult(lz[2*i], lz[i]), lz[2*i+1] = mult(lz[2*i+1], lz[i]);
	lz[i] = I;
}
void upd (int i, int l, int r, int x, int y, const matrix& ff) {
	push(i, l, r);
	if (x <= l and r <= y) {
		lz[i] = mult(lz[i], ff);
		push(i, l, r);
		return;
	}
	if (r < x or y < l) return;
	int md = (l+r)/2;
	upd(2*i, l, md, x, y, ff);
	upd(2*i+1, md+1, r, x, y, ff);
	seg[i][0][0] = (seg[2*i][0][0] + seg[2*i+1][0][0]) % mod;
	seg[i][1][0] = (seg[2*i][1][0] + seg[2*i+1][1][0]) % mod;
}

matrix query(int i, int l, int r, int x, int y) {
	push(i, l, r);
	if (r < x or y < l) return nada;
	if (x <= l and r <= y) return seg[i];
	int md = (l+r)/2;
	auto lx = query(2*i, l, md, x, y);
	auto rx = query(2*i+1, md+1, r, x, y);
	return {{(lx[0][0] + rx[0][0])%mod}, {(lx[1][0] + rx[1][0])%mod}};
};

void solve(){
	int n, m; cin >> n >> m;
	for (int i = 0; i < n; ++i) cin >> v[i], --v[i];
	build(1, 0, n-1);
	while (m--) {
		int op; cin >> op;
		if (op == 1) { 
			int l, r, d; cin >> l >> r >> d;
			--l , --r;
			upd(1, 0, n-1, l, r, fexp(fib, d));
		} else {
			int l, r; cin >> l >> r;
			--l , --r;
			matrix ans = query(1, 0, n-1, l, r);
			cout << ans[0][0] << endl;
		}
	}
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}

