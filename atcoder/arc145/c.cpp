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
const int mod = 998244353;
const int maxn = 5e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
int fat[maxn], ifat[maxn];
int fexp(int b, int e) {
	int p = b, ans = 1;
	while (e) {
		if (e&1) ans = ans * p % mod;
		p = p * p % mod, e /= 2;
	}
	return ans;
}
void solve() {
	int n; cin >> n;
	fat[0] = 1;
	for (int i = 1; i <= 2 * n; ++i) fat[i] = fat[i-1] * i % mod;
	ifat[2*n] = fexp(fat[2*n], mod - 2);
	for (int i = 2 * n - 1; i >= 0; --i) ifat[i] = (i + 1) * ifat[i+1] % mod;
	int pt = 1;
	for (int i = 1; i <= n; ++i) pt = 2 * pt % mod;
	cout << (pt * fat[2*n] % mod * ifat[n+1] % mod) << endl; 
}

int32_t main() {_
	int t = 1; //cin >> t;
	while(t--) solve();
}
