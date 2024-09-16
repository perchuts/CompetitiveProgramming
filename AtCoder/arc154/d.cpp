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

int tot_q = 0, id_1 = 1;

bool query(int i, int j, int k) {
	tot_q++;
	if (tot_q == 25001) assert(false);
	cout << "? " << i << ' ' << j << ' ' << k << endl;
	string ans; cin >> ans;
	return (ans[0] == 'Y');
}

vector<int> ans;

vector<int> mergesort(vector<int> v, int l, int r) {
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
void solve(){
	int n; cin >> n;
	ans.resize(n);
	for (int i = 2; i <= n; ++i) if (query(i, i, id_1) == false) id_1 = i;
	vector<int> aux(n); iota(all(aux), 1);
	auto order = mergesort(aux, 0, n-1);
	for (int i = 0; i < n; ++i) ans[order[i]-1] = i + 1;
	cout << "! ";
	for (auto x : ans) cout << x << ' ';
	cout << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
