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
const int maxn = 998244353;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

int fexp(int b, int e) {
	int ans = 1, p = b;
	while (e) {
		if (e&1) ans = ans * p % mod;
		p = p * p % mod, e /= 2;
	}
	return ans;
}

int brute(int n) {
	int ans = 0;
	for (int i = 0; i < (1 << (1<<n)); ++i) {
		bool ok = 1;
		for (int j = 1; j < (1 << (1<<n)); ++j) {
			if (((i&j) != j) || (__builtin_popcount(j) % 2 == 1)) continue;
			int xx = 0;
			for (int k = 0; k < (1 << n); ++k) if ((j>>k)&1) xx ^= k;
			if (xx == 0) {
				ok = 0; break;
			}
		}
		if (ok) ans++;
	}
	return ans;
}	

void solve(){
	int n; cin >> n;
	//cout << brute(n) << endl;
 	int ans = 2;
	// conjunto vazio
	vector<int> qtd_ind(n+2);
	// sem o 0
	qtd_ind[1] = (fexp(2, n) - 1 + mod) % mod;
	for (int i = 2; i <= n; ++i) {
		qtd_ind[i] = (qtd_ind[i-1] * (fexp(2, n) - fexp(2, i-1) + mod)) % mod;
			//if (((i&j) != j)in_popcount(j) % 2 == 1)) continue;
		qtd_ind[i] = qtd_ind[i] * fexp(i, mod - 2) % mod;
	}
	vector<int> tot_ind(n+1);
	tot_ind[0] = 1;
	for (int i = 1; i <= n; ++i) {
		vector<int> tmp(n+2);
		tmp[0] = 1;
		tmp[1] = (fexp(2, i) - 1 + mod) % mod;
		for (int j = 2; j <= i; ++j) {
			tmp[j] = (tmp[j-1] * (fexp(2, i) - fexp(2, j-1) + mod)) % mod;
			tmp[j] = (tmp[j] * fexp(j, mod - 2)) % mod;
		}
		for (auto x : tmp) tot_ind[i] = (tot_ind[i] + x) % mod;
		cout << i << ": " << tot_ind[i] << endl;
	}
	for (int i = 1; i <= n; ++i) {
		ans = (ans + 2*qtd_ind[i]) % mod;	
		cout << qtd_ind[i] << endl;
		if (i % 2 == 0) ans = (ans + qtd_ind[i] * fexp(i+1, mod-2) % mod * tot_ind[n-i]) % mod;
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}

