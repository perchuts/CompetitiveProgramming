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
const int maxn = 3e6+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

void solve(){
	vector<int> fat(maxn, 1), ifat = fat;
	auto choose = [&] (int a, int b) { return fat[a] * ifat[b] % mod * ifat[a-b] % mod; };
	auto fexp = [&] (int b, int e) {
		int ans = 1;
		while (e) {
			if (e&1) ans = ans * b % mod;
			b = b * b % mod, e /= 2;
		}
		return ans;
	};
	for (int i = 1; i < maxn; ++i) fat[i] = fat[i-1] * i % mod;
	ifat[maxn-1] = fexp(fat[maxn-1], mod-2);
	for (int i = maxn-2; ~i; --i) ifat[i] = (i + 1) * ifat[i+1] % mod;

	int n, m; cin >> n >> m;
	vector<int> a(n), b(m);
	int tot = 0;
	for (auto& x : a) cin >> x;
	for (auto& x : b) cin >> x, tot += x;
	vector<vector<int>> c(n, vector<int>(m));
	for (auto& x : c) for (auto& y : x) cin >> y;
	vector<vector<int>> dp(n+1, vector<int>(1<<n));
	for (int i = 0; i < m; ++i) {
		int msk = 0;
		for (int j = 0; j < n; ++j) if (c[j][i]) msk += (1 << j);
		dp[n][msk] += b[i];
	}
	for (int i = 0; i < (1 << n); ++i) {
		for (int j = n-1; ~j; --j) {
			if (i >> j & 1) dp[j][i] = dp[j+1][i] + dp[j+1][i-(1<<j)];	
			else dp[j][i] = dp[j+1][i];
		}
	}
	vector<int> cost = dp[0];
	vector<int> cost_a(1<<n);
	int smol = 1e18;
	vector<int> masks;
	for (int i = 1; i < (1 << n); ++i) {
		if (cost[i] == 0) continue;
		for (int j = 0; j < n; ++j) if (i >> j & 1) cost_a[i] += a[j];
		if (ckmin(smol, tot - cost[i] + cost_a[i])) masks.clear();	
		if (smol < tot) {
			cout << 0 << ' ' << 1 << endl;
			exit(0);
		}
		if (smol == tot - cost[i] + cost_a[i]) masks.pb(i);
	}
	vector<int> good(1<<n);
	for (auto x : masks) good[x] = 1;
	for (int i = (1<<n)-2; ~i; --i) {
		for (int j = 0; j < n; ++j) {
			if (i >> j & 1) {}
			else good[i] |= good[i + (1<<j)];
		}
	}
	int ans = 0;
	for (int i = 1; i < (1 << n); ++i) {
		if (cost_a[i] <= smol - tot) continue;
		// dp[bit][i] = numero de maneiras de escolher TODOS os caras q tao ligados em i
		// e com bit >= i, e no resto tanto faz
		// queremos dp[0][i] pra todo good[i] == 1
		dp[n][i] = choose(cost_a[i], smol - tot + 1);
		for (int j = n-1; ~j; --j) {
			if (i >> j & 1) dp[j][i] = (dp[j+1][i] - dp[j][i-(1<<j)] + mod) % mod; 
			else dp[j][i] = dp[j+1][i]; 
		}
		if (good[i]) ans = (ans + dp[0][i]) % mod;
	}
	cout << smol - tot + 1 << ' ' << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
