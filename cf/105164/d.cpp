#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

const int MOD = 1e9 + 7;

int32_t main() {
	fast_io;

	int n; cin >> n;

	int igual = 0, ans = 0;
	for (int a = 1; a <= n; ++a) {
		int l = a/2 + 1;
		int r = min((n-a)/2, a);
		if (l <= r) igual += r - l + 1;
	}

	for (int a = 1; a <= (n-1)/2; ++a) {
		int k = min(a, n-2*a-1);
		ans += (k+1)*k/2;
		if (n-2*a <= a) {
			ans += n*(a-(n-2*a)+1);
			ans -= 2 * a * (a-(n-2*a)+1);
		}
		//cout << ans << ' ';
	}
	//cout << "Ans: " << ans << endl;
	//cout << "Igual: " << igual << endl;
	//cout << ans << ' ' << igual << endl;
	ans = (ans-igual);
	assert(ans % 2 == 0);
	ans /= 2;
	ans += igual;
	ans %= MOD;
	cout << ans << endl;
}
