#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define endl '\n'
#define pb push_back

using namespace std;

using ll = long long;

int32_t main() {_
	int n; cin >> n;
	vector<int> as(n), bs(n);
	for (int i = 0; i < n; ++i) cin >> as[i];
	for (int i = 0; i < n; ++i) cin >> bs[i];

	vector<int> dp0(4001);
	for (int i = 0; i < n; ++i){
		vector<int> dp1(4001);
		for (int j = 0; j <= min(i,4000ll); ++j){
			if (j < 4000) dp1[j+1] = max(dp1[j+1], dp0[j]);
			dp1[j] = max(dp1[j], dp0[j] + (bs[i-j] * as[i]));
		}
		swap(dp0,dp1);
	}

	int ans = 0;
	for (auto v : dp0) ans = max(ans,v);
	cout << ans << endl;
}
