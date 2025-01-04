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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

void solve(){
	int n; cin >> n;
	vector<int> c(n);
	map<int, int> cnt;
	for (auto& x : c) cin >> x, cnt[x]++;
	vector<int> freqs;
	for (auto [x, y] : cnt) freqs.pb(y);
	vector<int> fat(n+1, 1), ifat(n+1, 1);
	for (int i = 1; i <= n; ++i) fat[i] = fat[i-1] * i % mod;
	auto fexp = [&] (int b, int e) {
		int ans = 1;
		while (e) {
			if (e&1) ans = ans * b % mod;
			e /= 2, b = b * b % mod;
		}
		return ans;
	};
	ifat[n] = fexp(fat[n], mod - 2);
	for (int i = n-1; i >= 0; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
	auto choose = [&] (int a, int b) {
		if (a < b) return 0ll;
		return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
	};
	c = freqs;
	sort(all(c));
	vector<ii> yay;
	for (auto x : c) {
		if (yay.empty() or yay.back().first != x) yay.pb({x, 1});
		else yay.back().second++;
	}
	for (int k = 1; k <= n; ++k) {
		int ans = sz(c) * choose(n, k);
		for (auto [val, qnts] : yay) {
			ans = (ans - qnts * choose(n - val, k)) % mod;
			ans = (ans + mod) % mod;
		}
		ans = ans * fexp(choose(n, k), mod - 2) % mod;
		cout << ans << endl;
	}
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
