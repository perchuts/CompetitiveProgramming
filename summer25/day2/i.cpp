#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;
	int n, k; cin >> n >> k;
	vector<int> foi(n+1);
	int qnt = 0, ans = 0;
	for (int i = 0; i < n; ++i) {
		int x; cin >> x;
		if (foi[x] == 0 and qnt < k) ans += i - qnt, qnt++, foi[x] = 1;
	}
	if (qnt == k) cout << ans << endl;
	else cout << -1 << endl;
}
