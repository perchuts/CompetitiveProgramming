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

void solve() {
	int x; cin >> x;
	if (x == 1) {
		cout << 0 << endl;
		return;
	}
	x--;
	int pot = 1;
	for (int digits = 1; digits <= 18; ++digits) {
		if (9 * pot >= x) {
			int p2 = pot + x - 1;
			string ans = to_string(p2);
			p2 /= 10;
			if (digits > 1) {
				string sx = to_string(p2);
				reverse(all(sx));
				ans += sx; 
			}
			cout << ans << endl;
			return;
		}
		x -= 9 * pot;
		if (9 * pot >= x) {
			int p2 = pot + x - 1;
			string sx = to_string(p2);
			string ans = sx;
			reverse(all(sx));
			ans += sx;
			cout << ans << endl;
			return;
		}
		x -= 9 * pot;
		pot *= 10;
	}
}

int32_t main() {_
	int t = 1; //cin >> t;
	while(t--) solve();
}
