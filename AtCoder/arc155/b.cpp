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
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

void solve(){
 	int q; cin >> q;
	vector<iii> queries(q+1);
	int A, B; cin >> A >> B;
	set<int> T;
	queries[0] = {1, A, B};
	for (int i = 1; i <= q; ++i) {
		auto& [x, y, z] = queries[i];
		cin >> x >> y >> z;
	}
	for (auto [x, y, z] : queries) {
		if (x == 1) {
			T.insert(y-z), T.insert(y+z);
		} else {
			auto id = T.lower_bound(y);
			
			int ans = 1e18;
			if (id != end(T)) {
				if (*id <= z) ans = 0; 
				else ckmin(ans, (*id)-z);
			}
			if (id != begin(T)) {
				id = prev(id);
				ckmin(ans, y-(*id));
			}
			cout << ans << endl;
		}	
	}
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
