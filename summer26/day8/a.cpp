#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll

using namespace std;

using ll = long long;

int32_t main() {_
	int n; cin >> n;
	vector<int> vec(n);
	for (int i = 0; i < n; ++i) cin >> vec[i];
	sort(vec.begin(), vec.end());
	
	int ans = 0;
	for (int i = 0; i < n; ++i){
		int v = (i == n-1) ? i+1 : i+2;
		ans += vec[i] * v;
	}

	cout << ans << endl;
}
