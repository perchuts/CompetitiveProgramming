#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define sz(x) (int) x.size()
#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

const int mod = 1e9+7;

int32_t main() {

	fast_io;

	int m, n; cin >> m >> n;

	vector<int> v(n), chains;

	for (auto& x : v) cin >> x;

	int mx = -1;

	for (int i = 0; i < n; ++i) if (v[i] >= mx) chains.pb(v[i]), mx = v[i];

	vector<int> fat(n+m+1, 1), ifat(n+m+1);

	for (int i = 1; i <= n+m; ++i) fat[i] = i * fat[i-1] % mod;

	auto fexp = [&] (int b, int e) {
		int ans = 1;
		while (e) {
			if (e&1) ans = ans * b % mod;
			e /= 2, b = b * b % mod;
		}
		return ans;
	};

	ifat.back() = fexp(fat[n+m], mod-2);

	for (int i = n+m-1; i >= 0; --i) ifat[i] = (i+1) * ifat[i+1] % mod;

	auto choose = [&] (int a, int b) {
		if (a < b) return 0ll;
		return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
	};

	int ans = 0;
	
	vector<int> freq;

	for (int l = 0, r = 0; l < sz(chains); l = r) {
		int c = 0;
		while (r != sz(chains) and chains[l] == chains[r]) c++, r++;
		freq.pb(c);
	}

	if (sz(chains) < m) {
		cout << 0 << endl;
		return 0;
	}

	for (int i = 1; i <= m; ++i) {	
		int cur = choose(m, i);
		for (auto x : freq) cur = cur * choose(i-1+x, x) % mod;
		if (i % 2 == m % 2) ans = (ans + cur) % mod;
		else ans = (ans - cur + mod) % mod;
	}

	cout << ans << endl;
}
