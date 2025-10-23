#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

const int MOD = 998244353;

int fexp(int a, int b) {
	int ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		b /= 2;
	}
	return ans;
}

int choose(int a, int b) {
	int ans = 1;
	for (int i = 0; i < b; i++) ans = ans * (a - i) % MOD;
	for (int i = 0; i < b; i++) ans = ans * fexp(b - i, MOD - 2) % MOD;
	return ans;
}

int32_t main() {
	fast_io;

	int n, k;
	cin >> n >> k;

	if (k == 1) {
		cout << 1 << endl;
		return 0;
	}

	vector<int> b(n - k + 1);
	for (int &i : b) cin >> i;

	vector<int> a(n);
	for (int i = 1; i < b.size(); i++) {
		a[k + i - 1] = a[i - 1] + b[i] - b[i - 1];
	}

	int tot = b[0];
	for (int j = 0; j < k; j++) {
		int mn = 0;
		for (int i = j; i < n; i += k) {
			mn = min(mn, a[i]);
		}
		tot += mn;
	}

	if (tot < 0) cout << 0 << endl;
	else cout << choose(tot + k - 1, k - 1) << endl;
}
