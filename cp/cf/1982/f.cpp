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
const int maxn = 5e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

struct node {
	int mn, mx, sorted;
} seg[4*maxn], nulo;

int v[maxn];

node merge(node a, node b) {
	node ans;
	ans.sorted = (a.sorted && b.sorted && a.mx <= b.mn);
	ans.mn = min(a.mn, b.mn), ans.mx = max(a.mx, b.mx);
	return ans;
}

void build(int i, int l, int r) {
	if (l == r) {
		seg[i].mn = seg[i].mx = v[l];
		seg[i].sorted = 1;
		return;
	}
	int md = (l + r) / 2;
	build(2*i, l, md), build(2*i+1, md+1, r);
	seg[i] = merge(seg[2*i], seg[2*i+1]);
}

void upd(int i, int l, int r, int x, int k) {
	if (l == r) {
		seg[i].mn = seg[i].mx = v[x] = k;
		return;
	}
	int md = (l + r) / 2;
	if (x <= md) upd(2*i, l, md, x, k);
	else upd(2*i+1, md+1, r, x, k);
	seg[i] = merge(seg[2*i], seg[2*i+1]);
}

int getPrefixSorted(int i, int l, int r) {
	if (l == r) return l;
	int md = (l + r) / 2;
	if (seg[2*i].sorted == 0) return getPrefixSorted(2*i, l, md);
	if (v[md+1] >= seg[2*i].mx) return getPrefixSorted(2*i+1, md+1, r);
	return md;
}

int getSuffixSorted(int i, int l, int r) {
	if (l == r) return l;
	int md = (l + r) / 2;
	if (seg[2*i+1].sorted == 0) return getSuffixSorted(2*i+1, md+1, r);
	if (v[md] <= seg[2*i+1].mn) return getSuffixSorted(2*i, l, md);
	return md + 1;
}

node query(int i, int l, int r, int x, int y) {
	if (r < x || y < l || x > y) return nulo;
	if (x <= l && r <= y) return seg[i];
	int md = (l + r) / 2;
	return merge(query(2*i, l, md, x, y), query(2*i+1, md+1, r, x, y));
}

int walkL(int i, int l, int r, int pref, int val) {
	if (l == r) return l;
	int md = (l + r) / 2;
	if (pref <= md) return walkL(2*i, l, md, pref, val);
	if (seg[2*i].mx <= val) return walkL(2*i+1, md+1, r, pref, val);
	return walkL(2*i, l, md, pref, val);
}

int walkR(int i, int l, int r, int suf, int val) {
	if (l == r) return l;
	int md = (l + r) / 2;
	if (md+1 <= suf) return walkR(2*i+1, md+1, r, suf, val);
	if (seg[2*i+1].mn >= val) return walkR(2*i, l, md, suf, val);
	return walkR(2*i+1, md+1, r, suf, val);
}

void solve(){
	int n; cin >> n;
	nulo.mn = 1e9, nulo.mx = -1e9, nulo.sorted = 1;
	for (int i = 1; i <= n; ++i) cin >> v[i];
	int q; cin >> q;
	build(1, 1, n);
	auto computeAns = [&] () {
		int lx = getPrefixSorted(1, 1, n), rx = getSuffixSorted(1, 1, n);
		node outerL = query(1, 1, n, lx+1, n), outerR = query(1, 1, n, 1, rx-1);
		int l = walkL(1, 1, n, lx, outerL.mn), r = walkR(1, 1, n, rx, outerR.mx);
		if (l == n) cout << -1 << ' ' << -1 << endl;
		else cout << l << ' ' << r << endl;
	};
	computeAns();
	while (q--) {
		int pos, x; cin >> pos >> x;
		upd(1, 1, n, pos, x);
		computeAns();
	}
}

int32_t main(){_
  int t; cin >> t;
  while(t--) solve();
}
