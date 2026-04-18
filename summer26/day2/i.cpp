#include <bits/stdc++.h>
#define int ll
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define pb push_back

using namespace std;

using ll = long long;

int32_t main() {_
	vector<int> penis(2000, 1);
	vector<int> prime;
	auto ask = [&] (int i) {
		cout << "? " << i << endl;
		int x; cin >> x;
		return x;
	};
	for (int i = 2; i <= 1986; ++i) {
		if (penis[i] == 0) continue;
		prime.pb(i);
		for (int j = i * i; j <= 1986; j += i) {
			penis[j] = 0;
		}
	}
	int t; cin >> t;
	while (t--) {
		ask(1);
		int ans = 1;
		for (auto p : prime) {
			int z = 1;
			while (true) {
				if (ans * z * p > 1986 or ask(z*p)) break;
				z *= p;
			}
			ans *= z;
		}
		cout << "! " << ans << endl;
	}
}
