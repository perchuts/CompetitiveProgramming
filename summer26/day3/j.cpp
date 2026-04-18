#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define endl '\n'
#define _ ios_base::sync_with_stdio(0);cin.tie(0);

using namespace std;

using ll = long long;

int32_t main() {_
	int n; cin >> n;
	vector<int> a(n), msb(n);
	for (auto& x : a) cin >> x;
	int mn = 1e18;
	for (int i = 0; i < n; ++i) {
		int cur = a[i];
		while (cur) {
			msb[i] = max(1LL, 2 * msb[i]);
			cur /= 2;
		}
		mn = min(mn, msb[i]);
	}
	if (mn == 0) {
		cout << 0 << endl;
		return 0;
	}
	int ans = a[0];
	for (int i = 1; i < n; ++i) ans = (ans & a[i]);
	// soh posso flipar os bichos ate aqui
	for (int j = 1; j <= mn; j *= 2) {
		auto b = a;
		int resp = -1;
		for (int i = 0; i < n; ++i) {
			int x = b[i];
			if (x & j) {}
			else {
				x = (2 * msb[i] - 1) - x;
			}
			if (resp == -1) resp = x;
			else resp = (resp & x);
		}
		ans = max(ans, resp);
	}
	cout << ans << endl;
}
