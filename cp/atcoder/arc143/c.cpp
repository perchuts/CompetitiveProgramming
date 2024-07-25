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
 	int n, x, y; cin >> n >> x >> y;
	vector<int> v(n);
	for (auto& z : v) cin >> z;
	if (x == y) {
		bool ok = 1;
		for (auto z : v) {
			z /= x;
			ok &= (z % 2 == 0);
		}
		cout << (ok ? "Second" : "First") << endl;
		return;
	}
	if (x < y) {
		for (auto z : v) {
			int m = z % (x + y);
			if (x <= m && m < y) {
				cout << "First" << endl;
				return;
			}	
		}
		cout << "Second" << endl;
		return;
	} else {
		bool ok = 0;
		for (auto z : v) {
			int m = z % (x + y);
			if (y <= m && m < x) {
				cout << "Second" << endl;
				return;
			}
			if (z >= x) {
				m = (z - x) % (x + y);
				ok |= (!(y <= m && m < x));
			}
		}
		cout << (ok ? "First" : "Second") << endl;
	}	
	
}

int32_t main(){_
	int t = 1; // cin >> t;
	while (t--) solve();
}
