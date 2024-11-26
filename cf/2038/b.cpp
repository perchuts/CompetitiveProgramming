#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define int long long
#define endl '\n'
using namespace std;

typedef long long ll;

int v[696969], v2[696969];

bool good(ll x, int n, int ops){
	int cost = 1, mod = 2, m = mod-1;
	for (int i = 0; i < n; ++i) v[i] = v2[i];
	while (ops >= 0 and cost <= ops) {
		for (int i = 0; i < n; ++i) {
			int w = v[i] & m;
			w = (w + mod) & m;
			if (x % mod != w) {
				v[i] += mod/2;
				v[(i?i-1:n-1)] -= mod;
				ops -= cost;
			}
		}
		mod *= 2, cost *= 2;
		m = 2*m+1;
	}
	for (int i = 0; i < n; ++i) if (v[i] != x) return false;
	return true;
}

int32_t main(){ _
	int t; cin >> t;
	while(t--){
		int n; ll tot = 0; cin >> n;
		for (int i = 0; i < n; ++i) cin >> v2[i], tot += v2[i];
		ll l = 0, r = 1e9, ans = -1;
		while(l <= r){
			ll m = (l+r)/2;
			if(good(m, n, tot - m*n)) ans = m, l = m+1;
			else r = m-1;
		}

		if(ans == -1) cout << ans << endl;
		else cout << tot-ans*n << endl;
	}
}

