#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;

		const int MOD = 1e9 + 7;
		using T = array<array<int, 3>, 3>;

		auto mul = [&] (T a, T b) {
			T ans{};
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
						ans[i][k] = (ans[i][k] + a[i][j] * b[j][k]) % MOD;
			return ans;
		};

		T a, ans;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				a[i][j] = i != j;
				ans[i][j] = i == j;
			}
		}

		n--;
		while (n) {
			if (n % 2) {
				ans = mul(ans, a);
			}
			a = mul(a, a);
			n /= 2;
		}

		cout << (ans[0][1] + ans[0][2]) % MOD << endl;
	}
}
