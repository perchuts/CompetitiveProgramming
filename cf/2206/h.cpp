#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;

int32_t main() {_
	int n; cin >> n;
	vector<int> a(n);
	for(auto& x : a) cin >> x;
	int U = a[0];
	int T = -a[n-1];
	int g = 0;
	
	for(int i=1;i<n;i++){
		g = gcd(g, 2*abs(a[i] - a[i-1]));
		if(a[i] - a[i-1] < 0) T += 2*(a[i] - a[i-1]);
	}

	int q = 0;
	if(g != 0) q = (U-1)/g*g;

	cout << -T-q << endl;
}
