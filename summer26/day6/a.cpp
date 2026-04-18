#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back

using namespace std;

using ll = long long;

mt19937_64 rng(83472938);

int32_t main() {_
	int n; cin >> n;
	vector<int> a(n), b(n);
	for(auto& x : a) cin >> x;
	for(auto& x : b) cin >> x;
	int T = 1000;
	while(T--){
		vector<int> c = a;
		shuffle(c.begin(), c.end(), rng);
		int ok = 1;
		for(int i=0;i<n;i++) if(c[i] == a[i] || c[i] == b[i]) ok = 0;
		if(ok){
			for(auto x : c) cout << x << " ";
			cout << endl;
			return 0;
		}
	}
	cout << "IMPOSSIBLE" << endl;
}
