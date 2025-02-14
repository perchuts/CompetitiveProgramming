#include <bits/stdc++.h>
using namespace std;

#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;
	vector<vector<pair<ll, int>>> mp;
	ll mx = 1e18 + 100,  lim = 5e6 + 100;
	for (int i = 2; i < 45; ++i) {
		vector<pair<ll, int>> m;
		int qnt = 0, lim2 = lim;
		for (int a = 1; a <= lim; ++a) {
			ll lcm = a;
			bool ok = 1;
			for (ll b = a+1; b <= a+i; ++b) {
				ll g = gcd(lcm, b);
				if (lcm / g > mx / b) {
					ok = 0;
					break;
				}
				lcm = lcm / g * b;
			}
			if (ok == 0) continue;	
			lim2 = a;
			m.push_back({lcm, a}); qnt++;
		}
		sort(begin(m), end(m));
		lim = lim2;
		mp.push_back(m);
	}
	int t; cin >> t;
	while (t--) {
		ll m; cin >> m;
		ll l = 0, r = 1e9;
		pair<ll, ll> ans = {m+1, m+1};
		while (l <= r) {
			ll md = l + (r-l+1)/2;
			if (md * (md+1) == m) {
				ans = {md, md+1};
				break;
			}
			if (md * (md+1) < m) l = md+1;
			else r = md-1;
		}
		for (int tam = 0; tam < mp.size(); ++tam) {
			int ind = lower_bound(begin(mp[tam]), end(mp[tam]), make_pair(m, 0)) - begin(mp[tam]);
			if (ind < mp[tam].size() and mp[tam][ind].first == m) ans = min(ans, {mp[tam][ind].second, mp[tam][ind].second+tam+2}); 
		}
		if (ans.first != m+1) cout << ans.first << ' ' << ans.second << endl;
		else cout << "NIE" << endl;
	}
}
