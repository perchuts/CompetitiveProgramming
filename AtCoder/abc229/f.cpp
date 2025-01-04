#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define stress

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

int solve(int n, vector<int> a, vector<int> b){
	int sum = 0;
	for (int i = 0; i < n; ++i) a.pb(a[i]), sum += b[i];
	for (int i = 0; i < n; ++i) b.pb(b[i]), sum += a[i];
	struct node {
		int lst, best[2][2];
	} nulo, seg[8*n+69];
	nulo.lst = -1; 
	auto merge = [&] (node& le, node& ri) {
		if (le.lst == -1) return ri;
		if (ri.lst == -1) return le;
		node res;
		res.lst = ri.lst;
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 2; ++j) {
				res.best[i][j] = -1e18;
				for (int x = 0; x < 2; ++x) {
					for (int y = 0; y < 2; ++y) {
						ckmax(res.best[i][j], le.best[i][x] + ri.best[y][j] + (x == y ? a[le.lst] : 0));
					}
				}
			}
		}
		return res;
	};
	function<void(int, int, int)> build = [&] (int i, int l, int r) {
		if (l == r) {
			for (int bit = 0; bit < 2; ++bit) {
				seg[i].best[bit][bit] = (l % 2 == bit ? b[l] : 0);
				seg[i].best[bit][bit^1] = -1e18;
			}
			seg[i].lst = l;
			return;
		}
		int md = (l+r)/2;
		build(2*i, l, md), build(2*i+1, md+1, r);
		seg[i] = merge(seg[2*i], seg[2*i+1]);
	};
	bool yes = 0;
	function<node(int, int, int, int, int)> query = [&] (int i, int l, int r, int x, int y) {
		if (r < x or y < l) return nulo;
		if (x <= l and r <= y) {
			if (yes) {
			}
			return seg[i];
		}
		int md = (l+r)/2;
		node le = query(2*i, l, md, x, y);
		node ri = query(2*i+1, md+1, r, x, y);
		return merge(le, ri);
	};
	build(1, 0, 2*n-1);
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		yes = (i == 3);
		node tudo = query(1, 0, 2*n-1, i, i+n-1);
		ckmax(ans, max({tudo.best[0][0], tudo.best[0][1], tudo.best[1][0], tudo.best[1][1]}));
	}
	int sa = 0, par = 0, impar = 0;
	for (int i = 0; i < n; ++i) {
		sa += a[i];
		if (i&1) impar += b[i];
		else par += b[i];
	}
	if (n % 2 == 0) ckmax(ans, sa + max(par, impar));
	return sum - ans;
}

int32_t main(){_
#ifndef stress
	int n; cin >> n;
	vector<int> a(n), b(n);
	for (auto& x : b) cin >> x;
	for (auto& x : a) cin >> x;
	cout << solve(n, a, b) << endl;
#else 
	int t = 1;
	while (true) {
		int n = rnd(3, 5);
		vector<int> a(n), b(n);
		for (auto& x : a) x = rnd(1, 10);
		for (auto& x : b) x = rnd(1, 10);
		int ans = solve(n, a, b);
		for (int i = 0; i < n; ++i) {
			vector<int> va, vb;
			for (int j = 0; j < n; ++j) va.pb(a[(j+1)%n]), vb.pb(b[(j+1)%n]);
			swap(a, va), swap(b, vb);
			if (solve(n, a, b) != ans) {
				cout << "Distinct answers for cyclic shifts on test " << t << endl;
				cout << n << endl;
				for (auto x : va) cout << x << ' ';
				cout << endl;
				for (auto x : vb) cout << x << ' ';
				cout << endl;
				cout << "Answer: " << solve(n, va, vb) << endl;
				cout << endl;
				cout << "cyclic shift: " << endl;
				cout << n << endl;
				for (auto x : a) cout << x << ' ';
				cout << endl;
				for (auto x : b) cout << x << ' ';
				cout << endl;
				cout << "Answer: " << solve(n, a, b) << endl;
				exit(0);
			}
			cout << "Ok for test " << t++ << endl;
		}
	}
#endif
}
