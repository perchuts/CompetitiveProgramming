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
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

int fexp(int b, int e) {
	int ans = 1;
	while (e) {
		if (e&1) ans = ans * b % mod;
		e /= 2, b = b * b % mod;
	}	
	return ans;
}


void solve(){
 	int n, k; cin >> n >> k;
	vector<int> a(n), fat(n+k+10), ifat(n+k+10);
	fat[0] = 1;
	for (int i = 1; i <= n+k+6; ++i) fat[i] = i * fat[i-1] % mod;
	ifat[n+k+6] = fexp(fat[n+k+6], mod - 2);
	for (int i = n + k + 5; i >= 0; --i) ifat[i] = (i + 1) * ifat[i+1] % mod;
	auto c = [&] (int x, int y) {
		return fat[x] * ifat[y] % mod * ifat[x-y] % mod;
	};
	for (auto& x : a) cin >> x;
	sort(all(a));
	vector<int> mexes;
	int i = 0, j = 0;
	while (sz(mexes) != k+1) {
		while (i < n && a[i] < j) i++;
		if (i < n && a[i] == j) j++;
		else mexes.pb(j++);
	}
	int ans = 0;
	for (i = 0; i <= k; ++i) {
		int go = mexes[i];
		// posso gerar qualquer merda entre 0 e go-1
		if (go) ans = (ans + c(go-1+k-i,go-1)) % mod;
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
