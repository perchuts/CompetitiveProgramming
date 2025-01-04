#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;
	int n, q; cin >> n >> q;
	while (q--) {
		int s, p; cin >> s >> p;
		int ans = 0;
		for (int k = 2; k <= min(n, 1001ll); ++k) {
			int l = (2*((s+p-1)/p) + k - k*k + 2*k-1) / (2 * k);	
			l = max(1ll, l);
			l = min(l, n-k+1);
			int r = (n+p-k*p)/p;
			r = max(r, l-1);
			ans += r-l+1;
		}
		cout << ans << endl;
	}

}
