#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define sz(x) (int) x.size()
#define pb push_back
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const int magic = 30;
const int maxn = 2e5 + 10;

vector<int> primos;
bool crivo[maxn];

void solve() {
	int n, m; cin >> n >> m;
	vector<int> mark(n + m + 1);
	if (n + m >= magic) {
		// proofed :nerd: that if pi(n+m)+1 < min(n, m) there is no solution hehe
		// if this is true, solution for this case is straight forward
		vector<int> small, big;
		for (auto x : primos) {
			if (sz(small) == min(n, m) || x > n + m) break;
			small.pb(x), mark[x] = 1;
		}
		if (sz(small) != min(n, m)) {
			cout << "NO" << endl;
			return;
		}
		for (int i = 1; i <= n + m; ++i) {
			if (mark[i] == 0) big.pb(i);
		}
		if (n < m) swap(small, big);
		cout << "YES" << endl;
		for (int i = 0; i < n; ++i) cout << big[i] << " \n"[i==n-1];
		for (int i = 0; i < m; ++i) cout << small[i] << " \n"[i==m-1];
	} else {
		// nao sei fazer :(
		// sei sim kkkkkkkkkkkkkkkk
		vector<int> list;
		for (auto x : primos) {
			if (2 * x > n + m) break;
			if (x != 1) list.pb(x);
		}
		int k = list.size();
		// k <= 5
		vector<vector<vector<int>>> dp(n + m + 1, vector<vector<int>>((1<<k), vector<int>(n+1)));
		vector<int> val(n + m + 1);
		dp[0][0][0] = 1;
		int troca = (1 << k) - 1;
		for (int i = 1; i <= n + m; ++i) 
			for (int j = 0; j < k; ++j) 
				if (i % list[j] == 0) val[i] += (1 << j);
		for (int msk = 0; msk < (1 << k); ++msk) {
			for (int i = 1; i <= n + m; ++i) {
				for (int saturated = 0; saturated < (1 << k); ++saturated) {
					for (int j = 0; j <= min(i, n); ++j) {
						dp[i][saturated][j] = 0;
						if (i - j > m) continue;
						// colocar na esquerda
						if (j) {
							int ruim = ((msk ^ troca) & val[i]);
							if ((ruim&saturated) == ruim) {
								dp[i][saturated][j] |= dp[i-1][saturated - ruim][j-1];
							}
						}
						// colocar na direita
						int ruim = (msk & val[i]);
						if ((ruim&saturated) == ruim) {
							dp[i][saturated][j] |= dp[i-1][saturated-ruim][j];
						}
					}
				}
			}
			vector<int> v, w;
			int saturated = -1, j = n;
			for (int a = 0; a < (1 << k); ++a) {
					if (dp[n+m][a][n] == 1) saturated = a;
			}
			if (saturated == -1) continue;
			for (int i = n + m; i >= 1; --i) {
				if (j) {
					int ruim = ((msk ^ troca) & val[i]);
					if ((ruim&saturated) == ruim && dp[i-1][saturated-ruim][j-1]) {
						v.push_back(i);
						saturated -= ruim, j--;
						continue;
					}
				}
				int ruim = (msk&val[i]);
				assert((ruim&saturated) == ruim && dp[i-1][saturated-ruim][j]);
				w.push_back(i);
				saturated -= ruim;
			}
			assert(v.size() == n && w.size() == m);
			for (int a = 0; a < n; ++a) {
				for (int b = a + 1; b < n; ++b) {
					int p = gcd(v[a], v[b]);
					for (int c = 0; c < m; ++c) {
						for (int d = c + 1; d < m; ++d) {
							int q = gcd(w[c], w[d]);
							assert(gcd(p, q) == 1);
						}
					}
				}
			}
			cout << "YES" << endl;
			for (int i = 0; i < n; ++i) cout << v[i] << " \n"[i==n-1];
			for (int i = 0; i < m; ++i) cout << w[i] << " \n"[i==m-1];
			return;
		}
		cout << "NO" << endl;
	}
}

int32_t main() {
	fast_io;
	primos.pb(1);
	for (int i = 2; i < maxn; ++i) {
		if (crivo[i]) continue;
		primos.pb(i);
		if (i >= 10000) continue;
		for (int j = i * i; j < maxn; j += i) crivo[j] = 1;
	}
	int t; cin >> t;
	while (t--) solve();
	return 0;
}

