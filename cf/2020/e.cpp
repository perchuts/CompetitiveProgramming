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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

void solve(){
	int n; cin >> n;
	vector<int> a(n);
	vector<int> p(n);
	for (auto& x : a) cin >> x;
	for (auto& x : p) cin >> x;
	auto fexp = [&] (int b, int e) {
		int ans = 1;
		while (e) {
			if (e&1) ans = ans * b % mod;
			b = b * b % mod, e /= 2;
		}
		return ans;
	};
	int ans = 0;
	for (int i = 0; i < 10; ++i) {
		for (int j = i; j < 10; ++j) {
			vector<vector<int>> dp(2, vector<int>(2));
			dp[0][0] = 1;
			for (int k = 0; k < n; ++k) {
				vector<vector<int>> ndp(2, vector<int>(2));
				int vali = ((a[k] >> i)&1);
				int valj = ((a[k] >> j)&1);
				for (int eu = 0; eu < 2; ++eu) {
					int pp = (eu ? p[k] : 10000-p[k]);
					for (int x = 0; x < 2; ++x) {
						for (int y = 0; y < 2; ++y) {
								
							int nx, ny;
							if (vali) nx = x^eu;
							else nx = x;

							if (valj) ny = y^eu;
							else ny = y;

							ndp[nx][ny] = (ndp[nx][ny] + dp[x][y] * pp) % mod; 
						}
					}
				}
				swap(dp, ndp);
			}
			int xx = (1 << i), yy = (1<<j);
			if (i == j) ans = (ans + xx * xx * dp[1][1]) % mod;
			else ans = (ans + 2 * xx * yy * dp[1][1]) % mod;
		}
	}
	int x = fexp(fexp(10000, mod - 2), n);
	ans = (ans * x) % mod;
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
