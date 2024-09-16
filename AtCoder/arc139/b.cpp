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
	int n, a, b, x, y, z; cin >> n >> a >> b >> x >> y >> z;
	int ans = x * n;
	if (a*x <= y) {
		cout << min(ans, (n/b)*z + (n%b)*x) << endl;
		return;
	} 
	if (b*x <= z) {
		cout << min(ans, (n/a)*y + (n%a)*x) << endl;
		return;
	}
	if (a < b) swap(a, b), swap(z, y);
	int pedagio = 0;
	if (a * b <= n) {
		int lcm = (a * b / gcd(a, b)) * 530, consigo = n - (n%lcm);
		pedagio = min((consigo/a)*y, (consigo/b)*z);
		n %= lcm, ans = x * n;
	}
	for (int i = 0; i * a <= n; ++i) {
		int sobra = n - i * a, cost = i * y;
		ckmin(ans, cost + (sobra/b)*z + (sobra%b)*x);
	}
	cout << ans + pedagio << endl;
}

int32_t main(){_
  int t; cin >> t;
  while(t--) solve();
}
