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
const int maxn = 6e5+100;

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

int fat[maxn], ifat[maxn];

int choose(int a, int b) {
	if (a < b) return 0;
	return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
}

void solve(){
	int n, k; cin >> n >> k;
	int alice = 0;
	vector<int> v(n);
	for (auto& x : v) cin >> x;
	int P = 0, m1 = (n-k+1)/2, m2 = (n-k)/2;
	for (int i = 0; i < k; ++i) P = (P + v[i]) % mod;
	int sum = 0;
	for (int i = 0; i < n; ++i) sum = (sum + v[i]) % mod;
	if (n == k) {
		cout << sum << ' ' << 0 << endl;
		return;
	}
	if ((m1+m2)&1) m2++;
	else m1++;
	for (int i = 1; i <= k; ++i) {
		int prob = choose(m1+i-1, m1-1) * choose(m2+k-i-1, m2-1) % mod;
		int sum_subsets = P * choose(k-1, i - 1) % mod; 
		alice = (alice + prob * sum_subsets % mod * fexp(choose(k, i), mod-2)) % mod;
	} 	
	alice = (alice * fexp(choose(m1+m2-1+k, m1+m2-1), mod-2)) % mod;
	if ((m1+m2)&1) m1--;
	else m2--;
	for (int i = k; i < n; ++i) alice = (alice + v[i] * m1 % mod * fexp(m1+m2, mod - 2) % mod) % mod;
	cout << alice << ' ' << (sum - alice + mod) % mod << endl;
}

int32_t main(){_
  int t; cin >> t;
  fat[0] = 1;
  for (int i = 1; i < maxn; ++i) fat[i] = fat[i-1] * i % mod;
  ifat[maxn-1] = fexp(fat[maxn-1], mod - 2);
  for (int i = maxn-2; i >= 0; --i) ifat[i] = (i + 1) * ifat[i+1] % mod;
  while(t--) solve();
}
