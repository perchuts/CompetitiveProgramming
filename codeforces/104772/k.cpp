#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define sz(x) (int) x.size()
#define all(x) begin(x), end(x)
#define pb push_back
#define int long long

using namespace std;

using ll = long long;

int32_t main() {_
	int t; cin >> t;
	while (t--) {
		int x; cin >> x;
		for (int ans = 0; ; ++ans) {
			int p = __builtin_popcountll(x+ans+1);
			if (p <= ans + 1) {	
				cout << ans << endl;
				break;
			}
		}
	}
}
