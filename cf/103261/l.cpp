#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

const int MOD = (119<<23)+1;
int32_t main() {
	fast_io;
   	int n, c; cin >> n >> c; 
	vector<int> a(n);
	for (auto& x : a) cin >> x;
	// checa se eh zero
	for (int i = 0; i < n-1; ++i) {
		if (a[i] != -1 and a[i+1] > 0) {
			__int128 X = max(a[i], a[i+1]), Y = min(a[i], a[i+1]);
			if (Y*Y > c/X) {
				cout << 0 << endl;
				exit(0);
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		if (a[i] == -1 and (i == 0 or a[i-1] <= 0) and (i == n-1 or a[i+1] <= 0)) {
			cout << -1 << endl;
			exit(0);
		}
	}
	int sq_c = 0;
	{
		int l = 0, r = 1000000;
		while (l <= r) {
			int md = l + (r-l+1)/2;
			if (md*md*md <= c) sq_c = md, l = md+1;
			else r = md-1;
		}
	}
	auto get = [&] (int x) {
		int l = 0, r = 1e18, ans = 0;
		while (l <= r) {
			int md = l + (r-l+1)/2;
			__int128 X = max(md, x), Y = min(md, x);
			if (Y*Y <= c/X) ans = md, l = md+1;
			else r = md-1;
		}
		return ans;
	};
	vector<int> mx(sq_c+1), ps(sq_c+1);
	for (int i = 1; i <= sq_c; ++i) {
		mx[i] = get(i);
		ps[i] = ((i ? ps[i-1] : 0) + mx[i] - i) % MOD;
	}
	int ans = 1;
	const int inf = 1'000'000'000'000'000'000;
	for (int i = 0; i < n; ++i) {
		if (a[i] == -1) {
			if (i != n-1 and a[i+1] == -1) {
				// faz coisa
				int x = inf, y = inf, ways = 0;
				if (i != 0) x = get(a[i-1]);
				if (i != n-2) y = get(a[i+2]);
				// dois iguais
				ways = min({x, y, sq_c}) + 1;
				// x < y
				for (int __ = 0; __ < 2; ++__) {
					int l = 1, r = min(sq_c, x), opt = r+1;
					// quero achar o menor opt tal que mx[opt] <= y
					while (l <= r) {
						int md = l + (r-l+1)/2;
						if (mx[md] <= y) opt = md, r = md-1;
						else l = md+1;
					}
					//cout << "x = " << x << " y = " << y << " opt = " << opt << endl;
					if (y <= opt) {
						int ymod = y % MOD;
						int z = (ymod*(y-1) - (y-1)*y/2) % MOD;
						z = (z + MOD) % MOD;
						ways = (ways + z) % MOD;
					} else {
						int ymod = y % MOD;
						int z = (ymod*(opt-1) - (opt-1)*opt/2) % MOD;
						z = (z + MOD) % MOD;
						z = (z + ps[min(x, sq_c)] - ps[opt-1] + MOD) % MOD;
						ways = (ways + z) % MOD;
					}
					swap(x, y);
				}
				ways = (ways + x + y) % MOD;
				ans = ans * ways % MOD;
				i++;
			} else {
				// faz coisa
				int z = inf;
				if (i != 0) z = min(z, get(a[i-1]));
				if (i != n-1) z = min(z, get(a[i+1]));
				z %= MOD;
				z = (z + 1) % MOD;
				ans = ans * z % MOD;
			}
		}
	}
	cout << ans << endl;
}
