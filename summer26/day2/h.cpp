#include <bits/stdc++.h>
#define int ll
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define pb push_back

using namespace std;

using ll = long long;
const int INF = 1e18;

int32_t main() {_
		int t; cin >> t;
		while (t--){
			int n; cin >> n;
			int a, b; cin >> a >> b;
			a--; b--;
			int t1, t2, t3, t4, t5, t6; cin >> t1 >> t2 >> t3 >> t4 >> t5 >> t6;

			if (a == b){
				cout << 0 << endl;
				continue;
			}

			int d1 = (b > a) ? b-a : (n-a)+b;
			int d2 = n-d1;

			int ans = min({d1*t1, d1*t4, d2*t2, d2*t3, (d1/2)*t5 + (d1&1)*min(t1,t4), (d2/2)*t6 + (d2&1)*min(t2,t3)});
			if (d1&1) ans = min(ans, (d1/2 + 1) * t5 + min(t2,t3));
			if (d2&1) ans = min(ans, (d2/2 + 1) * t6 + min(t1,t4));

			cout << ans << endl;
		}
}
