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
 	int n; cin >> n;
	vector<int> v(n);
	for (auto& x : v) cin >> x;
	vector<int> eq(n, 1);
	for (int i = n-2; i >= 0; --i) {
		if (v[i] == v[i+1]) eq[i] = eq[i+1]+1;
		else eq[i] = 1;
	}
	int ans = 0;
	vector bl(20, vector(n, 0));
	for (int p = 0; p < 20; ++p) {
		for (int i = 0; i + (1 << p) < n; ++i) {
			if (p == 0) bl[0][i] = abs(v[i] - v[i+1]);
			else {
				bl[p][i] = gcd(bl[p-1][i], bl[p-1][i+(1<<(p-1))]);
			}	
		}
	}
	for (int i = 0; i < n; ++i) {
		ans += eq[i];
		int g = 0, pos = i + eq[i] - 1;
		for (int j = 19; j >= 0 && pos < n-1; --j) {
			int k = gcd(g, bl[j][pos]);
			if (__builtin_popcount(k) > 1 && pos + (1 << j) < n) {
				g = k;
				pos += (1 << j);
			}
		}
		if (pos < n-1) {
			g = gcd(bl[0][pos], g);
			if (__builtin_popcount(g) == 1) ans += n - pos - 1; 
		}
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
