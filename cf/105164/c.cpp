#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;

	array<int, 3> a, b;
	cin >> a[0] >> a[1] >> a[2];
	cin >> b[0] >> b[1] >> b[2];

	vector<int> ord = {0, 1, 2};
	int ans = 0;
	do {
		int x = 1;
		x *= a[0] / b[ord[0]];
		x *= a[1] / b[ord[1]];
		x *= a[2] / b[ord[2]];
		ans = max(ans, x);
	} while (next_permutation(ord.begin(), ord.end()));

	cout << ans << endl;
}
