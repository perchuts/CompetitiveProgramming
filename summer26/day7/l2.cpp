#include <bits/stdc++.h>
#define int ll
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
using namespace std;

using ll = long long;

int32_t main() {_
	int n; cin >> n;
	int b, c; cin >> b >> c;

	vector<int> hs(n);
	for (int i = 0; i < n; ++i) cin >> hs[i];


	vector<int> ans(n+1,10000000);
	for (int i = 1; i < (1<<n);++i){
		int cur = 0;
		for (int u = 0; u < n; ++u){
			int d = 10000;
			for (int v = 0; v < n; ++v) if (i>>v&1) d = min(d,abs(u-v));
			cur += d*hs[u];
		}
		int k = __builtin_popcountll(i);
		ans[k] = min(ans[k], cur);
	}

	for (int i = 1; i <= n; ++i) cout << ans[i]*c + i*b << " ";
	cout << endl;

}
