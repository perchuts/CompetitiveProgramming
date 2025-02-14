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
const int maxn = 5e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

struct node {
	int resp[2];
	int end_type[2];
	int val[2];
	int mn, id_min;
} seg[4*maxn];


node merge(node a, node b) {
	node res;
	for (int i = 0; i < 2; ++i) {
		int fim = a.end_type[i];
		int tr;
		if (fim == 1 or a.val[1] >= b.val[0]) tr = 0;
		else tr = 1;
		res.resp[i] = a.resp[i] + b.resp[tr];
		res.end_type[i] = b.end_type[tr];
	}
	if (a.mn <= b.mn) res.mn = a.mn, res.id_min = a.id_min;
	else res.mn = b.mn, res.id_min = b.id_min;
	res.val[0] = a.val[0];
	res.val[1] = b.val[1];
	return res;
};

void build(int i, int l, int r, vector<int> &a) {
	if (l == r) {
		seg[i].val[0] = seg[i].val[1] = seg[i].mn = a[l];
		seg[i].id_min = l;
		seg[i].end_type[0] = 0;
		seg[i].end_type[1] = 1;
		seg[i].resp[0] = 0;
		seg[i].resp[1] = 1;
		return;
	}	
	int md = (l+r)/2;
	build(2*i, l, md, a), build(2*i+1, md+1, r, a);
	seg[i] = merge(seg[2*i], seg[2*i+1]);
}

void upd(int i, int l, int r, int x, int k) {
	if (l == r) {
		seg[i].val[0] = seg[i].val[1] = seg[i].mn = k;
		return;
	}
	int md = (l+r)/2;
	if (x <= md) upd(2*i, l, md, x, k);
	else upd(2*i+1, md+1, r, x, k);
	seg[i] = merge(seg[2*i], seg[2*i+1]);
}

node query(int i, int l, int r, int x, int y) {
	if (x <= l and r <= y) return seg[i];
	int md = (l+r)/2;
	if (y <= md) return query(2*i, l, md, x, y);
	if (md < x) return query(2*i+1, md+1, r, x, y);
	return merge(query(2*i, l, md, x, y), query(2*i+1, md+1, r, x, y));
}

int get_answer(int n) {
	int id = seg[1].id_min;
	assert(id < n);
	node ans = query(1, 0, 2*n-1, id, id+n-1);
	return ans.resp[0];
}

void solve(){
	int n, q; cin >> n >> q;
	vector<int> v(n);
	for (auto& x : v) cin >> x;
	for (int i = 0; i < n; ++i) v.pb(v[i]);
	build(1, 0, 2*n-1, v);
	vector<int> ans;
	ans.pb(get_answer(n));
	while (q--) {
		int i, x; cin >> i >> x;
		upd(1, 0, 2*n-1, i, x);
		upd(1, 0, 2*n-1, i+n, x); 
		ans.pb(get_answer(n));
	}
	for (auto x : ans) cout << x << ' ';
	cout << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
