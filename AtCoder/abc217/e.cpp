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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

void solve(){
	int q; cin >> q;
	multiset<int> mt;
	vector<int> vals;
	map<int, int> qt;
	int lst_sort = 0, ptr = 0;
	while (q--) {
		int op; cin >> op;
		if (op == 1) {
			int x; cin >> x;
			vals.pb(x);
			qt[x]++;
		} else if (op == 2) {
			if (ptr < lst_sort) {
				cout << (*begin(mt)) << endl;
				qt[*begin(mt)]--;
				mt.erase(mt.find(*begin(mt)));
			} else {
				while (qt[vals[ptr]] == 0) ptr++;
				cout << vals[ptr] << endl;
				qt[vals[ptr]]--;
				lst_sort++;
			}
			ptr++;
		} else {
			for (int i = lst_sort; i < sz(vals); ++i) mt.insert(vals[i]);
			lst_sort = sz(vals);
		}
	}
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
