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

bool query(int i, int j, int k) {
	cout << "? " << i << ' ' << j << ' ' << k << endl;
	string ans; cin >> ans;
	return (ans[0] == 'Y');
}

mt19937 rng(time(0));
vector<int> ans;
int id_1 = 1;

void quicksort(vector<int> v, int l, int r) {
	if (l == r) {
		ans[l] = v[0];
		return;
	}
	int pivot = rng() % (r-l+1);
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

void solve(){
	int n; cin >> n; 	 
	ans.resize(n);
	for (int i = 2; i <= n; ++i) {
		if (query(i, i, id_1) == false) id_1 = i;
	}
	vector<int> aux(n); iota(all(aux), 1);
	quicksort(aux, 0, n-1);
	cout << "! ";
	for (auto x : ans) cout << x << ' ';
	cout << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
