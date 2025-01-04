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

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

void solve(){
	int n, m, k; cin >> n >> m >> k;
	vector<ii> items(k);
	vector<int> fat(n+m+1, 1), ifat(n+m+1);
	for (auto& [x, y] : items) cin >> x >> y, x = n - x, y = m - y;
	auto fexp = [&] (int b, int e) {
		int ans = 1;
		while (e) {
			if (e&1) ans = ans * b % mod;
			b = b * b % mod, e /= 2;
		}
		return ans;
	};
	for (int i = 1; i <= n+m; ++i) fat[i] = i * fat[i-1] % mod;
	ifat[n+m] = fexp(fat[n+m], mod-2);
	for (int i = n+m-1; ~i; --i) ifat[i] = (i + 1) * ifat[i+1] % mod;
	auto ncr = [&] (int a, int b) {
		return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
	};
	items.pb({0, 0});
	items.pb({n, m});
	sort(all(items), [&] (ii a, ii b) {
		return a.first + a.second < b.first + b.second;
	});
	k += 2;
	vector<vector<int>> dp(k, vector<int>(k));
	for (int j = k-1; ~j; --j) {
		for (int i = j+1; i < k; ++i) {
			auto [x1, y1] = items[i];
			auto [x2, y2] = items[j];
			if (x2 > x1 or y2 > y1) continue;
			dp[i][j] = ncr(x1+y1-x2-y2, x1-x2);
			for (int w = j+1; w < i; ++w) {
				auto [x3, y3] = items[w];
				if (x2 <= x3 && x3 <= x1 && y2 <= y3 && y3 <= y1) {
					dp[i][j] = (dp[i][j] - dp[w][j] * ncr(x1+y1-x3-y3,x1-x3)) % mod;
					dp[i][j] = (dp[i][j] + mod) % mod;
				}
			}
		}
	}
	vector<int> dp2(k);
	for (int i = 1; i < k; ++i) {
		for (int j = 0; j < i; ++j) {
			auto [x1, y1] = items[i];
			auto [x2, y2] = items[j];
			if (x2 > x1 or y2 > y1) continue;
			int gain = 2*(x1-x2)+y1-y2;
			gain = gain * ncr(x2+y2, x2) % mod;
			dp2[i] = (dp2[i] + dp[i][j]*(gain+dp2[j])) % mod;	
		}
		if (i != k-1) dp2[i] = (2 * dp2[i]) % mod;
	}
	int ans = (dp2.back() * fexp(ncr(n+m, m), mod-2)) % mod;
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while (t--) solve();
}

