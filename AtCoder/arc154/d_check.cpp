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


vector<int> p;
int tot_q = 0, id_1 = 1, C = 5;

bool query(int i, int j, int k) {
	tot_q++;
	--i, --j, --k;
	return ((p[i] + p[j]) > p[k]);
}

mt19937 rng(time(0));
vector<int> ans;

void quicksort(vector<int> v, int l, int r) {
	if (l > r) return;
	if (l == r) {
		ans[v[0]-1] = l + 1;
		return;
	}
	if (r-l+1 <= C) {
		for (int i = 0; i < r-l+1; ++i) {
			bool ok = 1;
			for (int j = 0; j < r-l-i; ++j) {
				if (query(v[j], id_1, v[j+1])) swap(v[j], v[j+1]), ok = 0;
			}
			if (ok) break;
		}
		for (int i = 0; i < r-l+1; ++i) {
			ans[v[i]-1] = l + 1 + i;
		}
		return;
	}
	auto find_median = [&] (int a, int b, int c) { 
		int x = query(v[a], id_1, v[b]);
		int y = query(v[b], id_1, v[c]);
		int z = query(v[a], id_1, v[c]);
		if (x^z) return a;
		if ((!x && !y) || (x&& y)) return b;
		return c;
	};
	int pivot1 = rng() % (r-l+1);
	int pivot2 = rng() % (r-l+1);
	int pivot3 = rng() % (r-l+1);
	int pivot = find_median(pivot1, pivot2, pivot3);
	vector<int> small, big;
	for (auto x : v) {
		if (x == v[pivot]) continue;
		if (query(x, id_1, v[pivot])) big.pb(x);
		else small.pb(x);
	}
	ans[v[pivot]-1] = l + sz(small) + 1; 
	quicksort(small, l, l + sz(small)-1);
	quicksort(big, l+sz(small)+1, r);
}

vector<int> mergesort(vector<int> v, int l, int r) {
	assert(sz(v) == r-l+1);
	if (l == r) return v;
	vector<int> le, ri;
	int md = (r-l+1)/2;
	for (int i = 0; i < md; ++i) le.pb(v[i]);
	for (int i = md; i < r-l+1; ++i) ri.pb(v[i]);
	le = mergesort(le, l, l+md-1), ri = mergesort(ri, l+md, r);
	vector<int> resp;
	int i = 0, j = 0;
	while (i + j != r-l+1) {
		if (i == sz(le)) resp.pb(ri[j++]);
		else if (j == sz(ri)) resp.pb(le[i++]);
		else {
			if (query(le[i], id_1, ri[j])) resp.pb(ri[j++]);
			else resp.pb(le[i++]);
		}
	}
	return resp;
		
}
int n;
void solve(){
	cin >> n;
	ans.resize(n);
	id_1 = 1;
	for (int i = 2; i <= n; ++i) {
		if (query(i, i, id_1) == false) id_1 = i;
	}
	vector<int> aux(n); iota(all(aux), 1);
	auto order = mergesort(aux, 0, n-1);
	for (int i = 0; i < n; ++i) ans[order[i]-1] = i + 1;
	for (auto x : ans) cout << x << ' ';
	cout << endl;
}

int32_t main(){_
	solve();
	return 0;
	n = 2000;
	p.resize(n);
	iota(all(p), 1);
	double tot = 0;
	int mx = 0, mn = 1e9;
	int tests = 100;
	for (int i = 0; i < tests; ++i) {
		shuffle(all(p), rng);
		solve();
		if (p != ans) {
			for (auto x : p) cout << x << ' ';
			cout << endl;
			for (auto x : ans) cout << x << ' ';
			cout << endl;
			exit(0);
		}
		tot += tot_q;
		ckmax(mx, tot_q);
		ckmin(mn, tot_q);
		tot_q = 0;
	}
	cout << "max: " << mx << endl;
	cout << "min: " << mn << endl;
	cout << "avg: " << tot / (double)tests << endl;
}
