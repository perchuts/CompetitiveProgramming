#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define endl '\n'
#define pb push_back

using namespace std;

using ll = long long;

int32_t main() {_
	int x, b; cin >> x >> b;
	if (x >= b) {
		cout << -1 << endl;
		exit(0);
	}
	if (b % x) {
		int m = b % x;
		int falta = (b + x - 1) / x - 2;
		cout << m << " " << 0 << " ";
		for (int i = 1; i <= falta; ++i) cout << m + i << " ";
	} else {
		cout << x << " " << 0 << ' ';
		int falta = (b/x) - 2;
		for (int i = 1; i <= falta; ++i) cout << x + i << " ";
		cout << endl;
	}
}
